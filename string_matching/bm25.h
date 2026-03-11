/**
 * BM25 Ranking Algorithm
 *
 * BM25 (Okapi BM25 – Best Match 25) is a bag-of-words relevance ranking
 * function widely used in full-text search engines.  It extends TF-IDF by
 * adding:
 *   • Term-frequency saturation  – repeated occurrences of a term have
 *     diminishing returns (controlled by k1).
 *   • Document-length normalisation – longer documents are penalised
 *     relative to the average document length (controlled by b).
 *
 * BM25 score for query Q and document D:
 *
 *   score(D, Q) = Σ_{t in Q}  IDF(t) ·
 *                              tf(t, D) · (k1 + 1)
 *                              ──────────────────────────────────────────
 *                              tf(t, D) + k1 · (1 - b + b · |D| / avgdl)
 *
 *   IDF(t) = log( (N - df(t) + 0.5) / (df(t) + 0.5) + 1 )
 *
 * Where:
 *   tf(t, D)  – frequency of term t in document D
 *   df(t)     – number of documents containing term t
 *   N         – total number of documents in the corpus
 *   |D|       – length (number of tokens) in document D
 *   avgdl     – average document length across the corpus
 *   k1        – TF saturation parameter (typical range: 1.2 – 2.0)
 *   b         – length normalisation parameter (0 = off, 1 = full; typical: 0.75)
 *
 * Used in:
 * - Search engines (Elasticsearch, Solr, Lucene use BM25 as the default)
 * - Question answering retrieval
 * - Passage retrieval for RAG (retrieval-augmented generation) pipelines
 * - Document ranking in information retrieval benchmarks (TREC, BEIR)
 */

#ifndef BM25_H
#define BM25_H

#include <stddef.h>
#include <stdbool.h>

/* -------------------------------------------------------------------------
 * Parameters
 * ------------------------------------------------------------------------- */

/** Default BM25 hyperparameters (Elasticsearch / Lucene defaults). */
#define BM25_DEFAULT_K1  1.2
#define BM25_DEFAULT_B   0.75

/**
 * BM25 algorithm hyperparameters.
 */
typedef struct {
    double k1;  /* TF saturation (1.2 – 2.0 typical) */
    double b;   /* Length normalisation (0.0 – 1.0)  */
} BM25Params;

/* -------------------------------------------------------------------------
 * Corpus structures
 * ------------------------------------------------------------------------- */

/**
 * A single pre-tokenised document.
 * Tokens are null-terminated strings; the caller is responsible for their
 * lifetime while the document is in the corpus.
 */
typedef struct {
    const char **tokens;    /* Array of token strings                 */
    size_t       n_tokens;  /* Number of tokens (document length)     */
    size_t       doc_id;    /* Unique document identifier (0-indexed) */
} BM25Document;

/**
 * Entry in the inverted index for one term.
 * Records which documents contain the term and with what frequency.
 */
typedef struct {
    size_t  doc_id;  /* Document containing this term    */
    size_t  tf;      /* Term frequency within that document */
} BM25Posting;

/**
 * BM25 corpus – manages a collection of documents and a term inverted index.
 *
 * Typical usage:
 *   1. bm25_create()          – allocate corpus
 *   2. bm25_add_document() ×N – add each document
 *   3. bm25_build_index()     – build inverted index (required before ranking)
 *   4. bm25_rank()            – rank documents for a query
 *   5. bm25_free()            – release memory
 */
typedef struct {
    BM25Params  params;        /* Algorithm hyperparameters          */

    BM25Document *docs;        /* Array of added documents           */
    size_t        n_docs;      /* Current number of documents        */
    size_t        docs_cap;    /* Allocated capacity for docs array  */

    /* Inverted index – populated by bm25_build_index() */
    char       **terms;        /* Sorted unique term strings         */
    size_t       n_terms;      /* Number of unique terms             */
    size_t      *df;           /* df[i] = document frequency of term i */
    BM25Posting **postings;    /* postings[i] = posting list for term i */
    size_t       *postings_len;/* Length of each posting list        */

    double avg_doc_len;        /* Average number of tokens per document */
    bool   index_built;        /* True after bm25_build_index() succeeds */
} BM25Corpus;

/**
 * A (document, score) pair returned by bm25_rank().
 */
typedef struct {
    size_t doc_id; /* Index into BM25Corpus->docs */
    double score;  /* BM25 relevance score (higher = more relevant) */
} BM25Result;

/* -------------------------------------------------------------------------
 * Construction / destruction
 * ------------------------------------------------------------------------- */

/**
 * Create an empty BM25 corpus with the given hyperparameters.
 *
 * Pass BM25_DEFAULT_K1 / BM25_DEFAULT_B for standard settings.
 *
 * @param params Algorithm hyperparameters
 * @return Allocated corpus, or NULL on failure
 */
BM25Corpus* bm25_create(BM25Params params);

/**
 * Free all memory owned by a BM25Corpus.
 *
 * @param corpus Corpus to free (safe to call with NULL)
 */
void bm25_free(BM25Corpus *corpus);

/* -------------------------------------------------------------------------
 * Corpus construction
 * ------------------------------------------------------------------------- */

/**
 * Add a pre-tokenised document to the corpus.
 *
 * Must be called before bm25_build_index().  The token array and its strings
 * must remain valid until bm25_free() is called.
 *
 * @param corpus   Target corpus
 * @param tokens   Array of token (word) strings
 * @param n_tokens Number of tokens in the document
 * @return Assigned doc_id (0-indexed), or SIZE_MAX on failure
 */
size_t bm25_add_document(BM25Corpus *corpus,
                         const char **tokens,
                         size_t n_tokens);

/**
 * Build the inverted index over all added documents.
 *
 * Computes per-term document frequencies (df), per-document term frequencies
 * (tf), and the average document length.  Must be called after all documents
 * have been added and before any calls to bm25_rank() or bm25_score().
 *
 * @param corpus Corpus to index
 * @return true on success
 */
bool bm25_build_index(BM25Corpus *corpus);

/* -------------------------------------------------------------------------
 * Scoring
 * ------------------------------------------------------------------------- */

/**
 * Compute the BM25 score for a single query term against one document.
 *
 * @param corpus   Indexed BM25Corpus
 * @param term     Query term string
 * @param doc_id   Document to score
 * @return BM25 contribution of this term, or 0.0 if term not in index
 */
double bm25_score_term(const BM25Corpus *corpus,
                       const char *term,
                       size_t doc_id);

/**
 * Compute the total BM25 score for a multi-term query against one document.
 *
 * score(D, Q) = Σ_{t in Q} bm25_score_term(corpus, t, doc_id)
 *
 * @param corpus    Indexed BM25Corpus
 * @param query     Array of query token strings
 * @param n_query   Number of query tokens
 * @param doc_id    Document to score
 * @return Total BM25 score
 */
double bm25_score(const BM25Corpus *corpus,
                  const char **query,
                  size_t n_query,
                  size_t doc_id);

/**
 * Rank all documents in the corpus for a query, returning results sorted
 * by descending BM25 score.
 *
 * @param corpus    Indexed BM25Corpus
 * @param query     Array of query token strings
 * @param n_query   Number of query tokens
 * @param out       Caller-allocated array of at least corpus->n_docs BM25Results
 * @return Number of results written (equal to corpus->n_docs)
 */
size_t bm25_rank(const BM25Corpus *corpus,
                 const char **query,
                 size_t n_query,
                 BM25Result *out);

/**
 * Return the top-k documents for a query (shortcut for bm25_rank + head).
 *
 * @param corpus    Indexed BM25Corpus
 * @param query     Array of query token strings
 * @param n_query   Number of query tokens
 * @param k         Maximum number of results to return
 * @param out       Caller-allocated array of at least k BM25Results
 * @return Number of results written (min(k, n_docs))
 */
size_t bm25_get_top_k(const BM25Corpus *corpus,
                      const char **query,
                      size_t n_query,
                      size_t k,
                      BM25Result *out);

/* -------------------------------------------------------------------------
 * Individual metric accessors (useful for debugging / analysis)
 * ------------------------------------------------------------------------- */

/**
 * Compute the IDF weight for a term.
 *
 * IDF(t) = log( (N - df(t) + 0.5) / (df(t) + 0.5) + 1 )
 *
 * @param corpus Indexed corpus
 * @param term   Term string
 * @return IDF value, or 0.0 if term not in index
 */
double bm25_idf(const BM25Corpus *corpus, const char *term);

/**
 * Look up the term frequency of a term in a specific document.
 *
 * @param corpus Indexed corpus
 * @param term   Term string
 * @param doc_id Document identifier
 * @return Raw term frequency (count of occurrences), or 0
 */
size_t bm25_tf(const BM25Corpus *corpus, const char *term, size_t doc_id);

#endif /* BM25_H */

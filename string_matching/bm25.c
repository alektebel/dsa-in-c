/**
 * BM25 Ranking Algorithm Implementation
 */

#include "bm25.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

/* -------------------------------------------------------------------------
 * Construction / destruction
 * ------------------------------------------------------------------------- */

BM25Corpus* bm25_create(BM25Params params) {
    // TODO: Allocate and initialise a BM25Corpus
    // 1. malloc a BM25Corpus struct
    // 2. Set params, zero all pointer/count fields
    // 3. Allocate an initial docs array (e.g. capacity 16)
    // 4. Set index_built = false
    // 5. Return the struct (or NULL on malloc failure)
    (void)params;
    return NULL;
}

void bm25_free(BM25Corpus *corpus) {
    // TODO: Release all owned memory
    // 1. if (!corpus) return
    // 2. For each term in corpus->terms: free the term string
    // 3. free(corpus->terms)
    // 4. free(corpus->df)
    // 5. For each term i: free(corpus->postings[i])
    // 6. free(corpus->postings), free(corpus->postings_len)
    // 7. free(corpus->docs)   ← the BM25Document structs themselves
    //    (caller owns the token strings inside each doc)
    // 8. free(corpus)
    (void)corpus;
}

/* -------------------------------------------------------------------------
 * Corpus construction
 * ------------------------------------------------------------------------- */

size_t bm25_add_document(BM25Corpus *corpus,
                         const char **tokens,
                         size_t n_tokens) {
    // TODO: Append a new document to corpus->docs
    // 1. Validate inputs (corpus, tokens, n_tokens > 0)
    // 2. Grow corpus->docs if n_docs == docs_cap (realloc, double capacity)
    // 3. Fill the new BM25Document: tokens, n_tokens, doc_id = n_docs
    // 4. corpus->n_docs++
    // 5. Return the assigned doc_id
    // 6. Return SIZE_MAX on any failure
    (void)corpus;
    (void)tokens;
    (void)n_tokens;
    return (size_t)-1;
}

bool bm25_build_index(BM25Corpus *corpus) {
    // TODO: Build the inverted index from all added documents
    //
    // High-level steps:
    // 1. Collect all unique terms across all documents
    //    - Iterate corpus->docs[i].tokens for all i
    //    - Use a sorted array or hash map to track unique terms
    //    - corpus->terms = sorted array of strdup'd unique term strings
    //    - corpus->n_terms = number of unique terms
    //
    // 2. Allocate and zero arrays:
    //    corpus->df           = calloc(n_terms, sizeof(size_t))
    //    corpus->postings     = calloc(n_terms, sizeof(BM25Posting*))
    //    corpus->postings_len = calloc(n_terms, sizeof(size_t))
    //
    // 3. For each document d:
    //    For each token t in document d:
    //      a. Binary-search corpus->terms for t → term index idx
    //      b. Check if (d, idx) already has a posting (avoid double-counting df):
    //         - If not yet seen for this doc: corpus->df[idx]++
    //         - Append/update posting: { doc_id=d, tf++ } in postings[idx]
    //
    // 4. Compute average document length:
    //    avg_doc_len = sum(docs[i].n_tokens for all i) / n_docs
    //
    // 5. corpus->index_built = true; return true
    (void)corpus;
    return false;
}

/* -------------------------------------------------------------------------
 * Internal: binary search for a term in the sorted terms array
 * Returns the index, or SIZE_MAX if not found.
 * ------------------------------------------------------------------------- */
static size_t find_term(const BM25Corpus *corpus, const char *term) {
    // TODO: Binary search corpus->terms[0..n_terms) for term
    // Use strcmp for comparison
    // Return index on hit, SIZE_MAX on miss
    (void)corpus;
    (void)term;
    return (size_t)-1;
}

/* -------------------------------------------------------------------------
 * Scoring
 * ------------------------------------------------------------------------- */

double bm25_idf(const BM25Corpus *corpus, const char *term) {
    // TODO: Compute IDF(t) = log((N - df(t) + 0.5) / (df(t) + 0.5) + 1)
    // 1. idx = find_term(corpus, term); if idx == SIZE_MAX return 0.0
    // 2. df_t = corpus->df[idx]
    // 3. N    = corpus->n_docs
    // 4. return log((N - df_t + 0.5) / (df_t + 0.5) + 1.0)
    (void)corpus;
    (void)term;
    return 0.0;
}

size_t bm25_tf(const BM25Corpus *corpus, const char *term, size_t doc_id) {
    // TODO: Look up raw term frequency of term in document doc_id
    // 1. idx = find_term(corpus, term); if SIZE_MAX return 0
    // 2. Linear scan or binary search postings[idx] for doc_id
    // 3. Return the tf field of the matching posting, or 0 if not present
    (void)corpus;
    (void)term;
    (void)doc_id;
    return 0;
}

double bm25_score_term(const BM25Corpus *corpus,
                       const char *term,
                       size_t doc_id) {
    // TODO: Compute the BM25 contribution of one query term for one document
    //
    // Formula:
    //   idf = bm25_idf(corpus, term)
    //   tf  = (double)bm25_tf(corpus, term, doc_id)
    //   dl  = (double)corpus->docs[doc_id].n_tokens
    //   k1  = corpus->params.k1
    //   b   = corpus->params.b
    //   avgdl = corpus->avg_doc_len
    //
    //   numerator   = tf * (k1 + 1)
    //   denominator = tf + k1 * (1 - b + b * dl / avgdl)
    //
    //   return idf * numerator / denominator
    (void)corpus;
    (void)term;
    (void)doc_id;
    return 0.0;
}

double bm25_score(const BM25Corpus *corpus,
                  const char **query,
                  size_t n_query,
                  size_t doc_id) {
    // TODO: Sum bm25_score_term over all query tokens
    // score = 0
    // For each query[i]: score += bm25_score_term(corpus, query[i], doc_id)
    // Return score
    (void)corpus;
    (void)query;
    (void)n_query;
    (void)doc_id;
    return 0.0;
}

/* -------------------------------------------------------------------------
 * Ranking helpers
 * ------------------------------------------------------------------------- */

/** qsort comparator: descending order by BM25Result.score */
static int cmp_result_desc(const void *a, const void *b) {
    // TODO: Compare two BM25Result pointers by descending score
    // Cast a and b to const BM25Result*
    // Return positive if a->score < b->score (descending)
    (void)a;
    (void)b;
    return 0;
}

size_t bm25_rank(const BM25Corpus *corpus,
                 const char **query,
                 size_t n_query,
                 BM25Result *out) {
    // TODO: Score every document and return them sorted by descending BM25 score
    // 1. Validate inputs; return 0 on invalid or !corpus->index_built
    // 2. For i in [0, n_docs):
    //      out[i].doc_id = i
    //      out[i].score  = bm25_score(corpus, query, n_query, i)
    // 3. qsort(out, n_docs, sizeof(BM25Result), cmp_result_desc)
    // 4. Return corpus->n_docs
    (void)corpus;
    (void)query;
    (void)n_query;
    (void)out;
    return 0;
}

size_t bm25_get_top_k(const BM25Corpus *corpus,
                      const char **query,
                      size_t n_query,
                      size_t k,
                      BM25Result *out) {
    // TODO: Return the top-k results
    // 1. Allocate a temporary BM25Result array of size n_docs
    // 2. bm25_rank(corpus, query, n_query, tmp)
    // 3. Copy min(k, n_docs) results into out
    // 4. Free the temporary array
    // 5. Return the number of results copied
    (void)corpus;
    (void)query;
    (void)n_query;
    (void)k;
    (void)out;
    return 0;
}

/**
 * Product Quantization (PQ) Implementation
 *
 * Product Quantization compresses high-dimensional vectors by splitting them
 * into M sub-vectors and quantizing each sub-vector independently with a
 * small codebook learned via k-means.  This allows storing large datasets
 * compactly and computing approximate distances using lookup tables.
 * Used extensively in:
 * - Large-scale approximate nearest neighbor (ANN) search (FAISS, ScaNN)
 * - Vector compression in retrieval systems
 * - Combined with IVF to form IVFPQ indexes
 * - Mobile and edge AI inference (weight quantization)
 */

#ifndef PRODUCT_QUANTIZATION_H
#define PRODUCT_QUANTIZATION_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// Codebook for a single sub-quantizer
typedef struct {
    double **codewords;   // codewords[i] is the i-th centroid (sub_dim-dimensional)
    size_t n_codewords;   // Number of codewords (typically 256 for uint8 codes)
    size_t sub_dim;       // Dimensionality of each sub-vector
} PQSubQuantizer;

// Product Quantizer structure
typedef struct {
    PQSubQuantizer *sub_quantizers;  // Array of M sub-quantizers
    size_t M;                        // Number of sub-quantizers (sub-spaces)
    size_t dim;                      // Full vector dimensionality (must be divisible by M)
    size_t sub_dim;                  // dim / M
    size_t n_codewords;              // Codewords per sub-quantizer (Ks; typically 256)
    bool is_trained;                 // Whether the quantizer has been trained
} ProductQuantizer;

// A PQ-encoded vector: M bytes, one code per sub-quantizer (for n_codewords <= 256)
typedef struct {
    uint8_t *codes;       // Array of M codes
    size_t id;            // Original vector ID
    void *data;           // Optional associated data
} PQCode;

// Result from PQ search
typedef struct {
    size_t id;            // ID of the result vector
    void *data;           // Associated data
    float distance;       // Approximate distance to query
} PQResult;

/**
 * Create a new product quantizer
 * @param dim Full vector dimensionality
 * @param M Number of sub-quantizers (sub-spaces); dim must be divisible by M
 * @param n_codewords Number of codewords per sub-quantizer (typically 256)
 * @return Pointer to the newly created quantizer, or NULL on failure
 */
ProductQuantizer* pq_create(size_t dim, size_t M, size_t n_codewords);

/**
 * Free all memory associated with a product quantizer
 * @param pq The product quantizer to destroy
 */
void pq_destroy(ProductQuantizer *pq);

/**
 * Train the product quantizer by running k-means on each sub-space
 * @param pq The product quantizer
 * @param vectors Training vectors (n_train x dim)
 * @param n_train Number of training vectors
 * @param max_iter Maximum k-means iterations per sub-quantizer
 * @return true if training was successful, false otherwise
 */
bool pq_train(ProductQuantizer *pq, double **vectors, size_t n_train,
              size_t max_iter);

/**
 * Encode a single vector into M sub-quantizer codes
 * @param pq Trained product quantizer
 * @param vector Input vector (dim-dimensional)
 * @param id Caller-assigned identifier
 * @param data Optional associated data
 * @return Newly allocated PQCode, or NULL on failure; caller must free with
 *         pq_code_free()
 */
PQCode* pq_encode(const ProductQuantizer *pq, const double *vector,
                  size_t id, void *data);

/**
 * Encode multiple vectors in a batch
 * @param pq Trained product quantizer
 * @param vectors Array of vectors to encode
 * @param ids Array of caller-assigned identifiers
 * @param data Array of associated data pointers (may be NULL)
 * @param n_vectors Number of vectors to encode
 * @param codes_out Caller-allocated array of PQCode pointers (size n_vectors)
 * @return Number of vectors successfully encoded
 */
size_t pq_encode_batch(const ProductQuantizer *pq, double **vectors,
                       const size_t *ids, void **data, size_t n_vectors,
                       PQCode **codes_out);

/**
 * Decode a PQ code back to an approximate vector
 * @param pq Trained product quantizer
 * @param code PQ code to decode
 * @param vector_out Output buffer (dim-dimensional; caller-allocated)
 */
void pq_decode(const ProductQuantizer *pq, const PQCode *code,
               double *vector_out);

/**
 * Compute a distance lookup table for a query vector
 *
 * The lookup table lut[m][c] stores the distance between the query's m-th
 * sub-vector and codeword c of sub-quantizer m.  Given this table, the
 * approximate distance to a PQ-encoded database vector can be computed in O(M)
 * by summing lut[m][code[m]] for m = 0 … M-1.
 *
 * @param pq Trained product quantizer
 * @param query Query vector (dim-dimensional)
 * @param lut Output table of size M x n_codewords (caller-allocated)
 */
void pq_compute_distance_table(const ProductQuantizer *pq, const double *query,
                                float **lut);

/**
 * Compute the approximate distance from a query to a PQ-encoded vector
 * using a precomputed distance lookup table
 * @param pq The product quantizer
 * @param code Encoded database vector
 * @param lut Precomputed distance lookup table (from pq_compute_distance_table)
 * @return Approximate distance
 */
float pq_asymmetric_distance(const ProductQuantizer *pq, const PQCode *code,
                              float * const *lut);

/**
 * Search a set of PQ-encoded vectors for the k nearest neighbors
 * @param pq Trained product quantizer
 * @param query Query vector
 * @param codes Array of encoded database vectors
 * @param n_codes Number of encoded vectors
 * @param k Number of nearest neighbors to return
 * @param results Caller-allocated array of at least k elements
 * @return Number of results returned
 */
size_t pq_search(const ProductQuantizer *pq, const double *query,
                 PQCode * const *codes, size_t n_codes, size_t k,
                 PQResult *results);

/**
 * Free a PQCode allocated by pq_encode()
 * @param code The PQCode to free
 */
void pq_code_free(PQCode *code);

#endif // PRODUCT_QUANTIZATION_H

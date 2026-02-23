/**
 * Product Quantization (PQ) Implementation
 */

#include "product_quantization.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

ProductQuantizer* pq_create(size_t dim, size_t M, size_t n_codewords) {
    if (dim == 0 || M == 0 || n_codewords == 0 || dim % M != 0) return NULL;

    ProductQuantizer *pq = (ProductQuantizer*)malloc(sizeof(ProductQuantizer));
    if (!pq) return NULL;

    pq->dim = dim;
    pq->M = M;
    pq->sub_dim = dim / M;
    pq->n_codewords = n_codewords;
    pq->is_trained = false;

    pq->sub_quantizers = (PQSubQuantizer*)calloc(M, sizeof(PQSubQuantizer));
    if (!pq->sub_quantizers) {
        free(pq);
        return NULL;
    }

    for (size_t m = 0; m < M; m++) {
        pq->sub_quantizers[m].sub_dim = pq->sub_dim;
        pq->sub_quantizers[m].n_codewords = n_codewords;
        pq->sub_quantizers[m].codewords = (double**)calloc(n_codewords, sizeof(double*));
        if (!pq->sub_quantizers[m].codewords) {
            /* clean up already-allocated sub-quantizers */
            for (size_t j = 0; j < m; j++) {
                for (size_t c = 0; c < n_codewords; c++) {
                    free(pq->sub_quantizers[j].codewords[c]);
                }
                free(pq->sub_quantizers[j].codewords);
            }
            free(pq->sub_quantizers);
            free(pq);
            return NULL;
        }
        for (size_t c = 0; c < n_codewords; c++) {
            pq->sub_quantizers[m].codewords[c] =
                (double*)calloc(pq->sub_dim, sizeof(double));
            if (!pq->sub_quantizers[m].codewords[c]) {
                /* clean up partially-allocated codewords */
                for (size_t ci = 0; ci < c; ci++) {
                    free(pq->sub_quantizers[m].codewords[ci]);
                }
                free(pq->sub_quantizers[m].codewords);
                for (size_t j = 0; j < m; j++) {
                    for (size_t ci = 0; ci < n_codewords; ci++) {
                        free(pq->sub_quantizers[j].codewords[ci]);
                    }
                    free(pq->sub_quantizers[j].codewords);
                }
                free(pq->sub_quantizers);
                free(pq);
                return NULL;
            }
        }
    }

    return pq;
}

void pq_destroy(ProductQuantizer *pq) {
    if (!pq) return;

    for (size_t m = 0; m < pq->M; m++) {
        for (size_t c = 0; c < pq->n_codewords; c++) {
            free(pq->sub_quantizers[m].codewords[c]);
        }
        free(pq->sub_quantizers[m].codewords);
    }
    free(pq->sub_quantizers);
    free(pq);
}

bool pq_train(ProductQuantizer *pq, double **vectors, size_t n_train,
              size_t max_iter) {
    // TODO: Train each sub-quantizer independently using k-means
    // For sub-quantizer m (m = 0 … M-1):
    //   1. Extract the m-th sub-vector from every training vector
    //      (offset = m * sub_dim, length = sub_dim)
    //   2. Run k-means with n_codewords centroids for up to max_iter iterations
    //   3. Store the resulting centroids in sub_quantizers[m].codewords
    // After all M sub-quantizers are trained, set is_trained = true
    (void)pq;
    (void)vectors;
    (void)n_train;
    (void)max_iter;
    return false;
}

PQCode* pq_encode(const ProductQuantizer *pq, const double *vector,
                  size_t id, void *data) {
    // TODO: Assign each sub-vector to its nearest codeword
    // For m = 0 … M-1:
    //   1. Extract sub-vector: vector + m * sub_dim
    //   2. Find nearest codeword in sub_quantizers[m] (argmin over Euclidean dist)
    //   3. Store the index as codes[m]
    (void)pq;
    (void)vector;
    (void)id;
    (void)data;
    return NULL;
}

size_t pq_encode_batch(const ProductQuantizer *pq, double **vectors,
                       const size_t *ids, void **data, size_t n_vectors,
                       PQCode **codes_out) {
    // TODO: Call pq_encode() for each vector
    (void)pq;
    (void)vectors;
    (void)ids;
    (void)data;
    (void)n_vectors;
    (void)codes_out;
    return 0;
}

void pq_decode(const ProductQuantizer *pq, const PQCode *code,
               double *vector_out) {
    // TODO: Reconstruct approximate vector from codes
    // For m = 0 … M-1:
    //   Copy sub_quantizers[m].codewords[code->codes[m]] into
    //   vector_out + m * sub_dim
    (void)pq;
    (void)code;
    (void)vector_out;
}

void pq_compute_distance_table(const ProductQuantizer *pq, const double *query,
                                float **lut) {
    // TODO: Compute distance from each sub-vector of query to every codeword
    // For m = 0 … M-1:
    //   query_sub = query + m * sub_dim
    //   For c = 0 … n_codewords-1:
    //     lut[m][c] = squared_euclidean(query_sub, sub_quantizers[m].codewords[c])
    (void)pq;
    (void)query;
    (void)lut;
}

float pq_asymmetric_distance(const ProductQuantizer *pq, const PQCode *code,
                              float * const *lut) {
    // TODO: Sum precomputed distances for each sub-code
    // dist = sum_{m=0}^{M-1} lut[m][code->codes[m]]
    (void)pq;
    (void)code;
    (void)lut;
    return 0.0f;
}

size_t pq_search(const ProductQuantizer *pq, const double *query,
                 PQCode * const *codes, size_t n_codes, size_t k,
                 PQResult *results) {
    // TODO: Search encoded database vectors
    // 1. Compute distance lookup table with pq_compute_distance_table()
    // 2. For each encoded vector compute approximate distance with
    //    pq_asymmetric_distance()
    // 3. Maintain a max-heap of size k; return the k closest
    (void)pq;
    (void)query;
    (void)codes;
    (void)n_codes;
    (void)k;
    (void)results;
    return 0;
}

void pq_code_free(PQCode *code) {
    if (!code) return;
    free(code->codes);
    free(code);
}

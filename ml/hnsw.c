/**
 * HNSW (Hierarchical Navigable Small World) Graph Implementation
 */

#include "hnsw.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

HNSW* hnsw_create(size_t dim, size_t M, size_t ef_construction) {
    if (dim == 0 || M == 0 || ef_construction == 0) return NULL;

    HNSW *hnsw = (HNSW*)malloc(sizeof(HNSW));
    if (!hnsw) return NULL;

    hnsw->dim = dim;
    hnsw->M = M;
    hnsw->M0 = 2 * M;
    hnsw->ef_construction = ef_construction;
    hnsw->ef_search = ef_construction;
    hnsw->ml = 1.0 / log((double)M);
    hnsw->n_nodes = 0;
    hnsw->capacity = 0;
    hnsw->nodes = NULL;
    hnsw->entry_point = 0;
    hnsw->max_layer = 0;

    return hnsw;
}

void hnsw_destroy(HNSW *hnsw) {
    if (!hnsw) return;

    for (size_t i = 0; i < hnsw->n_nodes; i++) {
        HNSWNode *node = hnsw->nodes[i];
        if (node) {
            free(node->vector);
            if (node->neighbors) {
                for (size_t l = 0; l < node->n_layers; l++) {
                    free(node->neighbors[l]);
                }
                free(node->neighbors);
            }
            free(node->n_neighbors);
            free(node);
        }
    }
    free(hnsw->nodes);
    free(hnsw);
}

size_t hnsw_insert(HNSW *hnsw, const double *vector, void *data) {
    // TODO: Implement HNSW insert algorithm (Algorithm 1 from the paper)
    // 1. Draw the node's maximum layer l from a geometric distribution:
    //       l = floor(-ln(uniform(0,1)) * ml)
    // 2. Find the entry point by greedily descending from max_layer down to l+1
    // 3. For layers l down to 0:
    //    a. Use ef_construction-sized beam search to find candidates
    //    b. Select M (or M0 for layer 0) neighbors using a heuristic
    //    c. Add bidirectional connections; prune neighbors that exceed M/M0
    // 4. If l > max_layer, update entry_point and max_layer
    (void)hnsw;
    (void)vector;
    (void)data;
    return (size_t)-1;
}

size_t hnsw_search(const HNSW *hnsw, const double *query, size_t k,
                   size_t ef, HNSWResult *results) {
    // TODO: Implement HNSW search algorithm (Algorithm 5 from the paper)
    // 1. Start from entry_point at max_layer
    // 2. Greedily descend from max_layer to layer 1 using greedy search (ef=1)
    // 3. At layer 0 perform beam search with ef candidates
    // 4. Return the k closest candidates from the result set
    (void)hnsw;
    (void)query;
    (void)k;
    (void)ef;
    (void)results;
    return 0;
}

void hnsw_set_ef(HNSW *hnsw, size_t ef) {
    if (!hnsw || ef == 0) return;
    hnsw->ef_search = ef;
}

size_t hnsw_size(const HNSW *hnsw) {
    if (!hnsw) return 0;
    return hnsw->n_nodes;
}

double hnsw_distance_l2(const double *a, const double *b, size_t dim) {
    double dist = 0.0;
    for (size_t i = 0; i < dim; i++) {
        double diff = a[i] - b[i];
        dist += diff * diff;
    }
    return dist;
}

double hnsw_distance_ip(const double *a, const double *b, size_t dim) {
    double dot = 0.0;
    for (size_t i = 0; i < dim; i++) {
        dot += a[i] * b[i];
    }
    return -dot;
}

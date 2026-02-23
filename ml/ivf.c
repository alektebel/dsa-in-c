/**
 * IVF (Inverted File Index) Implementation
 */

#include "ivf.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

IVFIndex* ivf_create(size_t dim, size_t n_lists, size_t nprobe,
                     bool store_vectors) {
    if (dim == 0 || n_lists == 0 || nprobe == 0) return NULL;

    IVFIndex *index = (IVFIndex*)malloc(sizeof(IVFIndex));
    if (!index) return NULL;

    index->lists = (IVFList*)calloc(n_lists, sizeof(IVFList));
    if (!index->lists) {
        free(index);
        return NULL;
    }

    for (size_t i = 0; i < n_lists; i++) {
        index->lists[i].centroid = (double*)calloc(dim, sizeof(double));
        if (!index->lists[i].centroid) {
            /* clean up already allocated centroids */
            for (size_t j = 0; j < i; j++) {
                free(index->lists[j].centroid);
            }
            free(index->lists);
            free(index);
            return NULL;
        }
        index->lists[i].entries = NULL;
        index->lists[i].n_entries = 0;
        index->lists[i].capacity = 0;
    }

    index->dim = dim;
    index->n_lists = n_lists;
    index->n_vectors = 0;
    index->nprobe = (nprobe <= n_lists) ? nprobe : n_lists;
    index->store_vectors = store_vectors;

    return index;
}

void ivf_destroy(IVFIndex *index) {
    if (!index) return;

    for (size_t i = 0; i < index->n_lists; i++) {
        free(index->lists[i].centroid);
        if (index->lists[i].entries) {
            if (index->store_vectors) {
                for (size_t j = 0; j < index->lists[i].n_entries; j++) {
                    free(index->lists[i].entries[j].vector);
                }
            }
            free(index->lists[i].entries);
        }
    }
    free(index->lists);
    free(index);
}

bool ivf_train(IVFIndex *index, double **vectors, size_t n_train,
               size_t max_iter) {
    // TODO: Train the IVF index using k-means clustering
    // 1. Initialize centroids (e.g., pick n_lists random vectors from training set)
    // 2. Repeat for max_iter iterations:
    //    a. Assign each vector to its nearest centroid
    //    b. Recompute each centroid as the mean of assigned vectors
    //    c. Stop early if centroids did not change significantly
    (void)index;
    (void)vectors;
    (void)n_train;
    (void)max_iter;
    return false;
}

bool ivf_add(IVFIndex *index, const double *vector, size_t id, void *data) {
    // TODO: Assign vector to its nearest centroid and append to that list
    // 1. Find the nearest centroid using ivf_nearest_centroid()
    // 2. Grow the posting list if needed (realloc)
    // 3. Append an IVFEntry with the given id, vector (if store_vectors), and data
    (void)index;
    (void)vector;
    (void)id;
    (void)data;
    return false;
}

size_t ivf_add_batch(IVFIndex *index, double **vectors, const size_t *ids,
                     void **data, size_t n_vectors) {
    // TODO: Call ivf_add() for each vector in the batch
    (void)index;
    (void)vectors;
    (void)ids;
    (void)data;
    (void)n_vectors;
    return 0;
}

size_t ivf_search(const IVFIndex *index, const double *query, size_t k,
                  IVFResult *results) {
    // TODO: Approximate nearest neighbor search
    // 1. Compute distance from query to all centroids
    // 2. Sort/partial-sort to find the nprobe nearest centroids
    // 3. Scan vectors in those nprobe lists, tracking the k closest overall
    //    (use a max-heap of size k for efficiency)
    // 4. Return results sorted by ascending distance
    (void)index;
    (void)query;
    (void)k;
    (void)results;
    return 0;
}

void ivf_set_nprobe(IVFIndex *index, size_t nprobe) {
    if (!index || nprobe == 0) return;
    index->nprobe = (nprobe <= index->n_lists) ? nprobe : index->n_lists;
}

size_t ivf_nearest_centroid(const IVFIndex *index, const double *vector) {
    // TODO: Return index of nearest centroid using Euclidean distance
    (void)index;
    (void)vector;
    return 0;
}

size_t ivf_size(const IVFIndex *index) {
    if (!index) return 0;
    return index->n_vectors;
}

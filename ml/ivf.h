/**
 * IVF (Inverted File Index) Implementation
 *
 * An Inverted File Index partitions the vector space into Voronoi cells using
 * k-means clustering, then assigns each vector to its nearest cluster centroid.
 * At query time only a small number of cells (nprobe) are searched, enabling
 * fast approximate nearest-neighbor search over large datasets.
 * Used extensively in:
 * - Large-scale approximate nearest neighbor (ANN) search
 * - Vector databases (FAISS, Milvus, Weaviate)
 * - Image and document retrieval
 * - Recommendation systems
 */

#ifndef IVF_H
#define IVF_H

#include <stddef.h>
#include <stdbool.h>

// A single entry stored in an inverted list
typedef struct {
    size_t id;                   // Original vector ID
    double *vector;              // The stored vector (may be NULL if only IDs kept)
    void *data;                  // Optional associated data
} IVFEntry;

// One Voronoi cell / posting list
typedef struct {
    double *centroid;            // Cluster centroid
    IVFEntry *entries;           // Vectors assigned to this cell
    size_t n_entries;            // Number of entries in this cell
    size_t capacity;             // Allocated capacity for entries
} IVFList;

// IVF index structure
typedef struct {
    IVFList *lists;              // Array of inverted lists (one per cluster)
    size_t n_lists;              // Number of clusters (nlist)
    size_t dim;                  // Vector dimensionality
    size_t n_vectors;            // Total number of indexed vectors
    size_t nprobe;               // Number of cells to search at query time
    bool store_vectors;          // Whether to store raw vectors in the index
} IVFIndex;

// Nearest neighbor result
typedef struct {
    size_t id;                   // ID of the result vector
    double *vector;              // Pointer to the result vector (may be NULL)
    void *data;                  // Associated data
    double distance;             // Distance to query vector
} IVFResult;

/**
 * Create a new IVF index
 * @param dim Vector dimensionality
 * @param n_lists Number of Voronoi cells (clusters)
 * @param nprobe Number of nearest cells to search at query time
 * @param store_vectors Whether to store raw vectors inside the index
 * @return Pointer to the newly created IVF index, or NULL on failure
 */
IVFIndex* ivf_create(size_t dim, size_t n_lists, size_t nprobe,
                     bool store_vectors);

/**
 * Free all memory associated with an IVF index
 * @param index The IVF index to destroy
 */
void ivf_destroy(IVFIndex *index);

/**
 * Train the IVF index by running k-means on the provided vectors to compute
 * cluster centroids
 * @param index The IVF index (must be empty)
 * @param vectors Training vectors (n_train x dim)
 * @param n_train Number of training vectors
 * @param max_iter Maximum number of k-means iterations
 * @return true if training was successful, false otherwise
 */
bool ivf_train(IVFIndex *index, double **vectors, size_t n_train,
               size_t max_iter);

/**
 * Add a single vector to the index
 * @param index The IVF index (must be trained)
 * @param vector Vector to add (dim-dimensional)
 * @param id Caller-assigned identifier for this vector
 * @param data Optional associated data pointer
 * @return true if addition was successful, false otherwise
 */
bool ivf_add(IVFIndex *index, const double *vector, size_t id, void *data);

/**
 * Add multiple vectors to the index in a single batch
 * @param index The IVF index (must be trained)
 * @param vectors Array of vectors to add
 * @param ids Array of caller-assigned identifiers (one per vector)
 * @param data Array of associated data pointers (may be NULL)
 * @param n_vectors Number of vectors to add
 * @return Number of vectors successfully added
 */
size_t ivf_add_batch(IVFIndex *index, double **vectors, const size_t *ids,
                     void **data, size_t n_vectors);

/**
 * Search for the k nearest neighbors of a query vector
 * @param index The IVF index
 * @param query Query vector (dim-dimensional)
 * @param k Number of nearest neighbors to return
 * @param results Caller-allocated array of at least k elements
 * @return Number of results returned
 */
size_t ivf_search(const IVFIndex *index, const double *query, size_t k,
                  IVFResult *results);

/**
 * Set the nprobe parameter (number of cells searched per query)
 * @param index The IVF index
 * @param nprobe New nprobe value (must be in [1, n_lists])
 */
void ivf_set_nprobe(IVFIndex *index, size_t nprobe);

/**
 * Find the index of the nearest centroid to a given vector
 * @param index The IVF index (must be trained)
 * @param vector Query vector
 * @return Index of the nearest centroid
 */
size_t ivf_nearest_centroid(const IVFIndex *index, const double *vector);

/**
 * Get the total number of vectors stored in the index
 * @param index The IVF index
 * @return Total number of indexed vectors
 */
size_t ivf_size(const IVFIndex *index);

#endif // IVF_H

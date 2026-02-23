/**
 * HNSW (Hierarchical Navigable Small World) Graph Implementation
 *
 * HNSW is a graph-based approximate nearest neighbor search algorithm that
 * builds a hierarchical, multi-layer graph where each layer is a navigable
 * small world graph.
 * Used extensively in:
 * - Approximate nearest neighbor (ANN) search
 * - Semantic search and vector databases
 * - Recommendation systems
 * - Image and document retrieval
 *
 * Key properties:
 * - O(log n) search time
 * - Excellent recall/speed tradeoff
 * - Supports incremental insertion
 */

#ifndef HNSW_H
#define HNSW_H

#include <stddef.h>
#include <stdbool.h>

// A single node in the HNSW graph
typedef struct HNSWNode {
    double *vector;                // High-dimensional vector
    void *data;                    // Optional associated data
    size_t id;                     // Unique node identifier
    size_t n_layers;               // Number of layers this node participates in
    size_t **neighbors;            // neighbors[layer] = array of neighbor node IDs
    size_t *n_neighbors;           // n_neighbors[layer] = number of neighbors in layer
} HNSWNode;

// Candidate entry used during search (priority queue element)
typedef struct {
    size_t node_id;
    double distance;
} HNSWCandidate;

// HNSW graph structure
typedef struct {
    HNSWNode **nodes;              // Array of all nodes
    size_t n_nodes;                // Current number of inserted nodes
    size_t capacity;               // Allocated capacity
    size_t dim;                    // Vector dimensionality
    size_t M;                      // Max neighbors per node per layer
    size_t M0;                     // Max neighbors in layer 0 (typically 2*M)
    size_t ef_construction;        // Size of dynamic candidate list during build
    size_t ef_search;              // Size of dynamic candidate list during search
    double ml;                     // Level generation factor (1 / ln(M))
    size_t entry_point;            // ID of the current entry-point node
    size_t max_layer;              // Current maximum layer index
} HNSW;

// Nearest neighbor result
typedef struct {
    size_t node_id;                // ID of the found node
    double *vector;                // Pointer to the found vector
    void *data;                    // Associated data
    double distance;               // Distance to the query vector
} HNSWResult;

/**
 * Create a new HNSW graph
 * @param dim Vector dimensionality
 * @param M Maximum number of established connections per element per layer
 * @param ef_construction Size of the dynamic candidate list during construction
 * @return Pointer to the newly created HNSW graph, or NULL on failure
 */
HNSW* hnsw_create(size_t dim, size_t M, size_t ef_construction);

/**
 * Free all memory associated with an HNSW graph
 * @param hnsw The graph to destroy
 */
void hnsw_destroy(HNSW *hnsw);

/**
 * Insert a vector into the HNSW graph
 * @param hnsw The HNSW graph
 * @param vector Vector to insert (copied internally)
 * @param data Optional associated data pointer
 * @return Node ID assigned to the inserted vector, or (size_t)-1 on failure
 */
size_t hnsw_insert(HNSW *hnsw, const double *vector, void *data);

/**
 * Search for the k nearest neighbors of a query vector
 * @param hnsw The HNSW graph
 * @param query Query vector
 * @param k Number of nearest neighbors to return
 * @param ef Search-time candidate list size (>=k; larger = better recall)
 * @param results Caller-allocated array of at least k elements
 * @return Number of results returned (may be less than k if graph is small)
 */
size_t hnsw_search(const HNSW *hnsw, const double *query, size_t k,
                   size_t ef, HNSWResult *results);

/**
 * Set the ef parameter used during search
 * @param hnsw The HNSW graph
 * @param ef New ef_search value (must be >= 1)
 */
void hnsw_set_ef(HNSW *hnsw, size_t ef);

/**
 * Get the number of vectors stored in the graph
 * @param hnsw The HNSW graph
 * @return Number of inserted vectors
 */
size_t hnsw_size(const HNSW *hnsw);

/**
 * Compute the Euclidean (L2) distance between two vectors
 * @param a First vector
 * @param b Second vector
 * @param dim Dimensionality
 * @return Squared Euclidean distance
 */
double hnsw_distance_l2(const double *a, const double *b, size_t dim);

/**
 * Compute the inner product distance between two vectors
 * @param a First vector
 * @param b Second vector
 * @param dim Dimensionality
 * @return Negative inner product (so that smaller = more similar)
 */
double hnsw_distance_ip(const double *a, const double *b, size_t dim);

#endif // HNSW_H

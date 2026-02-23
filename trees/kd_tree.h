/**
 * KD Tree Implementation
 *
 * A k-d tree (k-dimensional tree) is a space-partitioning data structure for
 * organizing points in k-dimensional space.
 * Used extensively in:
 * - Nearest neighbor search
 * - Range queries
 * - Computational geometry
 * - Machine learning (KNN classifier/regressor)
 */

#ifndef KD_TREE_H
#define KD_TREE_H

#include <stddef.h>
#include <stdbool.h>

// KD tree node
typedef struct KDNode {
    double *point;             // k-dimensional point stored in this node
    void *data;                // Optional associated data
    int split_dim;             // Dimension used to split at this node
    struct KDNode *left;       // Points with smaller value in split dimension
    struct KDNode *right;      // Points with larger value in split dimension
} KDNode;

// KD tree structure
typedef struct {
    KDNode *root;
    size_t k;                  // Number of dimensions
    size_t size;               // Number of points in the tree
} KDTree;

// Result for nearest neighbor search
typedef struct {
    double *point;             // Nearest point found
    void *data;                // Associated data
    double distance;           // Distance to the nearest point
} KDNearest;

/**
 * Create a new KD tree
 * @param k Number of dimensions
 * @return Pointer to the newly created KD tree, or NULL on failure
 */
KDTree* kd_tree_create(size_t k);

/**
 * Insert a point into the KD tree
 * @param tree The KD tree
 * @param point k-dimensional point to insert (copied internally)
 * @param data Optional associated data
 * @return true if insertion was successful, false otherwise
 */
bool kd_tree_insert(KDTree *tree, const double *point, void *data);

/**
 * Build a balanced KD tree from an array of points
 * @param tree The KD tree (must be empty)
 * @param points Array of k-dimensional points
 * @param data  Array of associated data pointers (may be NULL)
 * @param n_points Number of points
 * @return true if build was successful, false otherwise
 */
bool kd_tree_build(KDTree *tree, double **points, void **data, size_t n_points);

/**
 * Search for the nearest neighbor to a query point
 * @param tree The KD tree
 * @param query k-dimensional query point
 * @param result Output structure filled with the nearest neighbor info
 * @return true if a nearest neighbor was found, false if tree is empty
 */
bool kd_tree_nearest(const KDTree *tree, const double *query, KDNearest *result);

/**
 * Find all points within a given radius of a query point
 * @param tree The KD tree
 * @param query k-dimensional query point
 * @param radius Search radius (Euclidean distance)
 * @param results Array to store result nodes (caller-allocated)
 * @param max_results Maximum number of results
 * @return Number of points found within the radius
 */
size_t kd_tree_range_search(const KDTree *tree, const double *query,
                             double radius, KDNearest *results, size_t max_results);

/**
 * Search for an exact point in the KD tree
 * @param tree The KD tree
 * @param point k-dimensional point to search for
 * @return Pointer to the node if found, NULL otherwise
 */
KDNode* kd_tree_search(const KDTree *tree, const double *point);

/**
 * Delete a point from the KD tree
 * @param tree The KD tree
 * @param point k-dimensional point to delete
 * @return true if deletion was successful, false otherwise
 */
bool kd_tree_delete(KDTree *tree, const double *point);

/**
 * Get the number of points in the tree
 * @param tree The KD tree
 * @return Number of points stored in the tree
 */
size_t kd_tree_size(const KDTree *tree);

/**
 * Check if the tree is empty
 * @param tree The KD tree
 * @return true if the tree contains no points, false otherwise
 */
bool kd_tree_is_empty(const KDTree *tree);

/**
 * Destroy the KD tree and free all allocated memory
 * @param tree The KD tree to destroy
 */
void kd_tree_destroy(KDTree *tree);

#endif // KD_TREE_H

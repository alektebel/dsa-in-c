/**
 * Ball Tree Implementation
 *
 * A ball tree is a binary space-partitioning structure that recursively
 * partitions a dataset into two nested hyper-spheres (balls).
 * Used extensively in:
 * - Nearest neighbor search (especially in high dimensions)
 * - Kernel density estimation
 * - N-body simulations
 * - Machine learning (KNN, range queries on metric spaces)
 */

#ifndef BALL_TREE_H
#define BALL_TREE_H

#include <stddef.h>
#include <stdbool.h>

// Ball tree node
typedef struct BallTreeNode {
    double *centroid;              // Center of the bounding ball
    double radius;                 // Radius of the bounding ball
    double **points;               // Points contained in this node (leaf only)
    void **data;                   // Associated data for each point (leaf only)
    size_t n_points;               // Number of points in this node (leaf only)
    struct BallTreeNode *left;     // Left child node
    struct BallTreeNode *right;    // Right child node
} BallTreeNode;

// Ball tree structure
typedef struct {
    BallTreeNode *root;
    size_t k;                      // Number of dimensions
    size_t leaf_size;              // Maximum points per leaf node
    size_t size;                   // Total number of points in the tree
} BallTree;

// Nearest neighbor result
typedef struct {
    double *point;                 // Nearest point found
    void *data;                    // Associated data
    double distance;               // Distance to the nearest point
} BallTreeNearest;

/**
 * Create a new ball tree
 * @param k Number of dimensions
 * @param leaf_size Maximum number of points stored in a leaf node
 * @return Pointer to the newly created ball tree, or NULL on failure
 */
BallTree* ball_tree_create(size_t k, size_t leaf_size);

/**
 * Build the ball tree from an array of points
 * @param tree The ball tree (must be empty)
 * @param points Array of k-dimensional points
 * @param data Array of associated data pointers (may be NULL)
 * @param n_points Number of points
 * @return true if build was successful, false otherwise
 */
bool ball_tree_build(BallTree *tree, double **points, void **data, size_t n_points);

/**
 * Search for the nearest neighbor to a query point
 * @param tree The ball tree
 * @param query k-dimensional query point
 * @param result Output structure filled with nearest neighbor info
 * @return true if a nearest neighbor was found, false if tree is empty
 */
bool ball_tree_nearest(const BallTree *tree, const double *query,
                       BallTreeNearest *result);

/**
 * Find the k nearest neighbors to a query point
 * @param tree The ball tree
 * @param query k-dimensional query point
 * @param k_neighbors Number of nearest neighbors to find
 * @param results Caller-allocated array of at least k_neighbors elements
 * @return Number of neighbors found (may be less than k_neighbors if tree
 *         contains fewer points)
 */
size_t ball_tree_knn(const BallTree *tree, const double *query,
                     size_t k_neighbors, BallTreeNearest *results);

/**
 * Find all points within a given radius of a query point
 * @param tree The ball tree
 * @param query k-dimensional query point
 * @param radius Search radius (Euclidean distance)
 * @param results Caller-allocated array for results
 * @param max_results Maximum number of results to return
 * @return Number of points found within the radius
 */
size_t ball_tree_range_search(const BallTree *tree, const double *query,
                               double radius, BallTreeNearest *results,
                               size_t max_results);

/**
 * Get the total number of points in the tree
 * @param tree The ball tree
 * @return Number of points stored in the tree
 */
size_t ball_tree_size(const BallTree *tree);

/**
 * Check if the tree is empty
 * @param tree The ball tree
 * @return true if the tree contains no points, false otherwise
 */
bool ball_tree_is_empty(const BallTree *tree);

/**
 * Destroy the ball tree and free all allocated memory
 * @param tree The ball tree to destroy
 */
void ball_tree_destroy(BallTree *tree);

#endif // BALL_TREE_H

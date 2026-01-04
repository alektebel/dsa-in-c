/**
 * Interval Tree Implementation
 * 
 * Interval trees are used to efficiently store and query intervals.
 * Common applications include scheduling, computational geometry, and range queries.
 * Each node stores an interval and maintains the maximum endpoint in its subtree.
 */

#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <stdbool.h>
#include <stddef.h>

// Interval structure
typedef struct Interval {
    int low;
    int high;
} Interval;

// Interval tree node
typedef struct IntervalNode {
    Interval interval;              // The interval stored in this node
    int max;                        // Maximum high value in subtree
    struct IntervalNode *left;      // Left child
    struct IntervalNode *right;     // Right child
} IntervalNode;

// Interval tree structure
typedef struct IntervalTree {
    IntervalNode *root;
} IntervalTree;

/**
 * Create a new interval tree
 * @return Pointer to the newly created interval tree
 */
IntervalTree* interval_tree_create(void);

/**
 * Insert an interval into the tree
 * @param tree The interval tree
 * @param low The lower bound of the interval
 * @param high The upper bound of the interval
 * @return true if insertion was successful, false otherwise
 */
bool interval_tree_insert(IntervalTree *tree, int low, int high);

/**
 * Search for an overlapping interval
 * @param tree The interval tree
 * @param low The lower bound of the query interval
 * @param high The upper bound of the query interval
 * @param result Pointer to store the found interval
 * @return true if an overlapping interval is found, false otherwise
 */
bool interval_tree_search_overlap(IntervalTree *tree, int low, int high, 
                                  Interval *result);

/**
 * Find all overlapping intervals
 * @param tree The interval tree
 * @param low The lower bound of the query interval
 * @param high The upper bound of the query interval
 * @param results Array to store the results
 * @param max_results Maximum number of results to return
 * @return Number of overlapping intervals found
 */
int interval_tree_find_all_overlaps(IntervalTree *tree, int low, int high,
                                    Interval *results, int max_results);

/**
 * Delete an interval from the tree
 * @param tree The interval tree
 * @param low The lower bound of the interval to delete
 * @param high The upper bound of the interval to delete
 * @return true if deletion was successful, false otherwise
 */
bool interval_tree_delete(IntervalTree *tree, int low, int high);

/**
 * Destroy the interval tree and free all allocated memory
 * @param tree The interval tree to destroy
 */
void interval_tree_destroy(IntervalTree *tree);

/**
 * Print the interval tree (for debugging)
 * @param tree The interval tree to print
 */
void interval_tree_print(IntervalTree *tree);

#endif // INTERVAL_TREE_H

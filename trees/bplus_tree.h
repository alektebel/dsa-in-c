/**
 * B+ Tree Implementation
 * 
 * B+ Trees are widely used in databases and file systems for indexing.
 * All values are stored in leaf nodes, and internal nodes only store keys for navigation.
 * Leaf nodes are linked together for efficient range queries.
 */

#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H

#include <stdbool.h>
#include <stddef.h>

#define BPLUS_ORDER 4  // Minimum degree (minimum number of keys)

// B+ Tree node structure
typedef struct BPlusNode {
    int *keys;                      // Array of keys
    struct BPlusNode **children;    // Array of child pointers
    struct BPlusNode *next;         // Pointer to next leaf (for leaf nodes)
    int num_keys;                   // Current number of keys
    bool is_leaf;                   // Flag to indicate if node is a leaf
} BPlusNode;

// B+ Tree structure
typedef struct BPlusTree {
    BPlusNode *root;
    int order;                      // Maximum number of children
} BPlusTree;

/**
 * Initialize a new B+ tree
 * @param order The order of the B+ tree
 * @return Pointer to the newly created B+ tree
 */
BPlusTree* bplus_tree_create(int order);

/**
 * Insert a key-value pair into the B+ tree
 * @param tree The B+ tree
 * @param key The key to insert
 * @return true if insertion was successful, false otherwise
 */
bool bplus_tree_insert(BPlusTree *tree, int key);

/**
 * Search for a key in the B+ tree
 * @param tree The B+ tree
 * @param key The key to search for
 * @return true if key exists, false otherwise
 */
bool bplus_tree_search(BPlusTree *tree, int key);

/**
 * Delete a key from the B+ tree
 * @param tree The B+ tree
 * @param key The key to delete
 * @return true if deletion was successful, false otherwise
 */
bool bplus_tree_delete(BPlusTree *tree, int key);

/**
 * Perform a range query on the B+ tree
 * @param tree The B+ tree
 * @param start_key The start of the range
 * @param end_key The end of the range
 * @param result Array to store the results
 * @param max_results Maximum number of results to return
 * @return Number of keys found in the range
 */
int bplus_tree_range_query(BPlusTree *tree, int start_key, int end_key, 
                           int *result, int max_results);

/**
 * Destroy the B+ tree and free all allocated memory
 * @param tree The B+ tree to destroy
 */
void bplus_tree_destroy(BPlusTree *tree);

/**
 * Print the B+ tree structure (for debugging)
 * @param tree The B+ tree to print
 */
void bplus_tree_print(BPlusTree *tree);

#endif // BPLUS_TREE_H

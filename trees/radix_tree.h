/**
 * Radix Tree (Patricia Trie) Implementation
 * 
 * Radix trees are space-optimized prefix trees used for:
 * - IP routing tables
 * - Memory management
 * - File system paths
 * - String matching and prefix searches
 */

#ifndef RADIX_TREE_H
#define RADIX_TREE_H

#include <stdbool.h>
#include <stddef.h>

// Radix tree node
typedef struct RadixNode {
    char *key;                      // Key fragment stored in this node
    void *value;                    // Value (NULL for internal nodes)
    struct RadixNode **children;    // Array of child pointers
    int num_children;               // Number of children
    bool is_leaf;                   // Whether this node stores a value
} RadixNode;

// Radix tree structure
typedef struct RadixTree {
    RadixNode *root;
    size_t size;                    // Number of key-value pairs
} RadixTree;

/**
 * Create a new radix tree
 * @return Pointer to the newly created radix tree
 */
RadixTree* radix_tree_create(void);

/**
 * Insert a key-value pair into the radix tree
 * @param tree The radix tree
 * @param key The key string to insert
 * @param value The value to associate with the key
 * @return true if insertion was successful, false otherwise
 */
bool radix_tree_insert(RadixTree *tree, const char *key, void *value);

/**
 * Search for a key in the radix tree
 * @param tree The radix tree
 * @param key The key to search for
 * @return The value associated with the key, or NULL if not found
 */
void* radix_tree_search(RadixTree *tree, const char *key);

/**
 * Delete a key from the radix tree
 * @param tree The radix tree
 * @param key The key to delete
 * @return true if deletion was successful, false otherwise
 */
bool radix_tree_delete(RadixTree *tree, const char *key);

/**
 * Find all keys with a given prefix
 * @param tree The radix tree
 * @param prefix The prefix to search for
 * @param results Array to store the matching keys
 * @param max_results Maximum number of results to return
 * @return Number of keys found
 */
int radix_tree_find_prefix(RadixTree *tree, const char *prefix, 
                           char **results, int max_results);

/**
 * Find the longest common prefix
 * @param tree The radix tree
 * @param key The key to find the longest prefix for
 * @return The longest matching prefix, or NULL if none found
 */
char* radix_tree_longest_prefix(RadixTree *tree, const char *key);

/**
 * Get the size of the tree
 * @param tree The radix tree
 * @return Number of key-value pairs in the tree
 */
size_t radix_tree_size(RadixTree *tree);

/**
 * Check if the tree is empty
 * @param tree The radix tree
 * @return true if tree is empty, false otherwise
 */
bool radix_tree_is_empty(RadixTree *tree);

/**
 * Destroy the radix tree and free all allocated memory
 * @param tree The radix tree to destroy
 */
void radix_tree_destroy(RadixTree *tree);

/**
 * Print the radix tree structure (for debugging)
 * @param tree The radix tree to print
 */
void radix_tree_print(RadixTree *tree);

#endif // RADIX_TREE_H

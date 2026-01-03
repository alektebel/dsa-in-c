/**
 * Red-Black Tree Implementation
 * 
 * Red-Black trees are self-balancing binary search trees used in many system components:
 * - Linux kernel for scheduling (Completely Fair Scheduler)
 * - Virtual memory management
 * - Process scheduling and priority queues
 * 
 * Properties:
 * 1. Every node is either red or black
 * 2. Root is always black
 * 3. All leaves (NIL) are black
 * 4. Red nodes cannot have red children
 * 5. All paths from root to leaves contain the same number of black nodes
 */

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdbool.h>
#include <stddef.h>

// Color enumeration
typedef enum {
    RED,
    BLACK
} NodeColor;

// Red-Black tree node
typedef struct RBNode {
    int key;                    // Key stored in the node
    void *data;                 // Associated data
    NodeColor color;            // Node color (RED or BLACK)
    struct RBNode *left;        // Left child
    struct RBNode *right;       // Right child
    struct RBNode *parent;      // Parent node
} RBNode;

// Red-Black tree structure
typedef struct RBTree {
    RBNode *root;
    RBNode *nil;                // Sentinel NIL node
    size_t size;                // Number of nodes in tree
} RBTree;

/**
 * Create a new red-black tree
 * @return Pointer to the newly created red-black tree
 */
RBTree* rb_tree_create(void);

/**
 * Insert a key-value pair into the red-black tree
 * @param tree The red-black tree
 * @param key The key to insert
 * @param data The data associated with the key
 * @return true if insertion was successful, false otherwise
 */
bool rb_tree_insert(RBTree *tree, int key, void *data);

/**
 * Search for a key in the red-black tree
 * @param tree The red-black tree
 * @param key The key to search for
 * @return Pointer to the node containing the key, or NULL if not found
 */
RBNode* rb_tree_search(RBTree *tree, int key);

/**
 * Delete a key from the red-black tree
 * @param tree The red-black tree
 * @param key The key to delete
 * @return true if deletion was successful, false otherwise
 */
bool rb_tree_delete(RBTree *tree, int key);

/**
 * Find the minimum key in the tree
 * @param tree The red-black tree
 * @return Pointer to the node with minimum key, or NULL if tree is empty
 */
RBNode* rb_tree_minimum(RBTree *tree);

/**
 * Find the maximum key in the tree
 * @param tree The red-black tree
 * @return Pointer to the node with maximum key, or NULL if tree is empty
 */
RBNode* rb_tree_maximum(RBTree *tree);

/**
 * Find the successor of a node
 * @param tree The red-black tree
 * @param node The node whose successor to find
 * @return Pointer to the successor node, or NULL if none exists
 */
RBNode* rb_tree_successor(RBTree *tree, RBNode *node);

/**
 * Find the predecessor of a node
 * @param tree The red-black tree
 * @param node The node whose predecessor to find
 * @return Pointer to the predecessor node, or NULL if none exists
 */
RBNode* rb_tree_predecessor(RBTree *tree, RBNode *node);

/**
 * Get the size of the tree
 * @param tree The red-black tree
 * @return Number of nodes in the tree
 */
size_t rb_tree_size(RBTree *tree);

/**
 * Check if the tree is empty
 * @param tree The red-black tree
 * @return true if tree is empty, false otherwise
 */
bool rb_tree_is_empty(RBTree *tree);

/**
 * Destroy the red-black tree and free all allocated memory
 * @param tree The red-black tree to destroy
 */
void rb_tree_destroy(RBTree *tree);

/**
 * Print the red-black tree structure (for debugging)
 * @param tree The red-black tree to print
 */
void rb_tree_print(RBTree *tree);

/**
 * Verify that the tree maintains red-black properties (for debugging)
 * @param tree The red-black tree to verify
 * @return true if tree is valid, false otherwise
 */
bool rb_tree_verify(RBTree *tree);

#endif // RED_BLACK_TREE_H

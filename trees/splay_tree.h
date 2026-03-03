/**
 * Splay Tree Implementation
 *
 * A splay tree is a self-adjusting binary search tree in which every
 * access (search, insert, delete) is followed by a "splay" operation that
 * moves the accessed element to the root via a sequence of rotations.
 *
 * Splay trees achieve O(log n) amortized time per operation and satisfy
 * the "working-set property": accessing element x takes time proportional
 * to log(t_x), where t_x is the number of distinct elements accessed since
 * the last access to x.
 *
 * Real-Life Use Cases:
 * 1. Cache-Friendly Symbol Tables: In an interpreter or JIT compiler,
 *    recently used variable bindings are accessed repeatedly. A splay tree
 *    keeps hot keys near the root, reducing average access depth from
 *    O(log n) toward O(1) for frequently used keys—acting as an implicit
 *    cache.
 * 2. Network Flow and Link-Cut Trees: Splay trees are the building block
 *    of Sleator-Tarjan link-cut trees, which support dynamic tree path
 *    operations in O(log n) amortized time. These underlie efficient max-flow
 *    and minimum spanning tree algorithms used in network design.
 * 3. Text Editor / Rope Data Structure: The "rope" data structure for
 *    efficient string concatenation and splitting is often built on splay
 *    trees, so that a text editor's most recently edited regions are kept
 *    near the root of the rope tree, making common editing patterns fast.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 7 (Mar 5, 2003)
 *   - Sleator & Tarjan, "Self-Adjusting Binary Search Trees", JACM 1985
 */

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stdbool.h>
#include <stddef.h>

/** A node in the splay tree. */
typedef struct SplayNode {
    int key;
    void *data;
    struct SplayNode *left;
    struct SplayNode *right;
    struct SplayNode *parent;
} SplayNode;

/** The splay tree. */
typedef struct SplayTree {
    SplayNode *root;
    size_t size;
} SplayTree;

/**
 * Create an empty splay tree.
 * @return Pointer to the new splay tree, or NULL on failure
 */
SplayTree *splay_tree_create(void);

/**
 * Destroy the splay tree and free all memory.
 * @param tree  The splay tree to destroy
 */
void splay_tree_destroy(SplayTree *tree);

/**
 * Insert a key-value pair into the splay tree.
 * Splays the new node to the root.
 * @param tree  The splay tree
 * @param key   Key to insert
 * @param data  Associated data pointer
 * @return true on success, false on failure (e.g., duplicate key)
 */
bool splay_tree_insert(SplayTree *tree, int key, void *data);

/**
 * Delete a key from the splay tree.
 * @param tree  The splay tree
 * @param key   Key to delete
 * @return true if key was found and deleted, false otherwise
 */
bool splay_tree_delete(SplayTree *tree, int key);

/**
 * Search for a key; splays it to the root if found.
 * @param tree  The splay tree
 * @param key   Key to search
 * @return Pointer to the node (now at root), or NULL if not found
 */
SplayNode *splay_tree_search(SplayTree *tree, int key);

/**
 * Find the minimum key; splays it to the root.
 * @param tree  The splay tree
 * @return Pointer to the minimum node, or NULL if empty
 */
SplayNode *splay_tree_minimum(SplayTree *tree);

/**
 * Find the maximum key; splays it to the root.
 * @param tree  The splay tree
 * @return Pointer to the maximum node, or NULL if empty
 */
SplayNode *splay_tree_maximum(SplayTree *tree);

/**
 * Split the splay tree into two trees around key.
 * After the call, *left holds all keys <= key, *right holds all keys > key.
 * @param tree   The splay tree (consumed)
 * @param key    Split key
 * @param left   Output: tree with keys <= key
 * @param right  Output: tree with keys > key
 */
void splay_tree_split(SplayTree *tree, int key,
                      SplayTree **left, SplayTree **right);

/**
 * Merge two splay trees (all keys in left must be < all keys in right).
 * @param left   Left tree (consumed)
 * @param right  Right tree (consumed)
 * @return Merged splay tree, or NULL on failure
 */
SplayTree *splay_tree_merge(SplayTree *left, SplayTree *right);

/**
 * Return the number of keys in the tree.
 * @param tree  The splay tree
 * @return size
 */
size_t splay_tree_size(const SplayTree *tree);

/**
 * Check whether the tree is empty.
 * @param tree  The splay tree
 * @return true if empty
 */
bool splay_tree_is_empty(const SplayTree *tree);

#endif /* SPLAY_TREE_H */

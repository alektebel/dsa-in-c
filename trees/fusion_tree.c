/**
 * Fusion Tree Implementation
 */

#include "fusion_tree.h"
#include <stdlib.h>
#include <string.h>

FusionTree *fusion_tree_create(void) {
    FusionTree *tree = (FusionTree *)malloc(sizeof(FusionTree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->n = 0;
    tree->height = 0;
    return tree;
}

/* Helper: recursively free nodes. */
static void fusion_node_destroy(FusionNode *node) {
    if (!node) return;
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++)
            fusion_node_destroy(node->children[i]);
    }
    free(node);
}

void fusion_tree_destroy(FusionTree *tree) {
    if (!tree) return;
    fusion_node_destroy(tree->root);
    free(tree);
}

/* Helper: create a new leaf node. */
static FusionNode *fusion_node_create(bool is_leaf) {
    FusionNode *node = (FusionNode *)calloc(1, sizeof(FusionNode));
    if (!node) return NULL;
    node->is_leaf = is_leaf;
    return node;
}

bool fusion_tree_insert(FusionTree *tree, uint64_t key) {
    /* TODO: Implement fusion tree insertion.
     * Algorithm:
     * 1. If tree is empty, create a leaf root and insert.
     * 2. Traverse from root to leaf using word-parallel sketched search
     *    at each node (allows O(1) comparison against all keys in a node).
     * 3. Insert key into the leaf; if leaf overflows (num_keys == FUSION_B),
     *    split and propagate upward.
     * 4. Recompute sketch for modified nodes.
     *
     * Sketch computation (simplified):
     *   Given B keys k_0 < k_1 < ... < k_{B-1}, the sketch packs a few
     *   "distinguishing bits" of each key into a single word so that a
     *   parallel comparison of a query key against all B keys can be done
     *   with O(1) word operations. */
    if (!tree) return false;
    return false;
}

bool fusion_tree_delete(FusionTree *tree, uint64_t key) {
    /* TODO: Implement fusion tree deletion.
     * 1. Find the leaf containing key using the sketch-based search.
     * 2. Remove the key from the leaf.
     * 3. If the node underflows (num_keys < FUSION_B/2), borrow from a
     *    sibling or merge with a sibling, then update sketches. */
    if (!tree) return false;
    return false;
}

bool fusion_tree_search(const FusionTree *tree, uint64_t key) {
    /* TODO: Traverse the tree using the sketch-based O(1)-per-node search.
     * At each internal node:
     *   1. Compute sketch of query key restricted to distinguishing bits.
     *   2. Parallel-compare against the node sketch in O(1) word ops.
     *   3. Extract the child index and descend.
     * At the leaf, do a linear scan (or sketched scan) for the key. */
    if (!tree || !tree->root) return false;
    return false;
}

bool fusion_tree_predecessor(const FusionTree *tree, uint64_t key,
                             uint64_t *result) {
    /* TODO: Similar traversal to search; track the largest key seen that
     * is less than the query key. */
    (void)key;
    if (result) *result = 0;
    return false;
}

bool fusion_tree_successor(const FusionTree *tree, uint64_t key,
                           uint64_t *result) {
    /* TODO: Track the smallest key seen that is greater than the query key. */
    (void)key;
    if (result) *result = 0;
    return false;
}

int fusion_tree_size(const FusionTree *tree) {
    return tree ? tree->n : 0;
}

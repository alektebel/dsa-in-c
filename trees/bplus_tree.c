/**
 * B+ Tree Implementation
 */

#include "bplus_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BPlusTree* bplus_tree_create(int order) {
    BPlusTree *tree = (BPlusTree*)malloc(sizeof(BPlusTree));
    if (!tree) return NULL;
    
    tree->root = NULL;
    tree->order = order;
    
    return tree;
}

bool bplus_tree_insert(BPlusTree *tree, int key) {
    // TODO: Implement B+ tree insertion
    // 1. Find the appropriate leaf node
    // 2. Insert key in sorted order
    // 3. If node overflows, split and propagate changes upward
    return false;
}

bool bplus_tree_search(BPlusTree *tree, int key) {
    // TODO: Implement B+ tree search
    // 1. Traverse from root to leaf
    // 2. At each internal node, find the appropriate child
    // 3. Check if key exists in leaf node
    return false;
}

bool bplus_tree_delete(BPlusTree *tree, int key) {
    // TODO: Implement B+ tree deletion
    // 1. Find and remove key from leaf
    // 2. Handle underflow by borrowing or merging
    // 3. Update internal nodes if necessary
    return false;
}

int bplus_tree_range_query(BPlusTree *tree, int start_key, int end_key, 
                           int *result, int max_results) {
    // TODO: Implement range query
    // 1. Find the leaf containing start_key
    // 2. Traverse linked leaf nodes collecting keys
    // 3. Stop when reaching end_key or max_results
    return 0;
}

void bplus_tree_destroy(BPlusTree *tree) {
    // TODO: Implement tree destruction
    // 1. Recursively free all nodes
    // 2. Free the tree structure itself
    if (tree) {
        // Free root and all children recursively
        free(tree);
    }
}

void bplus_tree_print(BPlusTree *tree) {
    // TODO: Implement tree printing for debugging
    printf("B+ Tree structure:\n");
    if (!tree || !tree->root) {
        printf("  (empty)\n");
        return;
    }
    // Print tree level by level
}

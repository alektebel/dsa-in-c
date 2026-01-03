/**
 * Interval Tree Implementation
 */

#include "interval_tree.h"
#include <stdlib.h>
#include <stdio.h>

IntervalTree* interval_tree_create(void) {
    IntervalTree *tree = (IntervalTree*)malloc(sizeof(IntervalTree));
    if (!tree) return NULL;
    
    tree->root = NULL;
    return tree;
}

bool interval_tree_insert(IntervalTree *tree, int low, int high) {
    // TODO: Implement interval tree insertion
    // 1. Insert based on low endpoint (like BST)
    // 2. Update max values along the path
    return false;
}

bool interval_tree_search_overlap(IntervalTree *tree, int low, int high, 
                                  Interval *result) {
    // TODO: Implement overlap search
    // 1. Start from root
    // 2. If current interval overlaps, return it
    // 3. If left child's max >= query low, search left
    // 4. Otherwise search right
    return false;
}

int interval_tree_find_all_overlaps(IntervalTree *tree, int low, int high,
                                    Interval *results, int max_results) {
    // TODO: Implement finding all overlapping intervals
    // 1. Traverse tree recursively
    // 2. Collect all overlapping intervals
    return 0;
}

bool interval_tree_delete(IntervalTree *tree, int low, int high) {
    // TODO: Implement interval deletion
    // 1. Find the interval to delete
    // 2. Remove node using BST deletion
    // 3. Update max values along the path
    return false;
}

void interval_tree_destroy(IntervalTree *tree) {
    // TODO: Implement tree destruction
    // Recursively free all nodes
    if (tree) {
        free(tree);
    }
}

void interval_tree_print(IntervalTree *tree) {
    // TODO: Implement tree printing for debugging
    printf("Interval Tree structure:\n");
    if (!tree || !tree->root) {
        printf("  (empty)\n");
        return;
    }
}

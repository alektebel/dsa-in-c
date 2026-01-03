/**
 * Radix Tree Implementation
 */

#include "radix_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

RadixTree* radix_tree_create(void) {
    RadixTree *tree = (RadixTree*)malloc(sizeof(RadixTree));
    if (!tree) return NULL;
    
    tree->root = NULL;
    tree->size = 0;
    
    return tree;
}

bool radix_tree_insert(RadixTree *tree, const char *key, void *value) {
    // TODO: Implement radix tree insertion
    // 1. Find the node where key should be inserted
    // 2. Split nodes if necessary to accommodate the key
    // 3. Create new nodes as needed
    return false;
}

void* radix_tree_search(RadixTree *tree, const char *key) {
    // TODO: Implement search
    // 1. Traverse tree matching key fragments
    // 2. Return value if exact match found
    return NULL;
}

bool radix_tree_delete(RadixTree *tree, const char *key) {
    // TODO: Implement deletion
    // 1. Find and remove the key
    // 2. Merge nodes if possible
    // 3. Remove empty branches
    return false;
}

int radix_tree_find_prefix(RadixTree *tree, const char *prefix, 
                           char **results, int max_results) {
    // TODO: Implement prefix search
    // 1. Find node matching the prefix
    // 2. Collect all keys in the subtree
    return 0;
}

char* radix_tree_longest_prefix(RadixTree *tree, const char *key) {
    // TODO: Find longest matching prefix
    // Used in routing and path matching
    return NULL;
}

size_t radix_tree_size(RadixTree *tree) {
    return tree ? tree->size : 0;
}

bool radix_tree_is_empty(RadixTree *tree) {
    return tree && tree->size == 0;
}

void radix_tree_destroy(RadixTree *tree) {
    // TODO: Implement tree destruction
    // Recursively free all nodes and key strings
    if (tree) {
        free(tree);
    }
}

void radix_tree_print(RadixTree *tree) {
    // TODO: Implement tree printing
    printf("Radix Tree structure:\n");
    if (!tree || !tree->root) {
        printf("  (empty)\n");
        return;
    }
}

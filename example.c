/**
 * Example Usage of DSA-in-C Templates
 * 
 * This file demonstrates how to include and use the various
 * data structures and algorithms provided by this library.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include headers from different modules
#include "trees/red_black_tree.h"
#include "hash/hash_table.h"
#include "hash/hash_functions.h"
#include "search_algorithms/binary_search.h"
#include "lists/priority_sorted_list.h"
#include "heaps/priority_heap.h"
#include "string_matching/kmp_string_matching.h"

void example_red_black_tree() {
    printf("\n=== Red-Black Tree Example ===\n");
    
    // Create a red-black tree
    RBTree *tree = rb_tree_create();
    if (!tree) {
        printf("Failed to create red-black tree\n");
        return;
    }
    
    printf("Red-black tree created successfully\n");
    printf("Size: %zu\n", rb_tree_size(tree));
    printf("Empty: %s\n", rb_tree_is_empty(tree) ? "Yes" : "No");
    
    // TODO: Once implemented, insert and search operations can be used
    // rb_tree_insert(tree, 10, NULL);
    // rb_tree_insert(tree, 5, NULL);
    // rb_tree_insert(tree, 15, NULL);
    // rb_tree_print(tree);
    
    rb_tree_destroy(tree);
    printf("Red-black tree destroyed\n");
}

void example_hash_table() {
    printf("\n=== Hash Table Example ===\n");
    
    // Create a hash table
    HashTable *table = hash_table_create(16);
    if (!table) {
        printf("Failed to create hash table\n");
        return;
    }
    
    printf("Hash table created successfully\n");
    printf("Size: %zu\n", hash_table_size(table));
    printf("Empty: %s\n", hash_table_is_empty(table) ? "Yes" : "No");
    printf("Load factor: %.2f\n", hash_table_load_factor(table));
    
    // TODO: Once implemented, insert and search operations can be used
    // hash_table_insert(table, "key1", "value1");
    // hash_table_insert(table, "key2", "value2");
    // void *value = hash_table_get(table, "key1");
    
    hash_table_destroy(table);
    printf("Hash table destroyed\n");
}

void example_hash_functions() {
    printf("\n=== Hash Functions Example ===\n");
    
    const char *text = "Hello, World!";
    
    printf("Text: \"%s\"\n", text);
    printf("DJB2 hash: %u\n", hash_djb2_string(text));
    printf("FNV-1a hash: %u\n", hash_fnv1a_32(text, strlen(text)));
    
    // Integer hash example
    uint32_t key = 12345;
    printf("Integer key: %u\n", key);
    printf("Hashed: %u\n", hash_int(key));
}

void example_binary_search() {
    printf("\n=== Binary Search Example ===\n");
    
    int array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int size = sizeof(array) / sizeof(array[0]);
    
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // TODO: Once implemented, search operations can be used
    // int target = 7;
    // int index = binary_search_int(array, size, target);
    // printf("Searching for %d: %s at index %d\n", 
    //        target, index != -1 ? "Found" : "Not found", index);
    
    printf("Binary search functions available (implementation pending)\n");
}

void example_priority_heap() {
    printf("\n=== Priority Heap Example ===\n");
    
    // Create a max heap
    PriorityHeap *heap = priority_heap_create(10, MAX_HEAP);
    if (!heap) {
        printf("Failed to create priority heap\n");
        return;
    }
    
    printf("Priority heap created successfully (MAX_HEAP)\n");
    printf("Size: %zu\n", priority_heap_size(heap));
    printf("Empty: %s\n", priority_heap_is_empty(heap) ? "Yes" : "No");
    printf("Capacity: %zu\n", heap->capacity);
    
    // TODO: Once implemented, heap operations can be used
    // priority_heap_insert(heap, 10, "task1");
    // priority_heap_insert(heap, 20, "task2");
    // priority_heap_insert(heap, 5, "task3");
    
    priority_heap_destroy(heap);
    printf("Priority heap destroyed\n");
}

void example_string_matching() {
    printf("\n=== KMP String Matching Example ===\n");
    
    const char *text = "ABABDABACDABABCABAB";
    const char *pattern = "ABABCABAB";
    
    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    
    // TODO: Once implemented, KMP search can be used
    // int index = kmp_search_string(text, pattern);
    // printf("Pattern %s at index %d\n", 
    //        index != -1 ? "found" : "not found", index);
    
    printf("KMP string matching available (implementation pending)\n");
}

int main(void) {
    printf("DSA-in-C Example Usage\n");
    printf("======================\n");
    printf("\nThis demonstrates the available templates.\n");
    printf("Full implementations are pending (see TODO comments).\n");
    
    example_red_black_tree();
    example_hash_table();
    example_hash_functions();
    example_binary_search();
    example_priority_heap();
    example_string_matching();
    
    printf("\n=== All Examples Completed ===\n");
    printf("\nNote: Most operations are templates with TODO comments.\n");
    printf("Implement the TODO sections to make them functional.\n");
    
    return 0;
}

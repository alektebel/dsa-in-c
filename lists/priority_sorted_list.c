/**
 * Priority Sorted List Implementation
 */

#include "priority_sorted_list.h"
#include <stdlib.h>
#include <stdio.h>

PrioritySortedList* priority_list_create(void) {
    PrioritySortedList *list = (PrioritySortedList*)malloc(sizeof(PrioritySortedList));
    if (!list) return NULL;
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    
    return list;
}

bool priority_list_insert(PrioritySortedList *list, int priority, void *data) {
    // TODO: Implement insertion in sorted order
    // 1. Create new node
    // 2. Find correct position based on priority
    // 3. Insert maintaining sorted order (highest priority first)
    return false;
}

void* priority_list_pop(PrioritySortedList *list, int *priority) {
    // TODO: Remove and return highest priority element
    // 1. Remove head node
    // 2. Update head pointer
    // 3. Return data and priority
    return NULL;
}

void* priority_list_peek(PrioritySortedList *list, int *priority) {
    // TODO: Return highest priority element without removing
    if (!list || !list->head) return NULL;
    if (priority) *priority = list->head->priority;
    return list->head->data;
}

bool priority_list_remove(PrioritySortedList *list, void *data) {
    // TODO: Find and remove specific element
    // 1. Search for element
    // 2. Unlink from list
    // 3. Free node
    return false;
}

bool priority_list_update_priority(PrioritySortedList *list, void *data, 
                                   int new_priority) {
    // TODO: Update priority and reposition element
    // 1. Find element
    // 2. Remove from current position
    // 3. Reinsert with new priority
    return false;
}

size_t priority_list_size(PrioritySortedList *list) {
    return list ? list->size : 0;
}

bool priority_list_is_empty(PrioritySortedList *list) {
    return list && list->size == 0;
}

void priority_list_clear(PrioritySortedList *list) {
    // TODO: Remove all elements
    if (!list) return;
    // Free all nodes
}

void priority_list_destroy(PrioritySortedList *list) {
    // TODO: Implement list destruction
    if (list) {
        priority_list_clear(list);
        free(list);
    }
}

void priority_list_print(PrioritySortedList *list) {
    // TODO: Print list for debugging
    printf("Priority Sorted List:\n");
    if (!list || !list->head) {
        printf("  (empty)\n");
        return;
    }
    // Print each node with priority and data
}

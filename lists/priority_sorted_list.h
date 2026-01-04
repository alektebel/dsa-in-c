/**
 * Priority Sorted List Implementation
 * 
 * Priority sorted lists are used in operating systems for:
 * - Mutex wait queues
 * - Device driver queues
 * - Task scheduling
 * 
 * Elements are kept sorted by priority for efficient access to highest priority items.
 */

#ifndef PRIORITY_SORTED_LIST_H
#define PRIORITY_SORTED_LIST_H

#include <stdbool.h>
#include <stddef.h>

// List node structure
typedef struct PriorityListNode {
    int priority;                       // Priority value (higher = more important)
    void *data;                         // Associated data
    struct PriorityListNode *next;      // Next node in list
    struct PriorityListNode *prev;      // Previous node in list
} PriorityListNode;

// Priority sorted list structure
typedef struct PrioritySortedList {
    PriorityListNode *head;             // Head of the list (highest priority)
    PriorityListNode *tail;             // Tail of the list (lowest priority)
    size_t size;                        // Number of elements
} PrioritySortedList;

/**
 * Create a new priority sorted list
 * @return Pointer to the newly created list
 */
PrioritySortedList* priority_list_create(void);

/**
 * Insert an element with given priority
 * @param list The priority sorted list
 * @param priority The priority value
 * @param data The data to insert
 * @return true if insertion was successful, false otherwise
 */
bool priority_list_insert(PrioritySortedList *list, int priority, void *data);

/**
 * Remove and return the highest priority element
 * @param list The priority sorted list
 * @param priority Pointer to store the priority of removed element
 * @return The data of the highest priority element, or NULL if list is empty
 */
void* priority_list_pop(PrioritySortedList *list, int *priority);

/**
 * Peek at the highest priority element without removing it
 * @param list The priority sorted list
 * @param priority Pointer to store the priority
 * @return The data of the highest priority element, or NULL if list is empty
 */
void* priority_list_peek(PrioritySortedList *list, int *priority);

/**
 * Remove a specific element from the list
 * @param list The priority sorted list
 * @param data The data to remove
 * @return true if element was found and removed, false otherwise
 */
bool priority_list_remove(PrioritySortedList *list, void *data);

/**
 * Update the priority of an existing element
 * @param list The priority sorted list
 * @param data The data whose priority to update
 * @param new_priority The new priority value
 * @return true if update was successful, false otherwise
 */
bool priority_list_update_priority(PrioritySortedList *list, void *data, 
                                   int new_priority);

/**
 * Get the size of the list
 * @param list The priority sorted list
 * @return Number of elements in the list
 */
size_t priority_list_size(PrioritySortedList *list);

/**
 * Check if the list is empty
 * @param list The priority sorted list
 * @return true if list is empty, false otherwise
 */
bool priority_list_is_empty(PrioritySortedList *list);

/**
 * Clear all elements from the list
 * @param list The priority sorted list
 */
void priority_list_clear(PrioritySortedList *list);

/**
 * Destroy the list and free all allocated memory
 * @param list The priority sorted list to destroy
 */
void priority_list_destroy(PrioritySortedList *list);

/**
 * Print the list (for debugging)
 * @param list The priority sorted list to print
 */
void priority_list_print(PrioritySortedList *list);

#endif // PRIORITY_SORTED_LIST_H

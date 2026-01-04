/**
 * Priority Heap (Binary Heap) Implementation
 * 
 * Priority heaps provide O(log n) insertion and O(1) access to highest priority element.
 * Used extensively in:
 * - Task scheduling
 * - Event-driven simulation
 * - Graph algorithms (Dijkstra's, Prim's)
 * - Heap sort
 */

#ifndef PRIORITY_HEAP_H
#define PRIORITY_HEAP_H

#include <stdbool.h>
#include <stddef.h>

// Heap element structure
typedef struct HeapElement {
    int priority;           // Priority value
    void *data;            // Associated data
} HeapElement;

// Heap type enumeration
typedef enum {
    MAX_HEAP,              // Maximum element at root
    MIN_HEAP               // Minimum element at root
} HeapType;

// Priority heap structure
typedef struct PriorityHeap {
    HeapElement *elements; // Array of heap elements
    size_t size;           // Current number of elements
    size_t capacity;       // Maximum capacity
    HeapType type;         // MAX_HEAP or MIN_HEAP
} PriorityHeap;

/**
 * Create a new priority heap
 * @param capacity Initial capacity of the heap
 * @param type Type of heap (MAX_HEAP or MIN_HEAP)
 * @return Pointer to the newly created heap
 */
PriorityHeap* priority_heap_create(size_t capacity, HeapType type);

/**
 * Insert an element into the heap
 * @param heap The priority heap
 * @param priority The priority value
 * @param data The data to insert
 * @return true if insertion was successful, false otherwise
 */
bool priority_heap_insert(PriorityHeap *heap, int priority, void *data);

/**
 * Remove and return the root element (highest/lowest priority)
 * @param heap The priority heap
 * @param priority Pointer to store the priority of removed element
 * @return The data of the root element, or NULL if heap is empty
 */
void* priority_heap_extract(PriorityHeap *heap, int *priority);

/**
 * Peek at the root element without removing it
 * @param heap The priority heap
 * @param priority Pointer to store the priority
 * @return The data of the root element, or NULL if heap is empty
 */
void* priority_heap_peek(PriorityHeap *heap, int *priority);

/**
 * Update the priority of an element at a given index
 * @param heap The priority heap
 * @param index Index of the element to update
 * @param new_priority The new priority value
 * @return true if update was successful, false otherwise
 */
bool priority_heap_update(PriorityHeap *heap, size_t index, int new_priority);

/**
 * Build a heap from an array of elements
 * @param heap The priority heap
 * @param elements Array of elements
 * @param count Number of elements
 * @return true if successful, false otherwise
 */
bool priority_heap_build(PriorityHeap *heap, HeapElement *elements, size_t count);

/**
 * Perform heap sort on an array
 * @param elements Array of elements to sort
 * @param count Number of elements
 * @param ascending Sort in ascending order if true, descending if false
 */
void priority_heap_sort(HeapElement *elements, size_t count, bool ascending);

/**
 * Get the size of the heap
 * @param heap The priority heap
 * @return Number of elements in the heap
 */
size_t priority_heap_size(PriorityHeap *heap);

/**
 * Check if the heap is empty
 * @param heap The priority heap
 * @return true if heap is empty, false otherwise
 */
bool priority_heap_is_empty(PriorityHeap *heap);

/**
 * Check if the heap is full
 * @param heap The priority heap
 * @return true if heap is full, false otherwise
 */
bool priority_heap_is_full(PriorityHeap *heap);

/**
 * Clear all elements from the heap
 * @param heap The priority heap
 */
void priority_heap_clear(PriorityHeap *heap);

/**
 * Destroy the heap and free all allocated memory
 * @param heap The priority heap to destroy
 */
void priority_heap_destroy(PriorityHeap *heap);

/**
 * Print the heap (for debugging)
 * @param heap The priority heap to print
 */
void priority_heap_print(PriorityHeap *heap);

/**
 * Verify heap property (for debugging)
 * @param heap The priority heap to verify
 * @return true if heap property is maintained, false otherwise
 */
bool priority_heap_verify(PriorityHeap *heap);

#endif // PRIORITY_HEAP_H

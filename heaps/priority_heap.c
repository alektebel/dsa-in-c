/**
 * Priority Heap Implementation
 */

#include "priority_heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PriorityHeap* priority_heap_create(size_t capacity, HeapType type) {
    PriorityHeap *heap = (PriorityHeap*)malloc(sizeof(PriorityHeap));
    if (!heap) return NULL;
    
    heap->elements = (HeapElement*)malloc(capacity * sizeof(HeapElement));
    if (!heap->elements) {
        free(heap);
        return NULL;
    }
    
    heap->size = 0;
    heap->capacity = capacity;
    heap->type = type;
    
    return heap;
}

bool priority_heap_insert(PriorityHeap *heap, int priority, void *data) {
    // TODO: Implement heap insertion
    // 1. Add element at end
    // 2. Bubble up to maintain heap property
    return false;
}

void* priority_heap_extract(PriorityHeap *heap, int *priority) {
    // TODO: Implement extract root
    // 1. Save root element
    // 2. Move last element to root
    // 3. Bubble down to maintain heap property
    return NULL;
}

void* priority_heap_peek(PriorityHeap *heap, int *priority) {
    // TODO: Return root element without removing
    if (!heap || heap->size == 0) return NULL;
    if (priority) *priority = heap->elements[0].priority;
    return heap->elements[0].data;
}

bool priority_heap_update(PriorityHeap *heap, size_t index, int new_priority) {
    // TODO: Update priority and restore heap property
    // 1. Update priority
    // 2. Bubble up or down as needed
    return false;
}

bool priority_heap_build(PriorityHeap *heap, HeapElement *elements, size_t count) {
    // TODO: Build heap from array (heapify)
    // Use bottom-up approach for O(n) complexity
    return false;
}

void priority_heap_sort(HeapElement *elements, size_t count, bool ascending) {
    // TODO: Implement heap sort
    // 1. Build heap
    // 2. Repeatedly extract max/min
}

size_t priority_heap_size(PriorityHeap *heap) {
    return heap ? heap->size : 0;
}

bool priority_heap_is_empty(PriorityHeap *heap) {
    return heap && heap->size == 0;
}

bool priority_heap_is_full(PriorityHeap *heap) {
    return heap && heap->size >= heap->capacity;
}

void priority_heap_clear(PriorityHeap *heap) {
    if (heap) heap->size = 0;
}

void priority_heap_destroy(PriorityHeap *heap) {
    if (heap) {
        if (heap->elements) free(heap->elements);
        free(heap);
    }
}

void priority_heap_print(PriorityHeap *heap) {
    printf("Priority Heap (%s):\n", 
           heap->type == MAX_HEAP ? "MAX" : "MIN");
    if (!heap || heap->size == 0) {
        printf("  (empty)\n");
        return;
    }
    // TODO: Print heap level by level
}

bool priority_heap_verify(PriorityHeap *heap) {
    // TODO: Verify heap property
    // Check that parent priority is >= (max) or <= (min) child priorities
    return true;
}

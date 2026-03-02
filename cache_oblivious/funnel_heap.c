/**
 * Funnelheap (Cache-Oblivious Priority Queue) Implementation
 */

#include "funnel_heap.h"
#include <stdlib.h>
#include <string.h>

FunnelHeap *fheap_create(void) {
    FunnelHeap *heap = (FunnelHeap *)calloc(1, sizeof(FunnelHeap));
    return heap;
}

void fheap_destroy(FunnelHeap *heap) {
    if (!heap) return;
    for (int i = 0; i < FH_MAX_LEVELS; i++) free(heap->levels[i].data);
    free(heap);
}

/* Helper: merge two sorted arrays a (size na) and b (size nb) into out. */
static void merge_sorted(const int *a, int na, const int *b, int nb, int *out) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) out[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
}

bool fheap_insert(FunnelHeap *heap, int key) {
    /* TODO: Implement funnelheap insert.
     * 1. Create a single-element sorted array at level 0.
     * 2. If level 0 is occupied (size > 0):
     *    Merge levels 0 and 1 into a temporary buffer; promote to level 1.
     *    Repeat carry propagation while consecutive levels are both occupied
     *    (like a binary counter increment).
     * 3. Store the result at the lowest empty level.
     *
     * Each level i holds exactly 2^i elements when full. */
    if (!heap) return false;

    /* Start with a 1-element "carry" array */
    int carry_data = key;
    int carry_size = 1;
    int *carry = &carry_data;

    for (int i = 0; i < FH_MAX_LEVELS; i++) {
        FHLevel *lv = &heap->levels[i];
        if (lv->size == 0) {
            /* Empty level: store carry here */
            int needed = carry_size;
            if (needed > lv->capacity) {
                int *tmp = (int *)realloc(lv->data, (size_t)needed * sizeof(int));
                if (!tmp) return false;
                lv->data = tmp; lv->capacity = needed;
            }
            memcpy(lv->data, carry, (size_t)carry_size * sizeof(int));
            lv->size = carry_size;
            if (carry != &carry_data) free(carry);
            if (i + 1 > heap->num_levels) heap->num_levels = i + 1;
            heap->n++;
            return true;
        }
        /* Merge carry with level i */
        int new_size = lv->size + carry_size;
        int *merged = (int *)malloc((size_t)new_size * sizeof(int));
        if (!merged) { if (carry != &carry_data) free(carry); return false; }
        merge_sorted(lv->data, lv->size, carry, carry_size, merged);
        if (carry != &carry_data) free(carry);
        /* Clear this level */
        lv->size = 0;
        carry = merged;
        carry_size = new_size;
    }
    /* All levels full: should not happen for sane input sizes */
    if (carry != &carry_data) free(carry);
    return false;
}

bool fheap_find_min(const FunnelHeap *heap, int *key) {
    if (!heap || heap->n == 0 || !key) return false;
    int best = 0;
    bool found = false;
    for (int i = 0; i < FH_MAX_LEVELS; i++) {
        if (heap->levels[i].size > 0) {
            if (!found || heap->levels[i].data[0] < best) {
                best = heap->levels[i].data[0];
                found = true;
            }
        }
    }
    if (found) *key = best;
    return found;
}

bool fheap_delete_min(FunnelHeap *heap, int *key) {
    /* TODO: Implement delete-min.
     * 1. Find the level whose first element is minimum.
     * 2. Remove that element from the level (shift remaining elements).
     * 3. If the level becomes empty, clear it and update num_levels.
     * 4. Decrement n. */
    if (!heap || heap->n == 0) return false;
    int best_level = -1, best_val = 0;
    for (int i = 0; i < FH_MAX_LEVELS; i++) {
        if (heap->levels[i].size > 0) {
            if (best_level < 0 || heap->levels[i].data[0] < best_val) {
                best_val = heap->levels[i].data[0];
                best_level = i;
            }
        }
    }
    if (best_level < 0) return false;
    if (key) *key = best_val;
    FHLevel *lv = &heap->levels[best_level];
    memmove(lv->data, lv->data + 1, (size_t)(lv->size - 1) * sizeof(int));
    lv->size--;
    heap->n--;
    return true;
}

int fheap_size(const FunnelHeap *heap) {
    return heap ? heap->n : 0;
}

bool fheap_is_empty(const FunnelHeap *heap) {
    return !heap || heap->n == 0;
}

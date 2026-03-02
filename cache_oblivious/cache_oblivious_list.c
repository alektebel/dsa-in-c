/**
 * Cache-Oblivious Linked List Implementation
 */

#include "cache_oblivious_list.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int next_pow2_col(int x) {
    int p = 1; while (p < x) p <<= 1; return p;
}

COList *col_create(int initial_capacity) {
    if (initial_capacity <= 0) initial_capacity = 8;
    int cap = next_pow2_col(initial_capacity);
    COList *list = (COList *)malloc(sizeof(COList));
    if (!list) return NULL;
    list->array = (COLElement *)malloc((size_t)cap * sizeof(COLElement));
    if (!list->array) { free(list); return NULL; }
    for (int i = 0; i < cap; i++) {
        list->array[i].key = COL_EMPTY;
        list->array[i].data = NULL;
    }
    list->capacity = cap;
    list->n = 0;
    list->height = (int)(log2((double)cap));
    return list;
}

void col_destroy(COList *list) {
    if (!list) return;
    free(list->array);
    free(list);
}

bool col_insert(COList *list, int key, void *data) {
    /* TODO: Insert into the packed-memory array maintaining sorted order.
     * Use the ordered-file maintenance strategy:
     * 1. Find the insertion position (binary search skipping empties).
     * 2. Shift elements to create a gap.
     * 3. Check density constraints; rebalance if needed.
     * 4. If at capacity, double and rebuild. */
    if (!list || key == COL_EMPTY) return false;

    /* Grow if full */
    if (list->n == list->capacity) {
        int new_cap = list->capacity * 2;
        COLElement *tmp = (COLElement *)realloc(list->array,
                                                (size_t)new_cap * sizeof(COLElement));
        if (!tmp) return false;
        list->array = tmp;
        for (int i = list->capacity; i < new_cap; i++) {
            list->array[i].key = COL_EMPTY;
            list->array[i].data = NULL;
        }
        list->capacity = new_cap;
        list->height = (int)(log2((double)new_cap));
    }

    /* Find insertion position */
    int pos = 0;
    while (pos < list->capacity &&
           list->array[pos].key != COL_EMPTY &&
           list->array[pos].key < key)
        pos++;
    if (pos < list->capacity && list->array[pos].key == key) return false;

    /* Find next empty slot */
    int empty = pos;
    while (empty < list->capacity && list->array[empty].key != COL_EMPTY) empty++;
    if (empty == list->capacity) {
        /* Wrap: find any empty */
        empty = 0;
        while (empty < list->capacity && list->array[empty].key != COL_EMPTY) empty++;
        if (empty == list->capacity) return false;
    }

    /* Shift right to make room */
    memmove(list->array + pos + 1, list->array + pos,
            (size_t)(empty - pos) * sizeof(COLElement));
    list->array[pos].key = key;
    list->array[pos].data = data;
    list->n++;
    return true;
}

bool col_delete(COList *list, int key) {
    if (!list) return false;
    int idx = col_search(list, key);
    if (idx < 0) return false;
    list->array[idx].key = COL_EMPTY;
    list->array[idx].data = NULL;
    list->n--;
    return true;
}

int col_search(const COList *list, int key) {
    if (!list) return -1;
    for (int i = 0; i < list->capacity; i++)
        if (list->array[i].key == key) return i;
    return -1;
}

void col_scan(const COList *list,
              void (*callback)(int key, void *data, void *user_data),
              void *user_data) {
    /* Sequential scan: cache-friendly because elements are in a contiguous array. */
    if (!list || !callback) return;
    for (int i = 0; i < list->capacity; i++) {
        if (list->array[i].key != COL_EMPTY)
            callback(list->array[i].key, list->array[i].data, user_data);
    }
}

int col_size(const COList *list) {
    return list ? list->n : 0;
}

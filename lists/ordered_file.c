/**
 * Ordered-File Maintenance (Packed-Memory Array) Implementation
 */

#include "ordered_file.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* ---- Density thresholds ---- */
/* At depth d (window of size 2^d):
 *   upper threshold = 3/4 + d/(4*height)  (denser near leaves)
 *   lower threshold = 1/4 - d/(4*height)
 * These ensure O(log^2 n) amortized insert cost. */

static double upper_threshold(int depth, int height) {
    return 0.75 + (double)depth / (4.0 * height);
}

static double lower_threshold(int depth, int height) {
    return 0.25 - (double)depth / (4.0 * height);
}

/* Next power of two >= x */
static int next_pow2(int x) {
    int p = 1;
    while (p < x) p <<= 1;
    return p;
}

OrderedFile *ofm_create(int initial_capacity) {
    if (initial_capacity <= 0) initial_capacity = 8;
    int cap = next_pow2(initial_capacity);
    OrderedFile *ofm = (OrderedFile *)malloc(sizeof(OrderedFile));
    if (!ofm) return NULL;
    ofm->keys = (int *)malloc((size_t)cap * sizeof(int));
    if (!ofm->keys) { free(ofm); return NULL; }
    for (int i = 0; i < cap; i++) ofm->keys[i] = OFM_EMPTY_KEY;
    ofm->capacity = cap;
    ofm->n = 0;
    ofm->height = (int)(log2((double)cap));
    return ofm;
}

void ofm_destroy(OrderedFile *ofm) {
    if (!ofm) return;
    free(ofm->keys);
    free(ofm);
}

/* Helper: count non-empty elements in keys[lo..hi-1]. */
static int count_elements(const int *keys, int lo, int hi) {
    int cnt = 0;
    for (int i = lo; i < hi; i++)
        if (keys[i] != OFM_EMPTY_KEY) cnt++;
    return cnt;
}

/* Helper: spread count elements evenly within keys[lo..lo+len-1].
 * Elements are taken from a temporary buffer. */
static void spread(int *keys, int lo, int len, const int *elems, int count) {
    /* Evenly distribute `count` elements in window of size `len` */
    for (int i = 0; i < len; i++) keys[lo + i] = OFM_EMPTY_KEY;
    if (count == 0) return;
    /* Place elements at positions lo + i*len/count (integer division). */
    for (int i = 0; i < count; i++) {
        int pos = lo + (int)((double)i * len / count);
        keys[pos] = elems[i];
    }
}

/* Rebalance window [lo, lo+len) at the given depth. */
static void rebalance(OrderedFile *ofm, int lo, int len, int depth) {
    int cnt = count_elements(ofm->keys, lo, lo + len);
    int *tmp = (int *)malloc((size_t)cnt * sizeof(int));
    if (!tmp) return;
    int k = 0;
    for (int i = lo; i < lo + len; i++)
        if (ofm->keys[i] != OFM_EMPTY_KEY) tmp[k++] = ofm->keys[i];
    spread(ofm->keys, lo, len, tmp, cnt);
    free(tmp);
    (void)depth;
}

bool ofm_insert(OrderedFile *ofm, int key) {
    /* TODO: Full OFM insert with density-based rebalancing.
     * 1. Binary search for insertion position (first empty cell >= where key fits).
     * 2. Shift elements to make room (or find closest empty cell).
     * 3. Find the smallest window containing the insertion point whose density
     *    is within bounds; rebalance that window.
     * 4. If root-level is too dense, double capacity and rebuild. */
    if (!ofm || key == OFM_EMPTY_KEY) return false;
    /* Simplified: find position and insert, then check density */
    int pos = 0;
    while (pos < ofm->capacity &&
           ofm->keys[pos] != OFM_EMPTY_KEY &&
           ofm->keys[pos] < key)
        pos++;
    if (pos < ofm->capacity && ofm->keys[pos] == key) return false; /* dup */
    /* Find nearest empty cell to the right */
    int empty = pos;
    while (empty < ofm->capacity && ofm->keys[empty] != OFM_EMPTY_KEY) empty++;
    if (empty == ofm->capacity) {
        /* Grow and rebalance */
        int new_cap = ofm->capacity * 2;
        int *tmp = (int *)realloc(ofm->keys, (size_t)new_cap * sizeof(int));
        if (!tmp) return false;
        ofm->keys = tmp;
        for (int i = ofm->capacity; i < new_cap; i++) ofm->keys[i] = OFM_EMPTY_KEY;
        ofm->capacity = new_cap;
        ofm->height = (int)(log2((double)new_cap));
        rebalance(ofm, 0, ofm->capacity, 0);
        return ofm_insert(ofm, key);
    }
    /* Shift right to make room at pos */
    memmove(ofm->keys + pos + 1, ofm->keys + pos,
            (size_t)(empty - pos) * sizeof(int));
    ofm->keys[pos] = key;
    ofm->n++;
    /* TODO: check density thresholds and rebalance if needed */
    return true;
}

bool ofm_delete(OrderedFile *ofm, int key) {
    /* TODO: Remove key, leave an empty cell, then rebalance if density
     * falls below the lower threshold. */
    if (!ofm) return false;
    int idx = ofm_search(ofm, key);
    if (idx < 0) return false;
    ofm->keys[idx] = OFM_EMPTY_KEY;
    ofm->n--;
    return true;
}

int ofm_search(const OrderedFile *ofm, int key) {
    /* Binary search skipping empty cells.
     * TODO: A proper OFM search skips empty cells efficiently. */
    if (!ofm) return -1;
    for (int i = 0; i < ofm->capacity; i++)
        if (ofm->keys[i] == key) return i;
    return -1;
}

bool ofm_order(const OrderedFile *ofm, int key_a, int key_b) {
    if (!ofm) return false;
    int ia = ofm_search(ofm, key_a);
    int ib = ofm_search(ofm, key_b);
    if (ia < 0 || ib < 0) return false;
    return ia < ib;
}

int ofm_size(const OrderedFile *ofm) {
    return ofm ? ofm->n : 0;
}

void ofm_print(const OrderedFile *ofm) {
    if (!ofm) { printf("(null)\n"); return; }
    printf("OFM [capacity=%d, n=%d]: ", ofm->capacity, ofm->n);
    for (int i = 0; i < ofm->capacity; i++) {
        if (ofm->keys[i] == OFM_EMPTY_KEY) printf("_ ");
        else printf("%d ", ofm->keys[i]);
    }
    printf("\n");
}

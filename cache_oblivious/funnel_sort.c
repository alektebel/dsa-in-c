/**
 * Funnelsort Implementation
 */

#include "funnel_sort.h"
#include <stdlib.h>
#include <string.h>

/* ---- Standard merge sort (base case / fallback) ---- */

static void merge(int *arr, int *tmp, int lo, int mid, int hi) {
    for (int i = lo; i < hi; i++) tmp[i] = arr[i];
    int l = lo, r = mid, k = lo;
    while (l < mid && r < hi)
        arr[k++] = (tmp[l] <= tmp[r]) ? tmp[l++] : tmp[r++];
    while (l < mid) arr[k++] = tmp[l++];
    while (r < hi)  arr[k++] = tmp[r++];
}

static void merge_sort_internal(int *arr, int *tmp, int lo, int hi) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    merge_sort_internal(arr, tmp, lo, mid);
    merge_sort_internal(arr, tmp, mid, hi);
    merge(arr, tmp, lo, mid, hi);
}

/* ---- Funnelsort top-level ---- */

void funnel_sort(int *arr, int n) {
    /* TODO: Implement cache-oblivious Funnelsort.
     *
     * Recursive structure:
     *   if n <= threshold: insertion_sort or merge_sort
     *   k = ceil(n^{1/3})
     *   group_size = ceil(n / k)
     *   for each group: recursively funnel_sort the group
     *   Create a k-way funnel merger
     *   Use funnel to merge k sorted groups into output
     *
     * For now, fall back to merge sort (O(n log n), O(n) space)
     * while the funnel infrastructure is being built. */
    if (!arr || n <= 1) return;
    int *tmp = (int *)malloc((size_t)n * sizeof(int));
    if (!tmp) return; /* fallback: do nothing on alloc failure */
    merge_sort_internal(arr, tmp, 0, n);
    free(tmp);
}

FunnelNode *funnel_create(int k, int buf_size) {
    /* TODO: Allocate and initialise the funnel tree.
     * - A k-merger has a binary tree structure with k leaves.
     * - Each internal node has an output buffer of size sqrt(k)^3.
     * - Recursively create left and right halves (each k/2-mergers). */
    if (k <= 0 || buf_size <= 0) return NULL;
    FunnelNode *node = (FunnelNode *)calloc(1, sizeof(FunnelNode));
    if (!node) return NULL;
    node->k = k;
    node->output_buf.data = (int *)malloc((size_t)buf_size * sizeof(int));
    if (!node->output_buf.data) { free(node); return NULL; }
    node->output_buf.capacity = buf_size;
    node->output_buf.head = 0;
    node->output_buf.tail = 0;
    node->is_leaf = (k == 1);
    return node;
}

void funnel_destroy(FunnelNode *funnel) {
    /* TODO: Recursively free all sub-funnels and buffers. */
    if (!funnel) return;
    free(funnel->output_buf.data);
    free(funnel->input_ptrs);
    free(funnel);
}

int funnel_fill(FunnelNode *funnel) {
    /* TODO: Implement the funnel fill procedure.
     * If leaf: copy elements from leaf_data[leaf_pos..] into output_buf.
     * Else:
     *   Recursively fill left and right halves.
     *   Merge their output buffers into this node's output buffer.
     *   Repeat until output buffer is full or inputs are exhausted. */
    if (!funnel) return 0;
    return 0;
}

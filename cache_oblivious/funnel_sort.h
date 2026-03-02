/**
 * Funnelsort (Cache-Oblivious Sorting) Implementation
 *
 * Funnelsort (Frigo, Leiserson, Prokop & Ramachandran, 1999) is a cache-
 * oblivious comparison-based sorting algorithm that achieves the optimal
 * number of cache misses: O((N/B) log_{M/B}(N/B)), where N is the input
 * size, B is the cache-line size, and M is the cache size—matching the
 * cache-aware merge sort lower bound without knowing B or M.
 *
 * Key idea:
 *   A k-merger ("funnel") merges k sorted sequences using a binary tree of
 *   buffers, where each buffer has a carefully chosen size (k^3 for the
 *   root, recursively smaller toward the leaves).  When the input fits in
 *   cache, all merges happen in cache; when it doesn't, the recursive
 *   structure ensures optimal cache use at every level.
 *
 * Algorithm:
 *   1. Divide the input into N^{2/3} groups of size N^{1/3}.
 *   2. Recursively sort each group.
 *   3. Merge all groups using a N^{1/3}-merger.
 *
 * Real-Life Use Cases:
 * 1. External Sort in Databases: Database engines sort data larger than
 *    RAM for ORDER BY, GROUP BY, and sort-merge joins.  A cache-oblivious
 *    sort automatically adapts to the disk block size, the OS read-ahead
 *    buffer, and the CPU cache hierarchy without manual tuning—unlike
 *    explicit k-way merge sorts that require manual block-size parameters.
 * 2. Cache-Efficient Parallel Sorting: High-performance computing frameworks
 *    (e.g., sorting in MPI-based systems) benefit from cache-oblivious sort
 *    within each node, reducing NUMA and cache effects before inter-node
 *    communication, improving overall throughput for data-intensive HPC jobs.
 * 3. Scientific Simulation Data Pipeline: Post-processing pipelines for
 *    molecular dynamics or climate simulations sort multi-terabyte
 *    trajectory files.  Cache-oblivious sorting minimises both L3 cache
 *    and disk I/O automatically as data size transitions from fitting in
 *    RAM to requiring disk-based sorting.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 17 (Apr 28, 2003)
 *   - Frigo, Leiserson, Prokop & Ramachandran, "Cache-Oblivious Algorithms",
 *     FOCS 1999
 */

#ifndef FUNNEL_SORT_H
#define FUNNEL_SORT_H

#include <stddef.h>
#include <stdbool.h>

/**
 * Buffer node in the funnel merger tree.
 * Each buffer is a segment of a shared array.
 */
typedef struct FunnelBuffer {
    int *data;      /* Buffer storage */
    int capacity;   /* Total capacity */
    int head;       /* Read pointer */
    int tail;       /* Write pointer (exclusive) */
} FunnelBuffer;

/**
 * A k-merger funnel node.
 */
typedef struct FunnelNode {
    int k;                    /* Arity (number of input streams) */
    FunnelBuffer output_buf;  /* Output buffer for this node */
    struct FunnelNode **left_half;  /* Left k/2 input funnels */
    struct FunnelNode **right_half; /* Right k/2 input funnels */
    int *input_ptrs;          /* Current read positions in leaf streams */
    bool is_leaf;             /* True if this is a leaf (reads from sorted array) */
    int *leaf_data;           /* Pointer to sorted leaf data */
    int leaf_size;            /* Size of leaf data */
    int leaf_pos;             /* Current read position in leaf */
} FunnelNode;

/**
 * Sort an integer array in ascending order using Funnelsort.
 * @param arr  Array to sort (modified in place)
 * @param n    Number of elements
 */
void funnel_sort(int *arr, int n);

/**
 * Create a k-merger funnel for merging k sorted sequences.
 * @param k         Number of input sequences (must be a power of 2)
 * @param buf_size  Total buffer size (k^3 elements)
 * @return Pointer to the funnel node, or NULL on failure
 */
FunnelNode *funnel_create(int k, int buf_size);

/**
 * Destroy a funnel and free all memory.
 * @param funnel  The funnel to destroy
 */
void funnel_destroy(FunnelNode *funnel);

/**
 * Fill the output buffer of a funnel by merging its inputs.
 * @param funnel  The funnel to fill
 * @return Number of elements placed in the output buffer
 */
int funnel_fill(FunnelNode *funnel);

#endif /* FUNNEL_SORT_H */

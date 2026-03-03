/**
 * Cache-Oblivious Linked List Implementation
 *
 * A cache-oblivious linked list achieves optimal cache efficiency for
 * sequential scans without requiring knowledge of the cache parameters
 * (block size B and cache size M).  The key idea is to embed the list nodes
 * into a packed-memory array (ordered-file structure) so that logically
 * adjacent nodes are also near each other in memory.
 *
 * Properties:
 *  - Sequential scan: O(N/B) cache misses (optimal)
 *  - Insert/Delete: O(log^2 N) amortized cache misses
 *    (due to ordered-file maintenance rebalancing)
 *  - For comparison, a pointer-based linked list causes O(N) cache misses
 *    on a sequential scan of N random nodes.
 *
 * Real-Life Use Cases:
 * 1. In-Memory Database Table Scans: A database engine performing a full
 *    table scan benefits from cache-oblivious list storage: logically
 *    sequential rows are physically sequential, so the scan runs at near
 *    memory bandwidth regardless of whether the table fits in L1, L2, or
 *    L3 cache—no explicit cache-blocking or SIMD is needed.
 * 2. Cache-Oblivious B-Tree Leaf Layer: The leaf layer of a cache-oblivious
 *    B-tree (Bender et al. 2000) is exactly a packed-memory array/ordered
 *    list.  Databases like TokuDB (now Percona) use fractional cascading and
 *    cache-oblivious layouts for write-optimized trees with good read
 *    performance across all levels of the memory hierarchy.
 * 3. Streaming Graph Processing: Graph frameworks that process edges in
 *    adjacency-list order (e.g., BFS, PageRank) achieve better cache
 *    utilization when adjacency lists are stored in a cache-oblivious
 *    ordered structure rather than traditional heap-allocated linked nodes,
 *    reducing TLB and cache pressure for irregular memory access patterns.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 15 (Apr 16, 2003)
 *   - Bender, Demaine & Farach-Colton, "Cache-Oblivious B-Trees", FOCS 2000
 */

#ifndef CACHE_OBLIVIOUS_LIST_H
#define CACHE_OBLIVIOUS_LIST_H

#include <stdbool.h>
#include <stddef.h>

#define COL_EMPTY  (-1)  /* Sentinel for empty cell */

/**
 * A single element in the cache-oblivious list.
 * Stored in a packed-memory array; the array index encodes ordering.
 */
typedef struct COLElement {
    int key;            /* Sort key (COL_EMPTY = empty cell) */
    void *data;         /* Associated data */
} COLElement;

/**
 * Cache-oblivious linked list structure.
 * Backed by a packed-memory array for cache-friendly sequential access.
 */
typedef struct COList {
    COLElement *array;  /* Packed-memory array */
    int capacity;       /* Total array size (power of 2) */
    int n;              /* Number of elements stored */
    int height;         /* log2(capacity) */
} COList;

/**
 * Create an empty cache-oblivious list.
 * @param initial_capacity  Initial size (rounded to next power of 2)
 * @return Pointer to the new list, or NULL on failure
 */
COList *col_create(int initial_capacity);

/**
 * Destroy the list and free all memory.
 * @param list  The list to destroy
 */
void col_destroy(COList *list);

/**
 * Insert a key-value pair, maintaining sorted order.
 * @param list  The list
 * @param key   Key to insert
 * @param data  Associated data
 * @return true on success
 */
bool col_insert(COList *list, int key, void *data);

/**
 * Delete a key from the list.
 * @param list  The list
 * @param key   Key to delete
 * @return true if found and deleted
 */
bool col_delete(COList *list, int key);

/**
 * Search for a key using binary search.
 * @param list  The list
 * @param key   Key to search
 * @return Index of the key in the array, or -1 if not found
 */
int col_search(const COList *list, int key);

/**
 * Perform a sequential scan, calling callback for each element in order.
 * This traversal achieves O(N/B) cache misses.
 * @param list      The list
 * @param callback  Function called with (key, data) for each element
 * @param user_data Passed through to callback
 */
void col_scan(const COList *list,
              void (*callback)(int key, void *data, void *user_data),
              void *user_data);

/**
 * Return the number of elements.
 * @param list  The list
 * @return element count
 */
int col_size(const COList *list);

#endif /* CACHE_OBLIVIOUS_LIST_H */

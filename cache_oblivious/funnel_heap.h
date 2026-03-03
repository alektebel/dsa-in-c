/**
 * Funnelheap (Cache-Oblivious Priority Queue) Implementation
 *
 * The Funnelheap (Brodal & Fagerberg, 2002) is a cache-oblivious priority
 * queue that achieves the optimal cache-oblivious bounds:
 *  - Insert:    O(log_2 N / B) amortized cache misses
 *  - Delete-min: O(log_2 N / B) amortized cache misses
 * matching the cache-aware lower bound of Ω((1/B) log_{M/B}(N/B)).
 *
 * Structure:
 *   A collection of up to log N sorted sequences (levels), arranged like a
 *   binary heap of sorted lists.  Each level i contains at most 2^i elements.
 *   Insertions add to level 0; when a level overflows, it is merged with the
 *   next level using a 2-merger (funnel).  Delete-min scans the minimums of
 *   all levels in O(log N) time.
 *
 * Real-Life Use Cases:
 * 1. External-Memory Dijkstra's Algorithm: Graph shortest-path algorithms
 *    on massive graphs (road networks, social networks) use priority queues.
 *    The Funnelheap's cache-oblivious bounds mean optimal disk I/O for
 *    external-memory Dijkstra without specifying disk block sizes, enabling
 *    efficient route planning on continental road networks.
 * 2. Event-Driven Simulation: Discrete-event simulators (networking,
 *    physics, logistics) process billions of timestamped events ordered by
 *    timestamp.  Funnelheap provides cache-efficient priority queue
 *    operations that automatically exploit L1/L2/L3 cache and disk, giving
 *    better throughput than heap-based approaches for large simulations.
 * 3. K-Way External Merge Sort: The merge phase of an external sort uses
 *    a priority queue to select the minimum among k runs.  A cache-oblivious
 *    priority queue automatically selects the right k based on available
 *    cache, matching the performance of a manually tuned k-way merge.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 17 (Apr 28, 2003)
 *   - Brodal & Fagerberg, "Cache-Oblivious Data Structures and Algorithms
 *     for Undirected Breadth-First Search and Shortest Paths", 2004
 */

#ifndef FUNNEL_HEAP_H
#define FUNNEL_HEAP_H

#include <stdbool.h>
#include <stddef.h>

#define FH_MAX_LEVELS 64  /* Supports up to 2^64 elements */

/**
 * A sorted buffer (level) in the funnelheap.
 */
typedef struct FHLevel {
    int *data;      /* Sorted array of keys */
    int size;       /* Number of elements */
    int capacity;   /* Allocated capacity */
} FHLevel;

/**
 * Funnelheap priority queue.
 */
typedef struct FunnelHeap {
    FHLevel levels[FH_MAX_LEVELS]; /* Sorted levels */
    int num_levels;                /* Number of active levels */
    int n;                         /* Total number of elements */
} FunnelHeap;

/**
 * Create an empty funnelheap.
 * @return Pointer to the new funnelheap, or NULL on failure
 */
FunnelHeap *fheap_create(void);

/**
 * Destroy the funnelheap and free all memory.
 * @param heap  The funnelheap to destroy
 */
void fheap_destroy(FunnelHeap *heap);

/**
 * Insert a key into the funnelheap.
 * @param heap  The funnelheap
 * @param key   Key to insert
 * @return true on success
 */
bool fheap_insert(FunnelHeap *heap, int key);

/**
 * Find the minimum key without removing it.
 * @param heap  The funnelheap
 * @param key   Output: minimum key
 * @return true if heap is non-empty
 */
bool fheap_find_min(const FunnelHeap *heap, int *key);

/**
 * Remove and return the minimum key.
 * @param heap  The funnelheap
 * @param key   Output: minimum key
 * @return true if heap was non-empty
 */
bool fheap_delete_min(FunnelHeap *heap, int *key);

/**
 * Return the number of elements.
 * @param heap  The funnelheap
 * @return element count
 */
int fheap_size(const FunnelHeap *heap);

/**
 * Check whether the heap is empty.
 * @param heap  The funnelheap
 * @return true if empty
 */
bool fheap_is_empty(const FunnelHeap *heap);

#endif /* FUNNEL_HEAP_H */

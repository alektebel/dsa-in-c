/**
 * Move-to-Front (MTF) List Implementation
 *
 * The move-to-front heuristic is a self-organizing list strategy: whenever
 * an element is accessed, it is moved to the front of the list. This is an
 * online algorithm with the "static optimality" property—over any sequence
 * of accesses it performs within a constant factor of the optimal static
 * ordering—and achieves competitive ratio 2 against the offline optimum.
 *
 * The same idea appears in data compression as the "move-to-front transform"
 * (Lecture 13): given a ranked alphabet, each symbol is encoded by its
 * current rank in the MTF list, then the symbol is moved to the front.
 * This concentrates small integers near frequently used symbols.
 *
 * Real-Life Use Cases:
 * 1. CPU Cache / TLB Replacement (Approximate LRU): The LRU eviction policy
 *    is equivalent to maintaining a move-to-front list of cache lines.  When
 *    a cache line is accessed it moves to the front; the back of the list is
 *    evicted on a miss.  This is implemented in Linux's "clock-pro" and
 *    "two-list" page replacement policies.
 * 2. Adaptive Huffman / BWT Compression: The move-to-front transform is a
 *    post-processing step in bzip2 (after BWT): it converts a run-biased
 *    sequence of bytes into a sequence of small integers amenable to
 *    run-length encoding and Huffman coding, achieving near-entropy
 *    compression without a static frequency table.
 * 3. Self-Organizing Menus / Recently-Used Lists: Operating systems and
 *    applications maintain "recently used" lists (recently opened files,
 *    recently visited URLs) using the MTF rule, prioritizing likely future
 *    accesses at the top of the list.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lectures 5 & 6 (Feb 26 – Mar 3, 2003)
 *   - Sleator & Tarjan, "Amortized Efficiency of List Update and Paging Rules",
 *     CACM 1985
 */

#ifndef MOVE_TO_FRONT_H
#define MOVE_TO_FRONT_H

#include <stdbool.h>
#include <stddef.h>

/* -----------------------------------------------------------------------
 * Self-organizing linked list with move-to-front
 * ----------------------------------------------------------------------- */

/** Node in the move-to-front list. */
typedef struct MTFNode {
    int key;
    void *data;
    struct MTFNode *next;
    struct MTFNode *prev;
} MTFNode;

/** Move-to-front doubly-linked list. */
typedef struct MTFList {
    MTFNode *head;
    MTFNode *tail;
    size_t size;
} MTFList;

/**
 * Create an empty move-to-front list.
 * @return Pointer to the new list, or NULL on failure
 */
MTFList *mtf_list_create(void);

/**
 * Destroy the move-to-front list and free all memory.
 * @param list  The list to destroy
 */
void mtf_list_destroy(MTFList *list);

/**
 * Insert a key-value pair at the front of the list.
 * @param list  The list
 * @param key   Key to insert
 * @param data  Associated data
 * @return true on success
 */
bool mtf_list_insert(MTFList *list, int key, void *data);

/**
 * Access a key: find the node and move it to the front.
 * This is the core move-to-front operation.
 * @param list  The list
 * @param key   Key to access
 * @return Pointer to the node (now at front), or NULL if not found
 */
MTFNode *mtf_list_access(MTFList *list, int key);

/**
 * Delete a key from the list.
 * @param list  The list
 * @param key   Key to delete
 * @return true if found and deleted
 */
bool mtf_list_delete(MTFList *list, int key);

/**
 * Return the number of elements.
 * @param list  The list
 * @return size
 */
size_t mtf_list_size(const MTFList *list);

/* -----------------------------------------------------------------------
 * Move-to-Front transform (for compression)
 * ----------------------------------------------------------------------- */

/**
 * Apply the MTF transform to a byte sequence.
 * Each byte is encoded as its current rank in the MTF alphabet list
 * (initially [0, 1, 2, ..., 255]), then moved to rank 0.
 *
 * @param input   Input byte array
 * @param output  Output rank array (caller allocates, same length)
 * @param n       Length of input/output arrays
 */
void mtf_transform(const unsigned char *input, int *output, int n);

/**
 * Invert the MTF transform.
 * @param input   Input rank array
 * @param output  Output byte array (caller allocates, same length)
 * @param n       Length of arrays
 */
void mtf_inverse_transform(const int *input, unsigned char *output, int n);

#endif /* MOVE_TO_FRONT_H */

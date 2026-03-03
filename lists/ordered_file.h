/**
 * Ordered-File Maintenance (OFM) Implementation
 *
 * An ordered-file (or packed-memory array) maintains n elements in sorted
 * order in an array of size O(n), supporting:
 *  - Ordered scan:   O(n) time
 *  - Lookup (rank):  O(log n) binary search
 *  - Insert/Delete:  O(log^2 n) amortized (with rebalancing)
 *
 * The structure supports "order queries" on lists: given a pointer to any
 * two elements, determine their relative order in O(1) time by comparing
 * their array positions (after O(log^2 n) inserts).
 *
 * Real-Life Use Cases:
 * 1. Cache-Oblivious B-Trees (van Emde Boas Layout): Ordered-file maintenance
 *    is the dynamic insertion layer in cache-oblivious B-trees.  Databases
 *    like VoltDB and SAP HANA use packed-memory arrays to keep sorted key
 *    arrays cache-friendly across levels of the memory hierarchy without
 *    explicit block-size parameters.
 * 2. Persistent / Versioned Data Stores: A persistent sorted array that
 *    supports efficient inserts while maintaining element positions is used
 *    in version-control systems and append-heavy databases where historical
 *    order queries ("which record was inserted first?") are needed in O(1).
 * 3. List Labeling for Order-Maintenance: The "list labeling" problem asks
 *    for integer labels for a dynamic ordered set so that relative order is
 *    determined by numeric comparison.  Ordered-file maintenance solves this
 *    with O(log^2 n) amortized label updates, used in persistent red-black
 *    trees and link-cut trees.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 14 (Apr 14, 2003)
 *   - Itai, Konheim & Rodeh, "A sparse table implementation of priority queues",
 *     ICALP 1981
 *   - Bender et al., "Two Simplified Algorithms for Maintaining Order in a List",
 *     ESA 2002
 */

#ifndef ORDERED_FILE_H
#define ORDERED_FILE_H

#include <stdbool.h>
#include <stddef.h>

/** Sentinel value for an empty cell in the packed-memory array. */
#define OFM_EMPTY_KEY  (-1)

/**
 * Ordered-file (packed-memory array) structure.
 * Elements are stored in a partially filled array such that the density
 * in every contiguous region of length 2^k stays within the bounds
 * [lower_threshold(k), upper_threshold(k)].
 */
typedef struct OrderedFile {
    int *keys;          /* Packed-memory array; OFM_EMPTY_KEY = empty cell */
    int capacity;       /* Total allocated cells (always a power of 2) */
    int n;              /* Number of elements currently stored */
    int height;         /* log2(capacity) = tree height for analysis */
} OrderedFile;

/**
 * Create an ordered file with the given initial capacity.
 * @param initial_capacity  Initial cell count (will be rounded up to 2^k)
 * @return Pointer to the new ordered file, or NULL on failure
 */
OrderedFile *ofm_create(int initial_capacity);

/**
 * Destroy the ordered file and free all memory.
 * @param ofm  The ordered file to destroy
 */
void ofm_destroy(OrderedFile *ofm);

/**
 * Insert a key into the ordered file, maintaining sorted order.
 * @param ofm  The ordered file
 * @param key  Key to insert (must not equal OFM_EMPTY_KEY)
 * @return true on success, false on failure
 */
bool ofm_insert(OrderedFile *ofm, int key);

/**
 * Delete a key from the ordered file.
 * @param ofm  The ordered file
 * @param key  Key to delete
 * @return true if found and deleted, false otherwise
 */
bool ofm_delete(OrderedFile *ofm, int key);

/**
 * Search for a key using binary search over occupied cells.
 * @param ofm  The ordered file
 * @param key  Key to search
 * @return Index in the array, or -1 if not found
 */
int ofm_search(const OrderedFile *ofm, int key);

/**
 * Order query: return true if key_a comes before key_b in the sorted order.
 * Works in O(1) by comparing array positions.
 * @param ofm    The ordered file
 * @param key_a  First key
 * @param key_b  Second key
 * @return true if key_a < key_b in the stored order
 */
bool ofm_order(const OrderedFile *ofm, int key_a, int key_b);

/**
 * Return the number of elements stored.
 * @param ofm  The ordered file
 * @return element count
 */
int ofm_size(const OrderedFile *ofm);

/**
 * Print the ordered file contents (for debugging).
 * @param ofm  The ordered file
 */
void ofm_print(const OrderedFile *ofm);

#endif /* ORDERED_FILE_H */

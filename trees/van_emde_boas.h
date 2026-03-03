/**
 * Van Emde Boas Tree Implementation
 *
 * The van Emde Boas (vEB) tree is a tree data structure that implements an
 * associative array with integer keys in the range [0, U-1]. It achieves
 * O(log log U) time for search, insert, delete, successor, and predecessor
 * operations, where U is the universe size.
 *
 * Real-Life Use Cases:
 * 1. Network Routing (IP address lookup): Router lookup tables store IP
 *    addresses (32-bit integers) as keys. vEB trees allow routers to find
 *    the next-hop for a destination IP in O(log log 2^32) = O(log 32) = O(5)
 *    time—effectively O(1) for 32-bit universes—much faster than balanced BSTs.
 * 2. Operating System Process Scheduling: An OS scheduler maintains a
 *    set of runnable process IDs (bounded by the max PID, e.g., 2^22).
 *    vEB trees let the scheduler find the highest- or lowest-priority
 *    runnable process in O(log log U) time, outperforming heaps for
 *    dense PID spaces.
 * 3. Calendar / Event Scheduling: Timestamps discretized to seconds
 *    within a year (~31 million values) can be stored in a vEB tree so
 *    that the next upcoming event is retrieved in O(log log 3.1e7) ≈ O(5)
 *    steps, enabling very fast "what's next?" queries in calendar apps.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 1 (Feb 10, 2003)
 *   - van Emde Boas, "Preserving order in a forest in less than logarithmic
 *     time", 1975
 */

#ifndef VAN_EMDE_BOAS_H
#define VAN_EMDE_BOAS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Special value representing "no element" (empty min/max). */
#define VEB_EMPTY (-1)

/**
 * Van Emde Boas tree node.
 * For universe size U = 2^k, the tree recursively splits into sqrt(U)
 * clusters each of size sqrt(U), plus a summary structure of size sqrt(U).
 */
typedef struct VEB {
    int universe;       /* Universe size (must be a power of two) */
    int min;            /* Minimum element stored (-1 if empty) */
    int max;            /* Maximum element stored (-1 if empty) */
    struct VEB *summary;/* Summary structure over clusters */
    struct VEB **cluster;/* Array of sqrt(U) sub-trees */
} VEB;

/**
 * Create a new van Emde Boas tree for universe [0, universe-1].
 * @param universe  Size of the universe (should be a power of 2)
 * @return Pointer to newly created vEB tree, or NULL on failure
 */
VEB *veb_create(int universe);

/**
 * Destroy a vEB tree and free all allocated memory.
 * @param tree  The vEB tree to destroy
 */
void veb_destroy(VEB *tree);

/**
 * Check whether the vEB tree is empty.
 * @param tree  The vEB tree
 * @return true if empty, false otherwise
 */
bool veb_is_empty(const VEB *tree);

/**
 * Insert a key into the vEB tree.
 * @param tree  The vEB tree
 * @param key   Key to insert (must be in [0, universe-1])
 */
void veb_insert(VEB *tree, int key);

/**
 * Delete a key from the vEB tree.
 * @param tree  The vEB tree
 * @param key   Key to delete (must currently be present)
 */
void veb_delete(VEB *tree, int key);

/**
 * Check whether a key is present in the vEB tree.
 * @param tree  The vEB tree
 * @param key   Key to look up
 * @return true if key is present, false otherwise
 */
bool veb_member(const VEB *tree, int key);

/**
 * Find the minimum key in the vEB tree.
 * @param tree  The vEB tree
 * @return Minimum key, or VEB_EMPTY if tree is empty
 */
int veb_minimum(const VEB *tree);

/**
 * Find the maximum key in the vEB tree.
 * @param tree  The vEB tree
 * @return Maximum key, or VEB_EMPTY if tree is empty
 */
int veb_maximum(const VEB *tree);

/**
 * Find the successor of a key (smallest key strictly greater than key).
 * @param tree  The vEB tree
 * @param key   The query key
 * @return Successor key, or VEB_EMPTY if none exists
 */
int veb_successor(const VEB *tree, int key);

/**
 * Find the predecessor of a key (largest key strictly less than key).
 * @param tree  The vEB tree
 * @param key   The query key
 * @return Predecessor key, or VEB_EMPTY if none exists
 */
int veb_predecessor(const VEB *tree, int key);

#endif /* VAN_EMDE_BOAS_H */

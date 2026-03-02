/**
 * Y-Fast Trie Implementation
 *
 * The y-fast trie (Willard, 1983) is a data structure for the fixed-universe
 * predecessor/successor problem that achieves O(log log U) time per operation
 * and O(n) space, improving over the van Emde Boas tree's O(U) space.
 *
 * Structure:
 *   - A perfect hash table (x-fast trie) stores O(n) representatives,
 *     one per block of size floor(log U / 2).
 *   - Each block is maintained as a balanced BST (e.g., a red-black tree)
 *     allowing O(log log U) operations within a block.
 *
 * Real-Life Use Cases:
 * 1. IP Routing with Memory Constraints: Like vEB trees, y-fast tries
 *    support O(log log U) next-hop lookups for 32-bit IP addresses, but
 *    use only O(n) space—critical for routers storing only the active
 *    prefix set rather than the full 2^32 universe.
 * 2. Database Index with Bounded Key Range: A database indexing integer
 *    primary keys in a known range can use a y-fast trie to answer range
 *    queries ("all rows with key in [a,b]") efficiently while keeping
 *    memory proportional to the number of stored rows, not the key range.
 * 3. Real-Time Sensor Data Processing: Sensor readings discretized to
 *    integer microsecond timestamps within a day (86,400,000 values) can
 *    be stored in a y-fast trie so the system quickly finds the next
 *    scheduled event or the closest past reading without allocating memory
 *    for all possible timestamps.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 2 (Feb 12, 2003)
 *   - Willard, "Log-logarithmic worst-case range queries are possible in
 *     space Θ(N)", 1983
 */

#ifndef Y_FAST_TRIE_H
#define Y_FAST_TRIE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define YFAST_EMPTY (-1)

/**
 * A single node inside a y-fast trie block (stored in the local BST).
 */
typedef struct YFastNode {
    int key;
    struct YFastNode *left;
    struct YFastNode *right;
} YFastNode;

/**
 * A block (cluster) in the y-fast trie.
 * Each block holds at most O(log U) consecutive keys in a balanced BST.
 */
typedef struct YFastBlock {
    int representative;     /* Representative key stored in the x-fast layer */
    YFastNode *bst_root;    /* Root of the local balanced BST */
    int size;               /* Number of keys in this block */
    struct YFastBlock *next;/* Linked list of blocks (for traversal) */
} YFastBlock;

/**
 * Y-fast trie top-level structure.
 */
typedef struct YFastTrie {
    int universe;           /* Universe size U */
    int log_u;              /* log2(U) */
    int block_size;         /* Target block size = log_u / 2 */
    YFastBlock **table;     /* Hash table mapping representatives -> blocks */
    int table_size;         /* Size of the hash table */
    int n;                  /* Total number of elements stored */
    YFastBlock *head;       /* Head of sorted block list */
} YFastTrie;

/**
 * Create a new y-fast trie for universe [0, universe-1].
 * @param universe  Universe size (typically a power of 2)
 * @return Pointer to newly created y-fast trie, or NULL on failure
 */
YFastTrie *yfast_create(int universe);

/**
 * Destroy the y-fast trie and free all memory.
 * @param trie  The trie to destroy
 */
void yfast_destroy(YFastTrie *trie);

/**
 * Insert a key into the y-fast trie.
 * @param trie  The y-fast trie
 * @param key   Key to insert (must be in [0, universe-1])
 * @return true on success, false on failure
 */
bool yfast_insert(YFastTrie *trie, int key);

/**
 * Delete a key from the y-fast trie.
 * @param trie  The y-fast trie
 * @param key   Key to delete
 * @return true if key was found and deleted, false otherwise
 */
bool yfast_delete(YFastTrie *trie, int key);

/**
 * Check if a key is present in the y-fast trie.
 * @param trie  The y-fast trie
 * @param key   Key to look up
 * @return true if present, false otherwise
 */
bool yfast_member(const YFastTrie *trie, int key);

/**
 * Find the successor of key (smallest stored key strictly greater than key).
 * @param trie  The y-fast trie
 * @param key   Query key
 * @return Successor, or YFAST_EMPTY if none
 */
int yfast_successor(const YFastTrie *trie, int key);

/**
 * Find the predecessor of key (largest stored key strictly less than key).
 * @param trie  The y-fast trie
 * @param key   Query key
 * @return Predecessor, or YFAST_EMPTY if none
 */
int yfast_predecessor(const YFastTrie *trie, int key);

/**
 * Return the minimum key stored in the trie.
 * @param trie  The y-fast trie
 * @return Minimum key, or YFAST_EMPTY if trie is empty
 */
int yfast_minimum(const YFastTrie *trie);

/**
 * Return the maximum key stored in the trie.
 * @param trie  The y-fast trie
 * @return Maximum key, or YFAST_EMPTY if trie is empty
 */
int yfast_maximum(const YFastTrie *trie);

#endif /* Y_FAST_TRIE_H */

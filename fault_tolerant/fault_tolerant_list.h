/**
 * Fault-Tolerant Linked List Implementation
 *
 * A fault-tolerant linked list stores elements in the presence of up to δ
 * memory faults in the unsafe storage region.  The approach (Lecture 19)
 * uses:
 *  1. A small "safe" header in fault-free memory holding the head pointer
 *     and element count.
 *  2. Each node stores its data along with a checksum/magic value and a
 *     redundant next-pointer so that a single corruption of either pointer
 *     or data can be detected (and skipped).
 *  3. Traversal validates each node before using it; corrupted nodes are
 *     transparently skipped.
 *
 * Operations:
 *  - Insert (front): O(1)
 *  - Delete:         O(n + δ)
 *  - Traversal:      O(n + δ) (visits at most n + δ cells)
 *
 * Real-Life Use Cases:
 * 1. Fault-Tolerant File System Metadata: A file system journal (e.g., ext4,
 *    btrfs) maintains a linked list of pending transactions in memory.  A
 *    fault-tolerant list for the in-memory journal ensures that a cosmic-ray
 *    or hardware bit-flip does not corrupt the journal chain, preventing
 *    filesystem corruption on the next crash or power-off.
 * 2. Safety-Critical Real-Time Systems (Automotive / Avionics): AUTOSAR
 *    and DO-178C standards require that safety-critical software handles
 *    transient memory errors.  A fault-tolerant linked list for the task
 *    queue of a real-time OS ensures the scheduler remains correct even
 *    if a memory cell is flipped by an EMI pulse.
 * 3. Persistent Memory (NVM) Event Log: Write-ahead logs in databases on
 *    NVM media are linked lists of log records.  Fault-tolerant linked lists
 *    with per-node checksums allow the database to recover a partially
 *    corrupted log on restart by detecting and skipping bad records, rather
 *    than aborting recovery entirely.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 19 (May 5, 2003)
 *   - Finocchi, Grandoni & Italiano, "Resilient Dictionaries", TALG 2009
 */

#ifndef FAULT_TOLERANT_LIST_H
#define FAULT_TOLERANT_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FTL_MAGIC   0xCAFEBABEu  /* Magic value for node validation */
#define FTL_DELTA   8            /* Default fault tolerance */

/**
 * A node in the fault-tolerant linked list.
 */
typedef struct FTLNode {
    uint32_t magic;         /* Must equal FTL_MAGIC */
    int key;                /* Node key */
    void *data;             /* Associated data */
    struct FTLNode *next;   /* Forward pointer */
    struct FTLNode *next_copy; /* Redundant copy of next pointer */
    uint32_t checksum;      /* Simple checksum over key and data pointer */
} FTLNode;

/**
 * Fault-tolerant linked list.
 */
typedef struct FTList {
    FTLNode *head;          /* "Safe" head pointer */
    int n;                  /* Trusted element count (in safe memory) */
    int delta;              /* Fault tolerance parameter */
} FTList;

/**
 * Compute the checksum for a node's key and data.
 * @param key   Node key
 * @param data  Node data pointer
 * @return Checksum value
 */
uint32_t ftl_checksum(int key, const void *data);

/**
 * Check whether a node is valid (not corrupted).
 * @param node  The node to check
 * @return true if magic, checksum, and next pointers are consistent
 */
bool ftl_node_valid(const FTLNode *node);

/**
 * Create an empty fault-tolerant linked list.
 * @param delta  Maximum number of faults to tolerate
 * @return Pointer to the new list, or NULL on failure
 */
FTList *ftl_create(int delta);

/**
 * Destroy the list, freeing all (reachable, valid) nodes.
 * @param list  The list to destroy
 */
void ftl_destroy(FTList *list);

/**
 * Insert a key-value pair at the front of the list.
 * @param list  The list
 * @param key   Key
 * @param data  Data pointer
 * @return true on success
 */
bool ftl_insert(FTList *list, int key, void *data);

/**
 * Delete the first valid node with the given key.
 * @param list  The list
 * @param key   Key to delete
 * @return true if found and deleted
 */
bool ftl_delete(FTList *list, int key);

/**
 * Search for the first valid node with the given key.
 * Skips corrupted nodes (up to delta of them).
 * @param list  The list
 * @param key   Key to search
 * @return Pointer to the found node, or NULL
 */
FTLNode *ftl_search(FTList *list, int key);

/**
 * Traverse all valid nodes, calling callback for each.
 * @param list      The list
 * @param callback  Called with (key, data, user_data) for each valid node
 * @param user_data Passed through to callback
 */
void ftl_traverse(FTList *list,
                  void (*callback)(int key, void *data, void *user_data),
                  void *user_data);

/**
 * Return the trusted element count.
 * @param list  The list
 * @return element count
 */
int ftl_size(const FTList *list);

/**
 * Inject a fault into a node at the given position (for testing).
 * @param list  The list
 * @param pos   0-indexed position of the node to corrupt
 */
void ftl_inject_fault(FTList *list, int pos);

#endif /* FAULT_TOLERANT_LIST_H */

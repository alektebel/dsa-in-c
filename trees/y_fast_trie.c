/**
 * Y-Fast Trie Implementation
 */

#include "y_fast_trie.h"
#include <stdlib.h>
#include <math.h>

YFastTrie *yfast_create(int universe) {
    /* TODO: Initialize the y-fast trie.
     * 1. Compute log_u = log2(universe), block_size = log_u / 2.
     * 2. Allocate a hash table of size O(n / block_size) for representatives.
     * 3. Set n = 0, head = NULL. */
    YFastTrie *trie = (YFastTrie *)malloc(sizeof(YFastTrie));
    if (!trie) return NULL;
    trie->universe = universe;
    trie->log_u = (int)(log2((double)universe));
    trie->block_size = (trie->log_u > 1) ? (trie->log_u / 2) : 1;
    trie->table_size = 16; /* TODO: choose an appropriate initial size */
    trie->table = (YFastBlock **)calloc((size_t)trie->table_size,
                                        sizeof(YFastBlock *));
    if (!trie->table) { free(trie); return NULL; }
    trie->n = 0;
    trie->head = NULL;
    return trie;
}

void yfast_destroy(YFastTrie *trie) {
    /* TODO: Free all blocks and their BST nodes, then free the hash table
     * and the trie struct. */
    if (!trie) return;
    free(trie->table);
    free(trie);
}

bool yfast_insert(YFastTrie *trie, int key) {
    /* TODO: Implement y-fast trie insertion.
     * 1. Find the block whose representative is the predecessor of key
     *    (or successor if no predecessor block exists).
     * 2. Insert key into that block's local BST.
     * 3. If the block exceeds 2*block_size elements, split it:
     *    - Choose the median as the new representative.
     *    - Update the x-fast (hash table) layer.
     * 4. Increment n. */
    if (!trie) return false;
    return false;
}

bool yfast_delete(YFastTrie *trie, int key) {
    /* TODO: Implement y-fast trie deletion.
     * 1. Locate the block containing key via the hash table.
     * 2. Remove key from the block's local BST.
     * 3. If the block falls below block_size/2 elements, merge with a
     *    neighbor block, or steal elements from it.
     * 4. Update the x-fast layer and decrement n. */
    if (!trie) return false;
    return false;
}

bool yfast_member(const YFastTrie *trie, int key) {
    /* TODO: Search the block corresponding to the successor representative
     * in the x-fast layer, then do a BST lookup within that block. */
    if (!trie) return false;
    return false;
}

int yfast_successor(const YFastTrie *trie, int key) {
    /* TODO: Find the block of the key using the x-fast hash table,
     * search the local BST for a successor, and if not found look at
     * the next block. */
    if (!trie) return YFAST_EMPTY;
    return YFAST_EMPTY;
}

int yfast_predecessor(const YFastTrie *trie, int key) {
    /* TODO: Symmetric to yfast_successor. */
    if (!trie) return YFAST_EMPTY;
    return YFAST_EMPTY;
}

int yfast_minimum(const YFastTrie *trie) {
    /* TODO: Walk to the first (leftmost) block and return its BST minimum. */
    if (!trie || !trie->head) return YFAST_EMPTY;
    return YFAST_EMPTY;
}

int yfast_maximum(const YFastTrie *trie) {
    /* TODO: Walk to the last block and return its BST maximum. */
    if (!trie) return YFAST_EMPTY;
    return YFAST_EMPTY;
}

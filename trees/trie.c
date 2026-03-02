/**
 * Trie (Digital Search Tree / Binary Trie) Implementation
 */

#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================================================
 * Character trie
 * ========================================================= */

static TrieNode *trie_node_create(void) {
    TrieNode *node = (TrieNode *)calloc(1, sizeof(TrieNode));
    return node;
}

Trie *trie_create(void) {
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    if (!trie) return NULL;
    trie->root = trie_node_create();
    if (!trie->root) { free(trie); return NULL; }
    trie->num_keys = 0;
    return trie;
}

static void trie_node_destroy(TrieNode *node) {
    if (!node) return;
    for (int i = 0; i < TRIE_ALPHA_SIZE; i++)
        trie_node_destroy(node->children[i]);
    free(node);
}

void trie_destroy(Trie *trie) {
    if (!trie) return;
    trie_node_destroy(trie->root);
    free(trie);
}

bool trie_insert(Trie *trie, const char *key) {
    /* TODO: Walk down the trie one character at a time.
     * For each character c = key[i] - 'a':
     *   if children[c] == NULL: allocate a new node.
     *   increment node->count.
     *   advance to children[c].
     * At the terminal node, set is_end = true.
     * Increment trie->num_keys. */
    if (!trie || !key) return false;
    return false;
}

bool trie_search(const Trie *trie, const char *key) {
    /* TODO: Walk down the trie; return true iff the terminal node exists
     * and has is_end == true. */
    if (!trie || !key) return false;
    return false;
}

bool trie_delete(Trie *trie, const char *key) {
    /* TODO: Walk the trie to find the terminal node.
     * On the way back up, decrement counts and free nodes that are no longer
     * needed (count == 0 and not an end of another key). */
    if (!trie || !key) return false;
    return false;
}

int trie_count_prefix(const Trie *trie, const char *prefix) {
    /* TODO: Walk down to the node representing prefix, then return its count.
     * The count field stores the number of keys passing through a node. */
    if (!trie || !prefix) return 0;
    return 0;
}

size_t trie_size(const Trie *trie) {
    return trie ? trie->num_keys : 0;
}

/* =========================================================
 * Binary trie
 * ========================================================= */

static BTrieNode *btrie_node_create(void) {
    BTrieNode *node = (BTrieNode *)calloc(1, sizeof(BTrieNode));
    return node;
}

BTrie *btrie_create(void) {
    BTrie *trie = (BTrie *)malloc(sizeof(BTrie));
    if (!trie) return NULL;
    trie->root = btrie_node_create();
    if (!trie->root) { free(trie); return NULL; }
    trie->num_keys = 0;
    return trie;
}

static void btrie_node_destroy(BTrieNode *node) {
    if (!node) return;
    btrie_node_destroy(node->child[0]);
    btrie_node_destroy(node->child[1]);
    free(node);
}

void btrie_destroy(BTrie *trie) {
    if (!trie) return;
    btrie_node_destroy(trie->root);
    free(trie);
}

bool btrie_insert(BTrie *trie, unsigned int key) {
    /* TODO: Walk from the most-significant bit to the least-significant bit
     * (bit BTRIE_BITS-1 down to 0).  At each level branch on the bit value,
     * creating nodes as needed.  Mark the terminal node is_end = true. */
    if (!trie) return false;
    return false;
}

bool btrie_member(const BTrie *trie, unsigned int key) {
    /* TODO: Walk from MSB to LSB; return is_end of the terminal node. */
    if (!trie) return false;
    return false;
}

bool btrie_delete(BTrie *trie, unsigned int key) {
    /* TODO: Walk to the terminal node, clear is_end.
     * Optionally compress the trie by removing now-redundant nodes. */
    if (!trie) return false;
    return false;
}

bool btrie_successor(const BTrie *trie, unsigned int key, unsigned int *result) {
    /* TODO: Traverse the trie following the bits of key; at each left-turn
     * remember the root of the right subtree.  After the traversal (or when
     * a child is missing), take the leftmost path in the remembered subtree. */
    (void)key;
    if (result) *result = 0;
    return false;
}

bool btrie_predecessor(const BTrie *trie, unsigned int key,
                       unsigned int *result) {
    /* TODO: Symmetric to btrie_successor. */
    (void)key;
    if (result) *result = 0;
    return false;
}

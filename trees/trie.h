/**
 * Trie (Digital Search Tree / Binary Trie) Implementation
 *
 * A trie stores a dynamic set of strings (or integers treated as bit strings)
 * and supports insert, delete, search, and prefix-based operations in time
 * proportional to the key length, independent of the number of keys stored.
 *
 * This file implements a binary trie (each node branches on a single bit)
 * and a general character trie (each node branches on one character from
 * an alphabet of size TRIE_ALPHA_SIZE).
 *
 * Real-Life Use Cases:
 * 1. Auto-Complete and Spell Checking: Text editors and search engines store
 *    a dictionary of words in a trie to quickly enumerate all words sharing
 *    a given prefix. Typing "pre" returns all completions in O(|prefix| + k)
 *    time where k is the number of completions.
 * 2. IP Longest-Prefix Matching: Routers store CIDR prefixes in a binary
 *    trie keyed on the bit representation of IP addresses. For each incoming
 *    packet, a walk down the trie in O(32) or O(128) steps for IPv4/IPv6
 *    finds the longest matching prefix and the corresponding next hop.
 * 3. DNA Sequence Indexing: Bioinformatics tools index genomic sequences
 *    (over the alphabet {A, C, G, T}) in a trie so that substring queries
 *    ("does this read appear in the genome?") run in O(L) time where L is
 *    the sequence length, enabling fast alignment seeding.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lectures 10 & 12 (Mar–Apr 2003)
 *   - Knuth, "The Art of Computer Programming", Vol. 3, §6.3
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stddef.h>

/* -----------------------------------------------------------------------
 * General character trie
 * ----------------------------------------------------------------------- */

#define TRIE_ALPHA_SIZE 26  /* lowercase English letters */

/** Node in a character trie. */
typedef struct TrieNode {
    struct TrieNode *children[TRIE_ALPHA_SIZE];
    bool is_end;            /* True if a key ends at this node */
    int count;              /* Number of keys that pass through this node */
} TrieNode;

/** Character trie. */
typedef struct Trie {
    TrieNode *root;
    size_t num_keys;
} Trie;

/**
 * Create an empty character trie.
 * @return Pointer to the new trie, or NULL on failure
 */
Trie *trie_create(void);

/**
 * Destroy the trie and free all memory.
 * @param trie  The trie to destroy
 */
void trie_destroy(Trie *trie);

/**
 * Insert a key (NUL-terminated string of lowercase letters) into the trie.
 * @param trie  The trie
 * @param key   Key to insert
 * @return true on success, false on failure
 */
bool trie_insert(Trie *trie, const char *key);

/**
 * Search for an exact key in the trie.
 * @param trie  The trie
 * @param key   Key to search
 * @return true if the key is present, false otherwise
 */
bool trie_search(const Trie *trie, const char *key);

/**
 * Delete a key from the trie (if present).
 * @param trie  The trie
 * @param key   Key to delete
 * @return true if key was found and deleted, false otherwise
 */
bool trie_delete(Trie *trie, const char *key);

/**
 * Count how many stored keys share the given prefix.
 * @param trie    The trie
 * @param prefix  The prefix to query
 * @return Number of keys with this prefix
 */
int trie_count_prefix(const Trie *trie, const char *prefix);

/**
 * Return the number of keys stored in the trie.
 * @param trie  The trie
 * @return size
 */
size_t trie_size(const Trie *trie);

/* -----------------------------------------------------------------------
 * Binary trie (keys are non-negative integers treated as w-bit strings)
 * ----------------------------------------------------------------------- */

#define BTRIE_BITS 32  /* Key width in bits */

/** Node in a binary trie. */
typedef struct BTrieNode {
    struct BTrieNode *child[2]; /* child[0] = bit 0, child[1] = bit 1 */
    bool is_end;
} BTrieNode;

/** Binary trie. */
typedef struct BTrie {
    BTrieNode *root;
    size_t num_keys;
} BTrie;

/**
 * Create an empty binary trie.
 * @return Pointer to the new binary trie, or NULL on failure
 */
BTrie *btrie_create(void);

/**
 * Destroy the binary trie and free all memory.
 * @param trie  The binary trie to destroy
 */
void btrie_destroy(BTrie *trie);

/**
 * Insert an unsigned integer key.
 * @param trie  The binary trie
 * @param key   Key to insert
 * @return true on success
 */
bool btrie_insert(BTrie *trie, unsigned int key);

/**
 * Check membership.
 * @param trie  The binary trie
 * @param key   Key to look up
 * @return true if present
 */
bool btrie_member(const BTrie *trie, unsigned int key);

/**
 * Delete a key.
 * @param trie  The binary trie
 * @param key   Key to delete
 * @return true if found and deleted
 */
bool btrie_delete(BTrie *trie, unsigned int key);

/**
 * Find the successor of key (smallest stored key > key).
 * @param trie    The binary trie
 * @param key     Query key
 * @param result  Output: successor key
 * @return true if successor exists
 */
bool btrie_successor(const BTrie *trie, unsigned int key, unsigned int *result);

/**
 * Find the predecessor of key (largest stored key < key).
 * @param trie    The binary trie
 * @param key     Query key
 * @param result  Output: predecessor key
 * @return true if predecessor exists
 */
bool btrie_predecessor(const BTrie *trie, unsigned int key,
                       unsigned int *result);

#endif /* TRIE_H */

/**
 * Fusion Tree Implementation
 *
 * Fusion trees (Fredman & Willard, 1993) are a B-tree variant that uses
 * bitwise tricks and word-level parallelism to answer predecessor/successor
 * queries in O(log_w n) time, where w is the machine word size (typically 64).
 * For 64-bit keys and n elements, this gives O(log_64 n) = O(log n / 6) time.
 *
 * Key idea: Pack B = w^{1/5} keys into a single machine word using a
 * "sketch" function, then use bitwise parallel comparison to search all
 * keys in a node in O(1) time.
 *
 * Real-Life Use Cases:
 * 1. Integer Sorting in O(n log log n): Fusion trees enable sorting n
 *    integers in O(n log log n) time—faster than comparison-based O(n log n)
 *    lower bound—by exploiting word-level parallelism. This benefits
 *    large-scale data pipelines sorting fixed-width integer keys (e.g.,
 *    hash digests, timestamps).
 * 2. High-Speed Symbol Table in Compilers: A compiler's symbol table maps
 *    hashed identifiers (64-bit integers) to type/value info. Fusion trees
 *    reduce lookup time compared to red-black trees, accelerating the
 *    critical-path symbol lookup in large translation units.
 * 3. Network Packet Classification: Firewalls and switches classify packets
 *    by matching integer fields (ports, protocol IDs) against rule sets.
 *    A fusion-tree index over integer rule keys provides sub-logarithmic
 *    lookup, helping sustain line-rate packet processing.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 4 (Feb 24, 2003)
 *   - Fredman & Willard, "Surpassing the information theoretic bound with
 *     fusion trees", 1993
 */

#ifndef FUSION_TREE_H
#define FUSION_TREE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* B-ary branching factor: B = w^{1/5}.  For w = 64, B = 3 (floor).
 * We use a small B here for illustration; tune for your word size. */
#define FUSION_B 4

/**
 * A single node in the fusion tree.
 * An internal node stores up to FUSION_B-1 keys and FUSION_B children.
 * A leaf stores up to FUSION_B keys.
 */
typedef struct FusionNode {
    uint64_t keys[FUSION_B];       /* Stored keys (sorted) */
    struct FusionNode *children[FUSION_B + 1]; /* Children (NULL for leaves) */
    int num_keys;                  /* Number of keys currently stored */
    bool is_leaf;                  /* True if this is a leaf node */
    /* Sketch: packed representation of all keys for word-parallel search */
    uint64_t sketch;               /* Compressed sketch for parallel comparison */
} FusionNode;

/**
 * Fusion tree root structure.
 */
typedef struct FusionTree {
    FusionNode *root;
    int n;                         /* Number of keys stored */
    int height;                    /* Height of the tree */
} FusionTree;

/**
 * Create an empty fusion tree.
 * @return Pointer to the new fusion tree, or NULL on failure
 */
FusionTree *fusion_tree_create(void);

/**
 * Destroy the fusion tree and free all memory.
 * @param tree  The fusion tree to destroy
 */
void fusion_tree_destroy(FusionTree *tree);

/**
 * Insert a key into the fusion tree.
 * @param tree  The fusion tree
 * @param key   Key to insert
 * @return true on success, false on failure or duplicate
 */
bool fusion_tree_insert(FusionTree *tree, uint64_t key);

/**
 * Delete a key from the fusion tree.
 * @param tree  The fusion tree
 * @param key   Key to delete
 * @return true if key was found and deleted, false otherwise
 */
bool fusion_tree_delete(FusionTree *tree, uint64_t key);

/**
 * Search for a key in the fusion tree.
 * @param tree  The fusion tree
 * @param key   Key to search
 * @return true if key is present, false otherwise
 */
bool fusion_tree_search(const FusionTree *tree, uint64_t key);

/**
 * Find the predecessor of key (largest stored key < key).
 * @param tree    The fusion tree
 * @param key     Query key
 * @param result  Output: predecessor key
 * @return true if predecessor exists, false otherwise
 */
bool fusion_tree_predecessor(const FusionTree *tree, uint64_t key,
                             uint64_t *result);

/**
 * Find the successor of key (smallest stored key > key).
 * @param tree    The fusion tree
 * @param key     Query key
 * @param result  Output: successor key
 * @return true if successor exists, false otherwise
 */
bool fusion_tree_successor(const FusionTree *tree, uint64_t key,
                           uint64_t *result);

/**
 * Return the number of keys stored.
 * @param tree  The fusion tree
 * @return count of keys
 */
int fusion_tree_size(const FusionTree *tree);

#endif /* FUSION_TREE_H */

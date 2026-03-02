/**
 * Succinct Data Structures: Rank and Select Implementation
 *
 * Succinct data structures represent data in space close to the information-
 * theoretic minimum while still supporting efficient queries.
 *
 * This file implements:
 *  - Rank/Select on a bit vector: the foundation of most succinct structures.
 *    rank(B, i) = number of 1-bits in B[0..i-1]
 *    select(B, j) = position of the j-th 1-bit in B
 *  - Succinct representation of ordered rooted trees using balanced
 *    parentheses encoding (LOUDS / BP representation).
 *
 * Space: rank/select structures use O(n / log n) extra bits over the n-bit
 * bitvector, achieving constant-time queries.
 *
 * Real-Life Use Cases:
 * 1. Compressed Inverted Indexes (Search Engines): Search engines store
 *    posting lists as bit vectors over document IDs. Rank/select on these
 *    bit vectors allows O(1) positional queries, enabling fast intersection
 *    and union of posting lists without fully decompressing them.
 * 2. Wavelet Trees for Genome Browsers: The wavelet tree, built on rank/
 *    select primitives, lets a genome browser answer "how many times does
 *    nucleotide X appear in reference[l..r]?" in O(log |Sigma|) time
 *    (|Sigma| = alphabet size) using space proportional to the entropy.
 * 3. Compressed Suffix Arrays: The FM-index (Ferragina & Manzini) encodes
 *    the suffix array in O(n H_k) bits (H_k = k-th order entropy) using
 *    rank/select on the Burrows-Wheeler Transform. It powers compressed
 *    full-text indexes in bioinformatics tools like BWA and Bowtie.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lecture 12 (Apr 7, 2003)
 *   - Jacobson, "Space-Efficient Static Trees and Graphs", 1989
 *   - Munro & Raman, "Succinct Representation of Balanced Parentheses", 1997
 */

#ifndef SUCCINCT_H
#define SUCCINCT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* -----------------------------------------------------------------------
 * Bit vector with O(1) rank and select
 * ----------------------------------------------------------------------- */

#define SUCCINCT_BLOCK   64   /* Bits per word */
#define SUCCINCT_SUPER   512  /* Super-block size in bits */

/** Bit vector with precomputed rank/select support. */
typedef struct BitVector {
    uint64_t *data;         /* Raw bit data */
    int n;                  /* Number of bits */
    int num_words;          /* Number of 64-bit words */

    /* Rank support */
    int *superblock_rank;   /* Cumulative rank at each super-block boundary */
    uint16_t *block_rank;   /* Rank within each block (relative to super-block) */

    /* Select support (simplified) */
    int *select1_samples;   /* Sampled positions for select(j) every K ones */
    int num_select_samples; /* Number of samples */
    int total_ones;         /* Total number of 1-bits */
} BitVector;

/**
 * Build a bit vector with rank/select support from raw bits.
 * @param bits   Array of bytes (LSB-first within each byte); length = ceil(n/8)
 * @param n      Number of bits
 * @return Pointer to the BitVector, or NULL on failure
 */
BitVector *bitvec_build(const uint8_t *bits, int n);

/**
 * Destroy the bit vector and free all memory.
 * @param bv  The bit vector
 */
void bitvec_destroy(BitVector *bv);

/**
 * Access bit i (0-indexed).
 * @param bv  The bit vector
 * @param i   Index
 * @return 0 or 1
 */
int bitvec_access(const BitVector *bv, int i);

/**
 * rank1(i): count of 1-bits in bv[0..i-1] (exclusive).
 * @param bv  The bit vector
 * @param i   Position (0 <= i <= n)
 * @return Number of 1-bits in [0, i)
 */
int bitvec_rank1(const BitVector *bv, int i);

/**
 * rank0(i): count of 0-bits in bv[0..i-1].
 * @param bv  The bit vector
 * @param i   Position
 * @return bitvec_rank0 = i - bitvec_rank1(bv, i)
 */
int bitvec_rank0(const BitVector *bv, int i);

/**
 * select1(j): position of the j-th 1-bit (1-indexed).
 * @param bv  The bit vector
 * @param j   Rank (1-indexed)
 * @return 0-indexed position of the j-th 1, or -1 if j > total_ones
 */
int bitvec_select1(const BitVector *bv, int j);

/**
 * select0(j): position of the j-th 0-bit (1-indexed).
 * @param bv  The bit vector
 * @param j   Rank (1-indexed)
 * @return 0-indexed position, or -1 if j > total_zeros
 */
int bitvec_select0(const BitVector *bv, int j);

/* -----------------------------------------------------------------------
 * Succinct tree (balanced parentheses representation)
 * ----------------------------------------------------------------------- */

/**
 * A tree encoded as a balanced parenthesis string of length 2n bits
 * where '(' = 1 (open) and ')' = 0 (close).  A pre-order DFS writes
 * '(' on entry and ')' on exit, giving a unique encoding.
 *
 * Supported operations (all O(1) after O(n) preprocessing):
 *  - parent(v):        parent of node v
 *  - first_child(v):   first child of node v
 *  - next_sibling(v):  next sibling of node v
 *  - subtree_size(v):  number of nodes in v's subtree
 *  - depth(v):         depth of node v
 *  - is_leaf(v):       whether v is a leaf
 */
typedef struct SuccinctTree {
    BitVector *bp;      /* Balanced parenthesis bit vector (length 2n) */
    int n;              /* Number of nodes */
} SuccinctTree;

/**
 * Build a succinct tree from a balanced parenthesis string.
 * @param bp_string  String of '(' and ')' characters, length = 2n
 * @param n          Number of nodes
 * @return Pointer to the SuccinctTree, or NULL on failure
 */
SuccinctTree *stree_build(const char *bp_string, int n);

/**
 * Destroy the succinct tree.
 * @param tree  The succinct tree to destroy
 */
void stree_destroy(SuccinctTree *tree);

/**
 * Return the position of the matching closing parenthesis for position i.
 * Used internally and exposed for advanced queries.
 * @param tree  The succinct tree
 * @param i     Position of an open parenthesis
 * @return Position of the matching close parenthesis
 */
int stree_close(const SuccinctTree *tree, int i);

/**
 * Return the position of the matching open parenthesis for position i.
 * @param tree  The succinct tree
 * @param i     Position of a close parenthesis
 * @return Position of the matching open parenthesis
 */
int stree_open(const SuccinctTree *tree, int i);

/**
 * Return the depth of the node whose open parenthesis is at position v.
 * @param tree  The succinct tree
 * @param v     Position of open parenthesis (node identifier)
 * @return Depth (root = 0)
 */
int stree_depth(const SuccinctTree *tree, int v);

/**
 * Return the parent of node v.
 * @param tree  The succinct tree
 * @param v     Node (position of its open paren)
 * @return Parent position, or -1 if v is the root
 */
int stree_parent(const SuccinctTree *tree, int v);

/**
 * Return the first child of node v, or -1 if v is a leaf.
 * @param tree  The succinct tree
 * @param v     Node
 * @return First child position, or -1
 */
int stree_first_child(const SuccinctTree *tree, int v);

/**
 * Return the next sibling of node v, or -1 if none.
 * @param tree  The succinct tree
 * @param v     Node
 * @return Next sibling position, or -1
 */
int stree_next_sibling(const SuccinctTree *tree, int v);

/**
 * Return the number of nodes in v's subtree.
 * @param tree  The succinct tree
 * @param v     Node
 * @return Subtree size
 */
int stree_subtree_size(const SuccinctTree *tree, int v);

#endif /* SUCCINCT_H */

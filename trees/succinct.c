/**
 * Succinct Data Structures: Rank and Select Implementation
 */

#include "succinct.h"
#include <stdlib.h>
#include <string.h>

/* =========================================================
 * Bit vector
 * ========================================================= */

/* Portable popcount using Brian Kernighan's algorithm (fallback). */
static int popcount64(uint64_t x) {
    int count = 0;
    while (x) { x &= x - 1; count++; }
    return count;
}

BitVector *bitvec_build(const uint8_t *bits, int n) {
    /* TODO: Build rank/select support.
     * 1. Allocate data array of ceil(n/64) 64-bit words; copy bits.
     * 2. Build superblock_rank[i] = total 1-bits in words 0..i*8-1.
     * 3. Build block_rank[i] = 1-bits in words[i % 8 * 64 bits] relative
     *    to the enclosing super-block.
     * 4. Count total_ones and build select1 samples every K ones. */
    if (!bits || n <= 0) return NULL;
    BitVector *bv = (BitVector *)calloc(1, sizeof(BitVector));
    if (!bv) return NULL;
    bv->n = n;
    bv->num_words = (n + SUCCINCT_BLOCK - 1) / SUCCINCT_BLOCK;
    bv->data = (uint64_t *)calloc((size_t)bv->num_words, sizeof(uint64_t));
    if (!bv->data) { free(bv); return NULL; }
    /* Copy raw bits */
    for (int i = 0; i < n; i++) {
        if ((bits[i / 8] >> (i % 8)) & 1)
            bv->data[i / SUCCINCT_BLOCK] |= (uint64_t)1 << (i % SUCCINCT_BLOCK);
    }
    bv->total_ones = 0;
    for (int i = 0; i < bv->num_words; i++)
        bv->total_ones += popcount64(bv->data[i]);
    /* TODO: build superblock_rank, block_rank, select1_samples */
    return bv;
}

void bitvec_destroy(BitVector *bv) {
    if (!bv) return;
    free(bv->data);
    free(bv->superblock_rank);
    free(bv->block_rank);
    free(bv->select1_samples);
    free(bv);
}

int bitvec_access(const BitVector *bv, int i) {
    if (!bv || i < 0 || i >= bv->n) return 0;
    return (int)((bv->data[i / SUCCINCT_BLOCK] >> (i % SUCCINCT_BLOCK)) & 1);
}

int bitvec_rank1(const BitVector *bv, int i) {
    /* TODO: Use superblock and block tables for O(1) rank.
     * rank = superblock_rank[i / SUCCINCT_SUPER]
     *      + block_rank[i / SUCCINCT_BLOCK]
     *      + popcount(data[i/SUCCINCT_BLOCK] & ((1<<(i%SUCCINCT_BLOCK))-1)) */
    if (!bv || i <= 0) return 0;
    if (i >= bv->n) i = bv->n;
    /* Fallback: linear scan (replace with O(1) once tables are built) */
    int count = 0;
    for (int j = 0; j < i; j++)
        count += bitvec_access(bv, j);
    return count;
}

int bitvec_rank0(const BitVector *bv, int i) {
    return i - bitvec_rank1(bv, i);
}

int bitvec_select1(const BitVector *bv, int j) {
    /* TODO: Use select samples + linear scan within a block for O(1) select. */
    if (!bv || j <= 0 || j > bv->total_ones) return -1;
    int count = 0;
    for (int i = 0; i < bv->n; i++) {
        if (bitvec_access(bv, i)) {
            count++;
            if (count == j) return i;
        }
    }
    return -1;
}

int bitvec_select0(const BitVector *bv, int j) {
    if (!bv || j <= 0 || j > (bv->n - bv->total_ones)) return -1;
    int count = 0;
    for (int i = 0; i < bv->n; i++) {
        if (!bitvec_access(bv, i)) {
            count++;
            if (count == j) return i;
        }
    }
    return -1;
}

/* =========================================================
 * Succinct tree
 * ========================================================= */

SuccinctTree *stree_build(const char *bp_string, int n) {
    /* TODO: Convert bp_string (sequence of '(' and ')') to a bit vector.
     * '(' -> 1, ')' -> 0.  Then build the BitVector and precompute
     * any auxiliary structures needed for close/open/depth queries. */
    if (!bp_string || n <= 0) return NULL;
    SuccinctTree *tree = (SuccinctTree *)malloc(sizeof(SuccinctTree));
    if (!tree) return NULL;
    tree->n = n;
    int len = 2 * n;
    uint8_t *bits = (uint8_t *)calloc((size_t)((len + 7) / 8), 1);
    if (!bits) { free(tree); return NULL; }
    for (int i = 0; i < len; i++) {
        if (bp_string[i] == '(')
            bits[i / 8] |= (uint8_t)(1 << (i % 8));
    }
    tree->bp = bitvec_build(bits, len);
    free(bits);
    if (!tree->bp) { free(tree); return NULL; }
    return tree;
}

void stree_destroy(SuccinctTree *tree) {
    if (!tree) return;
    bitvec_destroy(tree->bp);
    free(tree);
}

int stree_close(const SuccinctTree *tree, int i) {
    /* TODO: Find closing paren matching open paren at i.
     * Use excess function: excess(i) = rank1(i+1) - rank0(i+1).
     * Find smallest j > i with excess(j) == excess(i) - 1.
     * With a Range Minimum Query on the excess array this runs in O(1). */
    if (!tree) return -1;
    int depth = 1;
    for (int j = i + 1; j < 2 * tree->n; j++) {
        if (bitvec_access(tree->bp, j)) depth++;
        else depth--;
        if (depth == 0) return j;
    }
    return -1;
}

int stree_open(const SuccinctTree *tree, int i) {
    /* TODO: Symmetric to stree_close. */
    if (!tree) return -1;
    int depth = 1;
    for (int j = i - 1; j >= 0; j--) {
        if (!bitvec_access(tree->bp, j)) depth++;
        else depth--;
        if (depth == 0) return j;
    }
    return -1;
}

int stree_depth(const SuccinctTree *tree, int v) {
    /* depth(v) = rank1(v) - rank0(v) = 2*rank1(v) - v */
    if (!tree) return -1;
    return bitvec_rank1(tree->bp, v) - bitvec_rank0(tree->bp, v);
}

int stree_parent(const SuccinctTree *tree, int v) {
    if (!tree || v == 0) return -1;
    /* parent = open paren of (v-1)'s enclosing pair */
    return stree_open(tree, v - 1);
}

int stree_first_child(const SuccinctTree *tree, int v) {
    if (!tree) return -1;
    /* If v+1 is an open paren, v has a first child there. */
    if (v + 1 < 2 * tree->n && bitvec_access(tree->bp, v + 1))
        return v + 1;
    return -1;
}

int stree_next_sibling(const SuccinctTree *tree, int v) {
    if (!tree) return -1;
    int close = stree_close(tree, v);
    if (close + 1 < 2 * tree->n && bitvec_access(tree->bp, close + 1))
        return close + 1;
    return -1;
}

int stree_subtree_size(const SuccinctTree *tree, int v) {
    if (!tree) return 0;
    int close = stree_close(tree, v);
    return (close - v + 1) / 2;
}

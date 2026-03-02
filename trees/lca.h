/**
 * Least Common Ancestor (LCA) and Range Minimum Query (RMQ) Implementation
 *
 * LCA(u, v) in a rooted tree is the deepest node that is an ancestor of
 * both u and v.  The classic reduction by Bender & Farach-Colton (2000)
 * converts LCA to ±1 RMQ (range minimum query on an array where consecutive
 * elements differ by exactly 1) and then solves RMQ in O(n) preprocessing
 * and O(1) query time using sparse tables.
 *
 * Real-Life Use Cases:
 * 1. Suffix Tree / Suffix Array Queries: The longest common extension (LCE)
 *    of two suffixes equals the LCA of their leaf nodes in the suffix tree,
 *    which equals the minimum value in the LCP array between their positions.
 *    This O(1) LCA query powers O(1) string comparison and is the core of
 *    many bioinformatics alignment tools.
 * 2. XML / JSON Document Processing: A document is a tree; queries like
 *    "find the deepest common ancestor of two element nodes" arise in XSLT
 *    transformations and XPath evaluation.  O(1) LCA allows XML processors
 *    to evaluate ancestor-based predicates without traversing the tree.
 * 3. Version Control / File System Merge: In Git, finding the merge base of
 *    two commits means finding their LCA in the commit DAG (which, for trees,
 *    is an LCA query).  Efficient LCA computation speeds up three-way merges
 *    in repositories with deep histories.
 *
 * References:
 *   - 6.897 Advanced Data Structures, MIT, Lectures 10 & 11 (Mar–Apr 2003)
 *   - Bender & Farach-Colton, "The LCA Problem Revisited", 2000
 *   - Sparse table (Bender et al.): O(n log n) preprocessing, O(1) query
 */

#ifndef LCA_H
#define LCA_H

#include <stdbool.h>
#include <stddef.h>

/* -----------------------------------------------------------------------
 * Range Minimum Query (sparse table, static array)
 * ----------------------------------------------------------------------- */

/**
 * Sparse table for static O(1) range minimum queries after O(n log n)
 * preprocessing.  Assumes the array is fixed after construction.
 */
typedef struct RMQ {
    int *arr;           /* Input array (copy) */
    int **table;        /* table[k][i] = index of min in arr[i..i+2^k-1] */
    int *log2_floor;    /* Precomputed floor(log2(i)) for i in [1..n] */
    int n;              /* Length of array */
    int log_n;          /* ceil(log2(n)) */
} RMQ;

/**
 * Build a sparse table for range minimum query on arr[0..n-1].
 * @param arr  Input array (not modified)
 * @param n    Length of arr
 * @return Pointer to the RMQ structure, or NULL on failure
 */
RMQ *rmq_build(const int *arr, int n);

/**
 * Destroy the RMQ structure and free all memory.
 * @param rmq  The RMQ structure to destroy
 */
void rmq_destroy(RMQ *rmq);

/**
 * Query the index of the minimum element in arr[l..r] (inclusive).
 * @param rmq  The RMQ structure
 * @param l    Left endpoint (0-indexed)
 * @param r    Right endpoint (0-indexed, l <= r)
 * @return Index of the minimum element in [l, r]
 */
int rmq_query(const RMQ *rmq, int l, int r);

/* -----------------------------------------------------------------------
 * Rooted tree with LCA support
 * ----------------------------------------------------------------------- */

#define LCA_MAX_NODES 100000

/** Node in a rooted tree. */
typedef struct TreeNodeLCA {
    int id;
    int depth;
    int parent_id;       /* -1 for root */
    int *children;       /* Dynamic array of child IDs */
    int num_children;
    int children_cap;
} TreeNodeLCA;

/** Rooted tree with precomputed LCA support. */
typedef struct LCATree {
    TreeNodeLCA *nodes;  /* Array of nodes indexed by ID */
    int n;               /* Number of nodes */
    int root;            /* Root node ID */

    /* Euler tour arrays for LCA-via-RMQ */
    int *euler;          /* Euler tour (2n-1 entries) */
    int *first;          /* first[v] = first occurrence of v in euler[] */
    int euler_size;      /* Size of euler array (2n-1) */
    RMQ *rmq;            /* RMQ structure over euler depths */
} LCATree;

/**
 * Create a rooted tree for LCA queries.
 * @param n     Number of nodes (nodes are numbered 0..n-1)
 * @param root  Root node ID
 * @return Pointer to the LCATree, or NULL on failure
 */
LCATree *lca_tree_create(int n, int root);

/**
 * Destroy the LCA tree and free all memory.
 * @param tree  The LCA tree to destroy
 */
void lca_tree_destroy(LCATree *tree);

/**
 * Add an edge from parent to child.
 * @param tree    The LCA tree
 * @param parent  Parent node ID
 * @param child   Child node ID
 * @return true on success
 */
bool lca_tree_add_edge(LCATree *tree, int parent, int child);

/**
 * Preprocess the tree for O(1) LCA queries (builds Euler tour + RMQ).
 * Must be called after all edges are added and before lca_query.
 * @param tree  The LCA tree
 * @return true on success
 */
bool lca_preprocess(LCATree *tree);

/**
 * Answer an LCA query in O(1) time (after preprocessing).
 * @param tree  The LCA tree
 * @param u     First node ID
 * @param v     Second node ID
 * @return LCA node ID, or -1 on error
 */
int lca_query(const LCATree *tree, int u, int v);

/**
 * Return the depth of a node (root has depth 0).
 * @param tree  The LCA tree
 * @param u     Node ID
 * @return Depth, or -1 on error
 */
int lca_depth(const LCATree *tree, int u);

#endif /* LCA_H */

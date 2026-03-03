/**
 * LCA and Range Minimum Query Implementation
 */

#include "lca.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* =========================================================
 * Sparse table RMQ
 * ========================================================= */

RMQ *rmq_build(const int *arr, int n) {
    /* TODO: Build sparse table.
     * 1. Precompute log2_floor[i] for i in [1..n].
     * 2. Allocate table[0..log_n][0..n-1].
     * 3. table[0][i] = i (each range of length 1).
     * 4. For k = 1 to log_n:
     *      for i = 0 to n - 2^k:
     *        table[k][i] = argmin(arr[table[k-1][i]], arr[table[k-1][i+2^{k-1}]]) */
    if (!arr || n <= 0) return NULL;
    RMQ *rmq = (RMQ *)malloc(sizeof(RMQ));
    if (!rmq) return NULL;
    rmq->n = n;
    rmq->arr = (int *)malloc((size_t)n * sizeof(int));
    if (!rmq->arr) { free(rmq); return NULL; }
    memcpy(rmq->arr, arr, (size_t)n * sizeof(int));
    rmq->log_n = (n > 1) ? (int)(log2((double)n)) + 1 : 1;
    rmq->table = NULL;
    rmq->log2_floor = NULL;
    /* TODO: complete allocation and fill */
    return rmq;
}

void rmq_destroy(RMQ *rmq) {
    if (!rmq) return;
    if (rmq->table) {
        for (int k = 0; k <= rmq->log_n; k++)
            free(rmq->table[k]);
        free(rmq->table);
    }
    free(rmq->log2_floor);
    free(rmq->arr);
    free(rmq);
}

int rmq_query(const RMQ *rmq, int l, int r) {
    /* TODO: O(1) query using the sparse table.
     * k = log2_floor[r - l + 1]
     * Return argmin(arr[table[k][l]], arr[table[k][r - 2^k + 1]]) */
    if (!rmq || l > r) return -1;
    return l; /* placeholder */
}

/* =========================================================
 * LCA tree
 * ========================================================= */

LCATree *lca_tree_create(int n, int root) {
    LCATree *tree = (LCATree *)malloc(sizeof(LCATree));
    if (!tree) return NULL;
    tree->n = n;
    tree->root = root;
    tree->euler = NULL;
    tree->first = NULL;
    tree->euler_size = 0;
    tree->rmq = NULL;
    tree->nodes = (TreeNodeLCA *)calloc((size_t)n, sizeof(TreeNodeLCA));
    if (!tree->nodes) { free(tree); return NULL; }
    for (int i = 0; i < n; i++) {
        tree->nodes[i].id = i;
        tree->nodes[i].depth = 0;
        tree->nodes[i].parent_id = -1;
        tree->nodes[i].children = NULL;
        tree->nodes[i].num_children = 0;
        tree->nodes[i].children_cap = 0;
    }
    return tree;
}

void lca_tree_destroy(LCATree *tree) {
    if (!tree) return;
    if (tree->nodes) {
        for (int i = 0; i < tree->n; i++)
            free(tree->nodes[i].children);
        free(tree->nodes);
    }
    free(tree->euler);
    free(tree->first);
    rmq_destroy(tree->rmq);
    free(tree);
}

bool lca_tree_add_edge(LCATree *tree, int parent, int child) {
    if (!tree || parent < 0 || parent >= tree->n ||
        child < 0 || child >= tree->n) return false;
    TreeNodeLCA *p = &tree->nodes[parent];
    /* Grow children array if needed */
    if (p->num_children == p->children_cap) {
        int new_cap = (p->children_cap == 0) ? 4 : p->children_cap * 2;
        int *tmp = (int *)realloc(p->children, (size_t)new_cap * sizeof(int));
        if (!tmp) return false;
        p->children = tmp;
        p->children_cap = new_cap;
    }
    p->children[p->num_children++] = child;
    tree->nodes[child].parent_id = parent;
    return true;
}

bool lca_preprocess(LCATree *tree) {
    /* TODO: Build the Euler tour for LCA.
     * 1. DFS from root; record node id in euler[] on entry AND after
     *    returning from each child (2n-1 entries total).
     * 2. Record the first occurrence of each node in first[].
     * 3. Build a depth array over the euler tour.
     * 4. Build the RMQ structure over the depth array.
     *
     * Example DFS snippet:
     *   euler[pos++] = v;
     *   first[v] = first[v] == -1 ? pos-1 : first[v];
     *   for each child c of v:
     *     dfs(c, depth+1); euler[pos++] = v; */
    if (!tree) return false;
    return false;
}

int lca_query(const LCATree *tree, int u, int v) {
    /* TODO: After preprocessing:
     * l = min(first[u], first[v]);
     * r = max(first[u], first[v]);
     * return euler[rmq_query(rmq, l, r)]; */
    if (!tree) return -1;
    return -1;
}

int lca_depth(const LCATree *tree, int u) {
    if (!tree || u < 0 || u >= tree->n) return -1;
    return tree->nodes[u].depth;
}

/**
 * Suffix Tree Implementation (Ukkonen's online algorithm)
 */

#include "suffix_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---- Internal helpers ---- */

static int st_new_node(SuffixTree *tree, int start, int *end) {
    /* Grow node pool if needed */
    if (tree->num_nodes == tree->nodes_cap) {
        int new_cap = tree->nodes_cap * 2;
        STNode *tmp = (STNode *)realloc(tree->nodes,
                                        (size_t)new_cap * sizeof(STNode));
        if (!tmp) return -1;
        tree->nodes = tmp;
        tree->nodes_cap = new_cap;
    }
    int idx = tree->num_nodes++;
    STNode *node = &tree->nodes[idx];
    node->start = start;
    node->end = end;
    node->suffix_index = -1;
    node->suffix_link = 0; /* root by default */
    for (int i = 0; i < ST_ALPHA_SIZE; i++) node->children[i] = -1;
    return idx;
}

/* Edge length of node (for open-ended leaves, uses tree->leaf_end). */
static int edge_length(const SuffixTree *tree, int node_idx) {
    const STNode *node = &tree->nodes[node_idx];
    int end = (node->end == NULL) ? tree->leaf_end : *node->end;
    return end - node->start;
}

SuffixTree *suffix_tree_build(const char *text) {
    /* TODO: Implement Ukkonen's O(n) suffix tree construction.
     *
     * High-level algorithm:
     *   maintain (active_node, active_edge, active_length) and
     *   remaining suffixes count.
     *
     *   For each character text[i] (phase i):
     *     increment leaf_end (extends all open leaves in O(1)).
     *     while remaining > 0:
     *       if active_length == 0: active_edge = i
     *       if active_node has no edge for active_edge char:
     *         create leaf; set suffix link from last internal node if any
     *         remaining--; follow suffix link (or go to root)
     *       else:
     *         if we can walk down (active_length >= edge length): do so
     *         if text at active tip == text[i]: increment active_length; break
     *         split the edge; create internal node; create new leaf;
     *         set suffix link; remaining--; follow suffix link
     *
     * After construction, DFS to set suffix_index on all leaves. */
    if (!text) return NULL;
    SuffixTree *tree = (SuffixTree *)malloc(sizeof(SuffixTree));
    if (!tree) return NULL;

    tree->n = (int)strlen(text);
    tree->text = (char *)malloc((size_t)(tree->n + 1));
    if (!tree->text) { free(tree); return NULL; }
    memcpy(tree->text, text, (size_t)(tree->n + 1));

    tree->nodes_cap = 2 * tree->n + 10;
    tree->nodes = (STNode *)malloc((size_t)tree->nodes_cap * sizeof(STNode));
    if (!tree->nodes) { free(tree->text); free(tree); return NULL; }
    tree->num_nodes = 0;
    tree->leaf_end = 0;

    /* Create root node */
    int root_end_val = -1; /* placeholder, root edge has length 0 */
    tree->root = st_new_node(tree, -1, &root_end_val);

    /* TODO: run Ukkonen's phases */

    return tree;
}

void suffix_tree_destroy(SuffixTree *tree) {
    if (!tree) return;
    free(tree->text);
    /* TODO: free per-node end pointers for internal nodes */
    free(tree->nodes);
    free(tree);
}

bool suffix_tree_search(const SuffixTree *tree, const char *pattern) {
    /* TODO: Walk the suffix tree following characters of pattern.
     * At each node, match the edge label against the remaining pattern.
     * Return true if the entire pattern is consumed. */
    if (!tree || !pattern) return false;
    return false;
}

int suffix_tree_count(const SuffixTree *tree, const char *pattern) {
    /* TODO: Walk to the node where pattern ends, then count leaves in
     * that subtree (= number of suffix occurrences). */
    if (!tree || !pattern) return 0;
    return 0;
}

bool suffix_tree_find_all(const SuffixTree *tree, const char *pattern,
                          int *positions, int *count) {
    /* TODO: Walk to the node where pattern ends, then DFS to collect
     * suffix_index of all leaves in that subtree. */
    if (!tree || !pattern || !positions || !count) return false;
    *count = 0;
    return false;
}

void suffix_tree_longest_repeat(const SuffixTree *tree,
                                int *start, int *length) {
    /* TODO: Find the deepest internal node in the suffix tree (by string depth).
     * Its path label is the longest repeated substring. */
    if (start) *start = 0;
    if (length) *length = 0;
}

void suffix_tree_longest_palindrome(const SuffixTree *tree, int n,
                                    int *start, int *length) {
    /* TODO: In the combined string S+'$'+reverse(S)+'#', find the deepest
     * internal node whose subtree contains leaves from both halves. */
    (void)n;
    if (start) *start = 0;
    if (length) *length = 0;
}

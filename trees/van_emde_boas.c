/**
 * Van Emde Boas Tree Implementation
 */

#include "van_emde_boas.h"
#include <stdlib.h>
#include <math.h>

/* ---------- Helper macros ---------- */

/* Lower sqrt of universe size: clusters have this many elements. */
#define VEB_LOW_SQRT(u)  ((int)pow(2.0, floor(log2((double)(u)) / 2.0)))
/* Upper sqrt: there are this many clusters. */
#define VEB_HIGH_SQRT(u) ((int)pow(2.0, ceil(log2((double)(u)) / 2.0)))

/* Cluster index of element x in a universe of size u. */
#define VEB_HIGH(u, x)   ((x) / VEB_LOW_SQRT(u))
/* Position of element x within its cluster. */
#define VEB_LOW(u, x)    ((x) % VEB_LOW_SQRT(u))
/* Reconstruct element from cluster index and position. */
#define VEB_INDEX(u, h, l) ((h) * VEB_LOW_SQRT(u) + (l))

/* ---------- Public API ---------- */

VEB *veb_create(int universe) {
    /* TODO: Allocate a VEB node for the given universe size.
     * Base case: universe == 2 has no children (summary/cluster are NULL).
     * Recursive case: allocate a summary vEB of size high_sqrt(universe)
     * and an array of high_sqrt(universe) cluster vEBs each of size low_sqrt(universe).
     * Set min = max = VEB_EMPTY. */
    VEB *tree = (VEB *)malloc(sizeof(VEB));
    if (!tree) return NULL;
    tree->universe = universe;
    tree->min = VEB_EMPTY;
    tree->max = VEB_EMPTY;
    tree->summary = NULL;
    tree->cluster = NULL;
    /* TODO: for universe > 2, allocate summary and cluster arrays */
    return tree;
}

void veb_destroy(VEB *tree) {
    /* TODO: Recursively destroy summary and all clusters, then free tree. */
    if (!tree) return;
    free(tree);
}

bool veb_is_empty(const VEB *tree) {
    return !tree || tree->min == VEB_EMPTY;
}

void veb_insert(VEB *tree, int key) {
    /* TODO: Implement vEB insertion in O(log log U) time.
     * Algorithm (recursive):
     *   if tree is empty: set min = max = key and return.
     *   if key < tree->min: swap key with tree->min.
     *   if universe > 2:
     *     c = VEB_HIGH(u, key); pos = VEB_LOW(u, key)
     *     if cluster[c] is empty: insert c into summary
     *     insert pos into cluster[c]
     *   if key > tree->max: tree->max = key */
    if (!tree) return;
}

void veb_delete(VEB *tree, int key) {
    /* TODO: Implement vEB deletion in O(log log U) time.
     * Algorithm (recursive):
     *   if min == max: set min = max = VEB_EMPTY and return.
     *   if universe == 2: handle directly.
     *   if key == min: find new minimum from summary/cluster.
     *   c = VEB_HIGH(u, key); pos = VEB_LOW(u, key)
     *   delete pos from cluster[c]
     *   if cluster[c] is empty: delete c from summary
     *   else: update max if needed */
    if (!tree) return;
}

bool veb_member(const VEB *tree, int key) {
    /* TODO: Implement O(log log U) membership test.
     * if key == min or key == max: return true.
     * if universe == 2: return false.
     * recursively check cluster[VEB_HIGH(u,key)] for VEB_LOW(u,key). */
    if (!tree) return false;
    return false;
}

int veb_minimum(const VEB *tree) {
    return (tree) ? tree->min : VEB_EMPTY;
}

int veb_maximum(const VEB *tree) {
    return (tree) ? tree->max : VEB_EMPTY;
}

int veb_successor(const VEB *tree, int key) {
    /* TODO: Implement O(log log U) successor query.
     * if universe == 2: handle base case.
     * c = VEB_HIGH(u, key); pos = VEB_LOW(u, key)
     * if pos < max of cluster[c]: recurse into cluster[c].
     * else: find next non-empty cluster via summary successor. */
    if (!tree || veb_is_empty(tree)) return VEB_EMPTY;
    return VEB_EMPTY;
}

int veb_predecessor(const VEB *tree, int key) {
    /* TODO: Implement O(log log U) predecessor query.
     * Symmetric to successor. */
    if (!tree || veb_is_empty(tree)) return VEB_EMPTY;
    return VEB_EMPTY;
}

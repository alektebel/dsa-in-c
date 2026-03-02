/**
 * Splay Tree Implementation
 */

#include "splay_tree.h"
#include <stdlib.h>
#include <stdio.h>

/* ---- Helper: right rotation (zig) ---- */
static void rotate_right(SplayTree *tree, SplayNode *x) {
    /* TODO: Standard right rotation around node x.
     *   y = x->left; x->left = y->right; if y->right != NULL: y->right->parent = x
     *   y->parent = x->parent; update parent's child pointer; y->right = x; x->parent = y */
    (void)tree;
    (void)x;
}

/* ---- Helper: left rotation (zag) ---- */
static void rotate_left(SplayTree *tree, SplayNode *x) {
    /* TODO: Standard left rotation around node x. */
    (void)tree;
    (void)x;
}

/* ---- The splay operation ---- */
static void splay(SplayTree *tree, SplayNode *x) {
    /* TODO: Move node x to the root using zig, zig-zig, and zig-zag steps.
     *
     * While x is not the root:
     *   p = x->parent
     *   if p is root (zig step): rotate x up once.
     *   else if x and p are both left children (zig-zig):
     *     rotate p up, then rotate x up.
     *   else if x and p are both right children (zig-zig mirror):
     *     rotate p up, then rotate x up.
     *   else (zig-zag): rotate x up twice. */
    (void)tree;
    (void)x;
}

SplayTree *splay_tree_create(void) {
    SplayTree *tree = (SplayTree *)malloc(sizeof(SplayTree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

static void node_destroy_recursive(SplayNode *node) {
    if (!node) return;
    node_destroy_recursive(node->left);
    node_destroy_recursive(node->right);
    free(node);
}

void splay_tree_destroy(SplayTree *tree) {
    if (!tree) return;
    node_destroy_recursive(tree->root);
    free(tree);
}

bool splay_tree_insert(SplayTree *tree, int key, void *data) {
    /* TODO: Standard BST insert, then splay the new node to the root.
     * 1. Walk tree to find insertion position.
     * 2. Allocate new node, set key/data, link into tree.
     * 3. Call splay(tree, new_node).
     * 4. Increment tree->size. */
    if (!tree) return false;
    return false;
}

bool splay_tree_delete(SplayTree *tree, int key) {
    /* TODO: Splay the key to the root, then merge the two subtrees.
     * 1. splay_tree_search(tree, key) — splays key (or predecessor) to root.
     * 2. If root->key != key: return false.
     * 3. Detach left and right subtrees.
     * 4. Find max of left subtree, splay it to top of left.
     * 5. Attach right subtree as right child of left's new root.
     * 6. Free the old root, decrement size. */
    if (!tree) return false;
    return false;
}

SplayNode *splay_tree_search(SplayTree *tree, int key) {
    /* TODO: Standard BST search, then splay the found (or last visited) node.
     * This maintains the working-set / static-optimality property. */
    if (!tree || !tree->root) return NULL;
    return NULL;
}

SplayNode *splay_tree_minimum(SplayTree *tree) {
    /* TODO: Walk left to the minimum, then splay it to the root. */
    if (!tree || !tree->root) return NULL;
    return NULL;
}

SplayNode *splay_tree_maximum(SplayTree *tree) {
    /* TODO: Walk right to the maximum, then splay it to the root. */
    if (!tree || !tree->root) return NULL;
    return NULL;
}

void splay_tree_split(SplayTree *tree, int key,
                      SplayTree **left, SplayTree **right) {
    /* TODO: Splay key (or its successor) to root, then cut.
     * After splay: root->key <= key => left gets root+left-subtree,
     *              right gets root's right subtree. */
    if (left) *left = NULL;
    if (right) *right = NULL;
    if (!tree) return;
}

SplayTree *splay_tree_merge(SplayTree *left, SplayTree *right) {
    /* TODO: Splay the maximum of the left tree to its root,
     * then attach the right tree as the right child of that root. */
    if (!left) return right;
    if (!right) return left;
    return left;
}

size_t splay_tree_size(const SplayTree *tree) {
    return tree ? tree->size : 0;
}

bool splay_tree_is_empty(const SplayTree *tree) {
    return !tree || !tree->root;
}

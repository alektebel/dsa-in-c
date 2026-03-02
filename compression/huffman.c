/**
 * Huffman Coding Implementation
 */

#include "huffman.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---- Min-heap for building the Huffman tree ---- */

typedef struct MinHeap {
    HuffNode **data;
    int size;
    int capacity;
} MinHeap;

static MinHeap *heap_create(int capacity) {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    if (!h) return NULL;
    h->data = (HuffNode **)malloc((size_t)capacity * sizeof(HuffNode *));
    if (!h->data) { free(h); return NULL; }
    h->size = 0;
    h->capacity = capacity;
    return h;
}

static void heap_destroy(MinHeap *h) {
    if (h) { free(h->data); free(h); }
}

static void heap_swap(MinHeap *h, int i, int j) {
    HuffNode *tmp = h->data[i]; h->data[i] = h->data[j]; h->data[j] = tmp;
}

static void heap_sift_up(MinHeap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p]->freq > h->data[i]->freq) {
            heap_swap(h, p, i); i = p;
        } else break;
    }
}

static void heap_sift_down(MinHeap *h, int i) {
    while (1) {
        int l = 2*i+1, r = 2*i+2, m = i;
        if (l < h->size && h->data[l]->freq < h->data[m]->freq) m = l;
        if (r < h->size && h->data[r]->freq < h->data[m]->freq) m = r;
        if (m == i) break;
        heap_swap(h, i, m); i = m;
    }
}

static bool heap_push(MinHeap *h, HuffNode *node) {
    if (h->size == h->capacity) return false;
    h->data[h->size++] = node;
    heap_sift_up(h, h->size - 1);
    return true;
}

static HuffNode *heap_pop(MinHeap *h) {
    if (h->size == 0) return NULL;
    HuffNode *top = h->data[0];
    h->data[0] = h->data[--h->size];
    if (h->size > 0) heap_sift_down(h, 0);
    return top;
}

/* ---- Huffman tree ---- */

static HuffNode *huff_node_create(int symbol, long long freq) {
    HuffNode *node = (HuffNode *)calloc(1, sizeof(HuffNode));
    if (!node) return NULL;
    node->symbol = symbol;
    node->freq = freq;
    return node;
}

static void huff_node_destroy(HuffNode *node) {
    if (!node) return;
    huff_node_destroy(node->left);
    huff_node_destroy(node->right);
    free(node);
}

/* DFS to build the code table */
static void build_table(const HuffNode *node, HuffCode *table,
                        uint32_t bits, int len) {
    if (!node) return;
    if (node->left == NULL && node->right == NULL) {
        /* Leaf */
        table[node->symbol].bits = bits;
        table[node->symbol].length = len;
        return;
    }
    build_table(node->left,  table, (bits << 1),       len + 1);
    build_table(node->right, table, (bits << 1) | 1u,  len + 1);
}

HuffTree *huffman_build(const long long freqs[HUFFMAN_ALPHA_SIZE]) {
    if (!freqs) return NULL;
    HuffTree *tree = (HuffTree *)calloc(1, sizeof(HuffTree));
    if (!tree) return NULL;

    /* Count distinct symbols */
    int distinct = 0;
    for (int i = 0; i < HUFFMAN_ALPHA_SIZE; i++)
        if (freqs[i] > 0) distinct++;
    if (distinct == 0) { free(tree); return NULL; }

    MinHeap *heap = heap_create(HUFFMAN_ALPHA_SIZE);
    if (!heap) { free(tree); return NULL; }

    for (int i = 0; i < HUFFMAN_ALPHA_SIZE; i++) {
        if (freqs[i] > 0) {
            HuffNode *node = huff_node_create(i, freqs[i]);
            if (!node || !heap_push(heap, node)) {
                huff_node_destroy(node);
                heap_destroy(heap); free(tree); return NULL;
            }
        }
    }

    /* Handle single-symbol case */
    if (heap->size == 1) {
        HuffNode *only = heap_pop(heap);
        HuffNode *root = huff_node_create(-1, only->freq);
        if (!root) { huff_node_destroy(only); heap_destroy(heap); free(tree); return NULL; }
        root->left = only;
        tree->root = root;
    } else {
        /* Build tree by merging two minimums at a time */
        while (heap->size > 1) {
            HuffNode *a = heap_pop(heap);
            HuffNode *b = heap_pop(heap);
            HuffNode *parent = huff_node_create(-1, a->freq + b->freq);
            if (!parent) {
                huff_node_destroy(a); huff_node_destroy(b);
                heap_destroy(heap); free(tree); return NULL;
            }
            parent->left = a; parent->right = b;
            if (!heap_push(heap, parent)) {
                huff_node_destroy(parent); heap_destroy(heap); free(tree); return NULL;
            }
        }
        tree->root = heap_pop(heap);
    }
    heap_destroy(heap);

    /* Build encoding table */
    build_table(tree->root, tree->table, 0u, 0);
    return tree;
}

HuffTree *huffman_build_from_data(const uint8_t *data, size_t n) {
    if (!data || n == 0) return NULL;
    long long freqs[HUFFMAN_ALPHA_SIZE] = {0};
    for (size_t i = 0; i < n; i++) freqs[data[i]]++;
    return huffman_build(freqs);
}

void huffman_destroy(HuffTree *tree) {
    if (!tree) return;
    huff_node_destroy(tree->root);
    free(tree);
}

uint8_t *huffman_encode(const HuffTree *tree, const uint8_t *input,
                        size_t in_len, size_t *out_len, int *num_bits) {
    /* TODO: Implement Huffman encoding.
     * 1. Compute total bit count = sum over input[i] of table[input[i]].length
     * 2. Allocate output buffer of ceil(total_bits / 8) bytes.
     * 3. Emit each codeword bit-by-bit (MSB first) into the output buffer.
     * 4. Set *out_len = ceil(total_bits/8), *num_bits = total_bits % 8 (0 = full). */
    if (!tree || !input || in_len == 0 || !out_len || !num_bits) return NULL;
    *out_len = 0; *num_bits = 0;
    return NULL;
}

uint8_t *huffman_decode(const HuffTree *tree, const uint8_t *input,
                        size_t in_len, int num_bits, size_t *out_len) {
    /* TODO: Implement Huffman decoding.
     * Walk the tree bit-by-bit: 0 -> left, 1 -> right.
     * When a leaf is reached, emit its symbol and restart from root. */
    if (!tree || !input || in_len == 0 || !out_len) return NULL;
    *out_len = 0;
    (void)num_bits;
    return NULL;
}

void huffman_print_table(const HuffTree *tree) {
    if (!tree) return;
    printf("Huffman code table:\n");
    for (int i = 0; i < HUFFMAN_ALPHA_SIZE; i++) {
        if (tree->table[i].length > 0) {
            printf("  '%c' (0x%02x): ", (i >= 32 && i < 127) ? i : '.', i);
            for (int b = tree->table[i].length - 1; b >= 0; b--)
                printf("%d", (tree->table[i].bits >> b) & 1);
            printf(" (%d bits)\n", tree->table[i].length);
        }
    }
}

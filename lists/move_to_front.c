/**
 * Move-to-Front List Implementation
 */

#include "move_to_front.h"
#include <stdlib.h>
#include <string.h>

/* =========================================================
 * Self-organizing list
 * ========================================================= */

MTFList *mtf_list_create(void) {
    MTFList *list = (MTFList *)malloc(sizeof(MTFList));
    if (!list) return NULL;
    list->head = list->tail = NULL;
    list->size = 0;
    return list;
}

void mtf_list_destroy(MTFList *list) {
    if (!list) return;
    MTFNode *cur = list->head;
    while (cur) {
        MTFNode *next = cur->next;
        free(cur);
        cur = next;
    }
    free(list);
}

bool mtf_list_insert(MTFList *list, int key, void *data) {
    if (!list) return false;
    MTFNode *node = (MTFNode *)malloc(sizeof(MTFNode));
    if (!node) return false;
    node->key = key;
    node->data = data;
    node->prev = NULL;
    node->next = list->head;
    if (list->head) list->head->prev = node;
    else list->tail = node;
    list->head = node;
    list->size++;
    return true;
}

/* Helper: unlink a node without freeing it. */
static void mtf_unlink(MTFList *list, MTFNode *node) {
    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;
    node->prev = node->next = NULL;
}

MTFNode *mtf_list_access(MTFList *list, int key) {
    /* TODO: Find node with the given key, move it to head, return it.
     * Walk from head to tail; when found, call mtf_unlink then re-insert
     * at head. */
    if (!list) return NULL;
    MTFNode *cur = list->head;
    while (cur) {
        if (cur->key == key) {
            if (cur != list->head) {
                mtf_unlink(list, cur);
                cur->next = list->head;
                if (list->head) list->head->prev = cur;
                else list->tail = cur;
                list->head = cur;
            }
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

bool mtf_list_delete(MTFList *list, int key) {
    if (!list) return false;
    MTFNode *cur = list->head;
    while (cur) {
        if (cur->key == key) {
            mtf_unlink(list, cur);
            free(cur);
            list->size--;
            return true;
        }
        cur = cur->next;
    }
    return false;
}

size_t mtf_list_size(const MTFList *list) {
    return list ? list->size : 0;
}

/* =========================================================
 * MTF transform
 * ========================================================= */

void mtf_transform(const unsigned char *input, int *output, int n) {
    /* TODO: Implement MTF encoding.
     * Maintain a list L = [0, 1, 2, ..., 255].
     * For each byte b = input[i]:
     *   rank = position of b in L
     *   output[i] = rank
     *   move b to front of L */
    if (!input || !output || n <= 0) return;
    unsigned char list[256];
    for (int i = 0; i < 256; i++) list[i] = (unsigned char)i;
    for (int i = 0; i < n; i++) {
        unsigned char b = input[i];
        int rank = 0;
        /* TODO: replace with a more efficient data structure */
        while (list[rank] != b) rank++;
        output[i] = rank;
        /* Shift list[0..rank-1] right by one and put b at front */
        memmove(list + 1, list, (size_t)rank);
        list[0] = b;
    }
}

void mtf_inverse_transform(const int *input, unsigned char *output, int n) {
    /* TODO: Implement MTF decoding (symmetric to encoding).
     * Maintain list L = [0, 1, ..., 255].
     * For each rank r = input[i]:
     *   b = L[r]
     *   output[i] = b
     *   move b to front of L */
    if (!input || !output || n <= 0) return;
    unsigned char list[256];
    for (int i = 0; i < 256; i++) list[i] = (unsigned char)i;
    for (int i = 0; i < n; i++) {
        int rank = input[i];
        unsigned char b = list[rank];
        output[i] = b;
        memmove(list + 1, list, (size_t)rank);
        list[0] = b;
    }
}

/**
 * Fault-Tolerant Linked List Implementation
 */

#include "fault_tolerant_list.h"
#include <stdlib.h>
#include <string.h>

uint32_t ftl_checksum(int key, const void *data) {
    /* Simple XOR-based checksum; a real implementation would use CRC32. */
    uint32_t k = (uint32_t)key;
    uintptr_t d = (uintptr_t)data;
    return k ^ (uint32_t)(d & 0xFFFFFFFFu) ^ (uint32_t)(d >> 32);
}

/* Get the validated next pointer of a node. */
static FTLNode *ftl_next(const FTLNode *node) {
    if (node->next == node->next_copy) return node->next;
    /* Disagreement: use majority vote (only two copies, so pick one
     * and flag as uncertain—real system would use three copies). */
    return node->next; /* TODO: improve with triple redundancy */
}

bool ftl_node_valid(const FTLNode *node) {
    if (!node) return false;
    if (node->magic != FTL_MAGIC) return false;
    if (node->next != node->next_copy) return false;
    if (ftl_checksum(node->key, node->data) != node->checksum) return false;
    return true;
}

FTList *ftl_create(int delta) {
    FTList *list = (FTList *)malloc(sizeof(FTList));
    if (!list) return NULL;
    list->head = NULL;
    list->n = 0;
    list->delta = (delta > 0) ? delta : FTL_DELTA;
    return list;
}

void ftl_destroy(FTList *list) {
    if (!list) return;
    FTLNode *cur = list->head;
    int guard = list->n + list->delta + 1;
    while (cur && guard-- > 0) {
        FTLNode *next = ftl_node_valid(cur) ? ftl_next(cur) : NULL;
        free(cur);
        cur = next;
    }
    free(list);
}

bool ftl_insert(FTList *list, int key, void *data) {
    if (!list) return false;
    FTLNode *node = (FTLNode *)malloc(sizeof(FTLNode));
    if (!node) return false;
    node->magic = FTL_MAGIC;
    node->key = key;
    node->data = data;
    node->next = list->head;
    node->next_copy = list->head;
    node->checksum = ftl_checksum(key, data);
    list->head = node;
    list->n++;
    return true;
}

bool ftl_delete(FTList *list, int key) {
    if (!list) return false;
    FTLNode *prev = NULL;
    FTLNode *cur = list->head;
    int guard = list->n + list->delta + 1;
    while (cur && guard-- > 0) {
        if (ftl_node_valid(cur) && cur->key == key) {
            FTLNode *next = ftl_next(cur);
            if (prev) {
                prev->next = next;
                prev->next_copy = next;
            } else {
                list->head = next;
            }
            free(cur);
            list->n--;
            return true;
        }
        prev = ftl_node_valid(cur) ? cur : prev;
        cur = ftl_node_valid(cur) ? ftl_next(cur) : NULL;
    }
    return false;
}

FTLNode *ftl_search(FTList *list, int key) {
    if (!list) return NULL;
    FTLNode *cur = list->head;
    int guard = list->n + list->delta + 1;
    while (cur && guard-- > 0) {
        if (ftl_node_valid(cur) && cur->key == key) return cur;
        cur = ftl_node_valid(cur) ? ftl_next(cur) : NULL;
    }
    return NULL;
}

void ftl_traverse(FTList *list,
                  void (*callback)(int key, void *data, void *user_data),
                  void *user_data) {
    if (!list || !callback) return;
    FTLNode *cur = list->head;
    int guard = list->n + list->delta + 1;
    while (cur && guard-- > 0) {
        if (ftl_node_valid(cur)) callback(cur->key, cur->data, user_data);
        cur = ftl_node_valid(cur) ? ftl_next(cur) : NULL;
    }
}

int ftl_size(const FTList *list) {
    return list ? list->n : 0;
}

void ftl_inject_fault(FTList *list, int pos) {
    if (!list) return;
    FTLNode *cur = list->head;
    int i = 0, guard = list->n + list->delta + 1;
    while (cur && guard-- > 0) {
        if (i == pos) {
            cur->magic ^= 0xFFFFFFFFu; /* Corrupt magic to simulate fault */
            return;
        }
        cur = ftl_node_valid(cur) ? ftl_next(cur) : NULL;
        i++;
    }
}

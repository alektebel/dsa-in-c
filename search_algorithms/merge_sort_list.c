/**
 * Merge Sort on Linked Lists Implementation
 */

#include "merge_sort_list.h"
#include <stdlib.h>
#include <stdio.h>

ListNode* merge_sort_list(ListNode *head) {
    // TODO: Implement merge sort on linked list
    // Base case: empty or single node
    if (!head || !head->next) return head;
    
    // 1. Split list into two halves
    // 2. Recursively sort both halves
    // 3. Merge sorted halves
    return head;
}

ListNode* merge_sort_list_custom(ListNode *head, list_compare_func_t compare) {
    // TODO: Merge sort with custom comparison
    return head;
}

struct DoublyListNode* merge_sort_doubly_list(struct DoublyListNode *head) {
    // TODO: Merge sort for doubly linked list
    // Similar to singly linked list but maintain prev pointers
    return head;
}

ListNode* list_node_create(int data) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

bool list_insert_front(ListNode **head, int data) {
    // TODO: Insert at front
    ListNode *node = list_node_create(data);
    if (!node) return false;
    node->next = *head;
    *head = node;
    return true;
}

bool list_append(ListNode **head, int data) {
    // TODO: Append at end
    ListNode *node = list_node_create(data);
    if (!node) return false;
    
    if (!*head) {
        *head = node;
        return true;
    }
    
    // Find last node
    ListNode *curr = *head;
    while (curr->next) curr = curr->next;
    curr->next = node;
    return true;
}

int list_length(ListNode *head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

bool list_is_sorted(ListNode *head) {
    // TODO: Check if sorted
    if (!head) return true;
    while (head->next) {
        if (head->data > head->next->data) return false;
        head = head->next;
    }
    return true;
}

ListNode* list_reverse(ListNode *head) {
    // TODO: Reverse list
    ListNode *prev = NULL, *curr = head, *next;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

ListNode* list_merge_sorted(ListNode *list1, ListNode *list2) {
    // TODO: Merge two sorted lists
    if (!list1) return list2;
    if (!list2) return list1;
    
    // Choose head and recursively merge
    return NULL;
}

void list_split(ListNode *head, ListNode **front, ListNode **back) {
    // TODO: Split list using slow/fast pointer
    // Slow moves 1 step, fast moves 2 steps
    // When fast reaches end, slow is at middle
}

void list_print(ListNode *head) {
    printf("List: ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void list_free(ListNode *head) {
    ListNode *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

DoublyListNode* doubly_node_create(int data) {
    DoublyListNode *node = (DoublyListNode*)malloc(sizeof(DoublyListNode));
    if (!node) return NULL;
    node->data = data;
    node->next = node->prev = NULL;
    return node;
}

bool doubly_list_insert_front(DoublyListNode **head, int data) {
    // TODO: Insert at front of doubly linked list
    DoublyListNode *node = doubly_node_create(data);
    if (!node) return false;
    
    node->next = *head;
    if (*head) (*head)->prev = node;
    *head = node;
    return true;
}

void doubly_list_print(DoublyListNode *head) {
    printf("Doubly List: ");
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void doubly_list_free(DoublyListNode *head) {
    DoublyListNode *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

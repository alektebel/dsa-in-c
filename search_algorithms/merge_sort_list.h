/**
 * Merge Sort on Linked Lists Implementation
 * 
 * Merge sort is particularly well-suited for linked lists as it doesn't
 * require random access and can be done in-place with O(1) extra space.
 * 
 * Used in:
 * - Standard library sorting (e.g., Linux kernel list_sort)
 * - External sorting
 * - Database query processing
 */

#ifndef MERGE_SORT_LIST_H
#define MERGE_SORT_LIST_H

#include <stdbool.h>
#include <stddef.h>

// Linked list node
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

// Comparison function type
typedef int (*list_compare_func_t)(const ListNode *a, const ListNode *b);

/**
 * Sort a linked list using merge sort
 * @param head Pointer to head of the list
 * @return Pointer to new head of sorted list
 */
ListNode* merge_sort_list(ListNode *head);

/**
 * Sort a linked list with custom comparison function
 * @param head Pointer to head of the list
 * @param compare Comparison function
 * @return Pointer to new head of sorted list
 */
ListNode* merge_sort_list_custom(ListNode *head, list_compare_func_t compare);

/**
 * Sort a doubly linked list using merge sort
 * @param head Pointer to head of the doubly linked list
 * @return Pointer to new head of sorted list
 */
struct DoublyListNode* merge_sort_doubly_list(struct DoublyListNode *head);

/**
 * Create a new list node
 * @param data Data to store in node
 * @return Pointer to newly created node
 */
ListNode* list_node_create(int data);

/**
 * Insert node at beginning of list
 * @param head Pointer to head pointer
 * @param data Data to insert
 * @return true if successful
 */
bool list_insert_front(ListNode **head, int data);

/**
 * Append node at end of list
 * @param head Pointer to head pointer
 * @param data Data to append
 * @return true if successful
 */
bool list_append(ListNode **head, int data);

/**
 * Get length of list
 * @param head Head of list
 * @return Number of nodes in list
 */
int list_length(ListNode *head);

/**
 * Check if list is sorted
 * @param head Head of list
 * @return true if sorted in ascending order
 */
bool list_is_sorted(ListNode *head);

/**
 * Reverse a linked list
 * @param head Pointer to head pointer
 * @return Pointer to new head
 */
ListNode* list_reverse(ListNode *head);

/**
 * Merge two sorted lists
 * @param list1 First sorted list
 * @param list2 Second sorted list
 * @return Pointer to merged sorted list
 */
ListNode* list_merge_sorted(ListNode *list1, ListNode *list2);

/**
 * Split list into two halves
 * @param head Head of list
 * @param front Pointer to store first half
 * @param back Pointer to store second half
 */
void list_split(ListNode *head, ListNode **front, ListNode **back);

/**
 * Print list
 * @param head Head of list
 */
void list_print(ListNode *head);

/**
 * Free entire list
 * @param head Head of list
 */
void list_free(ListNode *head);

// Doubly linked list node
typedef struct DoublyListNode {
    int data;
    struct DoublyListNode *next;
    struct DoublyListNode *prev;
} DoublyListNode;

/**
 * Create doubly linked list node
 * @param data Data to store
 * @return Pointer to new node
 */
DoublyListNode* doubly_node_create(int data);

/**
 * Insert at front of doubly linked list
 * @param head Pointer to head pointer
 * @param data Data to insert
 * @return true if successful
 */
bool doubly_list_insert_front(DoublyListNode **head, int data);

/**
 * Print doubly linked list
 * @param head Head of list
 */
void doubly_list_print(DoublyListNode *head);

/**
 * Free doubly linked list
 * @param head Head of list
 */
void doubly_list_free(DoublyListNode *head);

#endif // MERGE_SORT_LIST_H

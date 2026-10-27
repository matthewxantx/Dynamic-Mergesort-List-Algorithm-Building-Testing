/* msort.c -- Part 1: merge sort on a singly linked list.
 *
 * RULES (violations lose points):
 *   - Do NOT copy the list into an array, and do NOT call malloc/calloc/realloc
 *     anywhere in this file. You sort by RELINKING the existing nodes.
 *   - No global variables. No library sort functions.
 *   - The sort must be STABLE: nodes with equal keys keep their original order.
 *   - Time must be Theta(n lg n).
 *   - Your code must run with zero errors and zero leaks under Valgrind.
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* split(head)
 *   Splits the list into two lists, in place.
 *   - If the list has n >= 2 nodes: the FIRST list keeps the first ceil(n/2)
 *     nodes (its last node's next must become NULL) and the function returns
 *     the head of the SECOND list (the remaining floor(n/2) nodes).
 *   - If the list has fewer than 2 nodes: return NULL and change nothing.
 *   You may make at most TWO passes over the list (calling list_length()
 *   counts as one pass): count the nodes and then walk to the middle, or use
 *   two pointers (slow/fast) to find the middle in a single pass.
 *
 *   Examples:  1->2->3->4->5  becomes  1->2->3   and returns 4->5
 *              1->2->3->4     becomes  1->2      and returns 3->4
 *              1->2           becomes  1         and returns 2
 */
Node *split(Node *head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    Node *slow = head;
    Node *fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node *second = slow->next;
    slow->next = NULL;
    return second;
}

/* merge(a, b)
 *   a and b are each sorted (non-decreasing keys). Relink their nodes into ONE
 *   sorted list and return its head. Either input may be NULL.
 *   Must be STABLE: when a->key == b->key, the node from 'a' comes first.
 *   Must be iterative (a loop, not recursion) and use O(1) extra space.
 *   Hint: a local 'Node dummy;' (on the stack, not malloc'd) avoids a special
 *   case for the first node.
 */
Node *merge(Node *a, Node *b) {
    Node *head = NULL;
    Node *tail = NULL;
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (a->key <= b->key) {
        head = a;
        a = a->next;
    }
    else {
        head = b;
        b = b->next;
    }
    tail = head;

    while (a && b) {
        if (a->key <= b->key) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    if (a != NULL) {
        tail->next = a;
    }
    else {
        tail->next = b;
    }
    return head;
}

/* mergesort_list(head)
 *   Sorts the list in non-decreasing order of key and returns the new head.
 *   Recursive: base case, split, sort each half, merge.
 */
Node *mergesort_list(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    Node *second = split(head);
    head = mergesort_list(head);
    second = mergesort_list(second);
    return merge(head, second);
}

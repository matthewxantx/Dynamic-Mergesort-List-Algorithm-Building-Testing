/* fixed.c -- Part 2, Task 4.
 *
 * Pick ONE defective candidate from candidates.c. Copy its code here, give the
 * copied functions new names (candidates.c already uses names like merge1 and
 * sort1, and those are static there, so reusing them in this file is fine, but
 * choosing clear new names helps you), FIX the defect, and make fixed_sort()
 * call your corrected version.
 *
 * Then test it with:   ./audit 5 <n> <max_key>
 * It must pass every check you wrote in audit.c's student_checks().         */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Split the list into two halves. */
static Node *fixed_split(Node *head) {
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

/* Merge two sorted lists, preserving stability. */
static Node *fixed_merge(Node *a, Node *b) {
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
    while (a != NULL && b != NULL) {
        if (a->key <= b->key) {
            tail->next = a;
            a = a->next;
        }
	else {
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

/* Recursively sort the list. */
static Node *fixed_mergesort(Node *head) {
    if ((head == NULL) || (head->next == NULL)) {
        return head;
    }
    Node *second = fixed_split(head);
    head = fixed_mergesort(head);
    second = fixed_mergesort(second);
    return fixed_merge(head, second);
}

/* Entry point called by audit.c for candidate 5. */
Node *fixed_sort(Node *head) {
    return fixed_mergesort(head);
}

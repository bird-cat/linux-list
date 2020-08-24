#include <stdlib.h>
#include "list.h"

#include "common.h"
#include "list-sort.h"

static void list_insert(struct list_head *node,
                        struct list_head *prev,
                        struct list_head *next)
{
    node->next = next;
    next->prev = node;
    node->prev = prev;
    prev->next = node;
}

static void list_merge(struct list_head *head1, struct list_head *head2)
{
    LIST_HEAD(tmp_head);

    while (!list_empty(head1) && !list_empty(head2)) {
        if (cmpint(&list_first_entry(head1, struct listitem, list)->i,
                   &list_first_entry(head2, struct listitem, list)->i) < 0) {
            list_move_tail(head1->next, &tmp_head);
        } else {
            list_move_tail(head2->next, &tmp_head);
        }
    }
    if (!list_empty(head1))
        list_splice_tail(head1, &tmp_head);
    if (!list_empty(head2))
        list_splice_tail(head2, &tmp_head);
    list_insert(head1, tmp_head.prev, tmp_head.next);
}

static void list_divide(struct list_head *head1, struct list_head *head2)
{
    struct list_head *fast = head1, *slow = head1;
    while (fast->next != head1 && fast->next->next != head1) {
        fast = fast->next->next;
        slow = slow->next;
    }

    list_cut_position(head2, head1, slow);
}

void list_mergesort(struct list_head *head)
{
    if (list_empty(head) || list_is_singular(head))
        return;

    LIST_HEAD(head2);

    list_divide(head, &head2);
    list_mergesort(head);
    list_mergesort(&head2);

    list_merge(head, &head2);
}


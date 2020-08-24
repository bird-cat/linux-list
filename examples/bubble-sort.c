#include <stdlib.h>
#include "list.h"

#include "common.h"
#include "list-sort.h"

static void emerge(struct list_head *head, struct list_head **tail)
{
    struct list_head *cur = head->next;
    while (cur->next != *tail) {
        if (cmpint(&list_entry(cur, struct listitem, list)->i,
                   &list_entry(cur->next, struct listitem, list)->i) > 0)
            list_move(cur->next, cur->prev);
        else
            cur = cur->next;
    }
    *tail = cur;
}

void list_bubblesort(struct list_head *head)
{
    struct list_head *tail = head;

    while (head->next != tail)
        emerge(head, &tail);
}

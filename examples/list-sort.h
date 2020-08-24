#ifndef LIST_SORT_H
#define LIST_SORT_H

/**
 * list_XXXsort - sort a list by XXX sorting function
 * @head: pointer to the head of the list
 */
void list_insertsort(struct list_head *head);
void list_mergesort(struct list_head *head);
void list_qsort(struct list_head *head);
void list_bubblesort(struct list_head *head);

#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "list-sort.h"
#include "list.h"

#include "common.h"

#ifndef SIZE
#define SIZE 256
#endif
static uint16_t values[SIZE];

#define ANALYSIS(sorting_function, list_name)                           \
    do {                                                                \
        gettimeofday(&start, NULL);                                     \
        sorting_function(&list_name);                                   \
        gettimeofday(&end, NULL);                                       \
        timersub(&end, &start, &diff);                                  \
        fprintf(fp, "%ld %f\n", len, diff.tv_sec * 1e6 + diff.tv_usec); \
    } while (0)

static void correctness_and_free(struct list_head *head, size_t len)
{
    struct listitem *item, *is;
    int i = 0;
    list_for_each_entry_safe (item, is, head, list) {
        assert(item->i == values[i]);
        list_del(&item->list);
        free(item);
        i++;
    }

    assert(i == len);
    assert(list_empty(head));
}

static char *strcat_gen(char *s1, const char *s2)
{
    char *s = (char *) malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(s, s1);
    strcat(s, s2);
    return s;
}

// @argv[1]: sorting fuction name
int main(int argc, char **argv)
{
    assert(argc == 2);

    struct list_head testlist;
    struct listitem *item = NULL;
    struct timeval start, end, diff;
    size_t i;

    char *fname = strcat_gen(argv[1], ".log");
    FILE *fp = fopen(fname, "w");

    for (size_t len = 1; len <= SIZE; len++) {

#ifdef RANDOM
        random_shuffle_array(values, (uint16_t) len);
#else
        for (i = 0; i < len; i++)
            values[i] = (uint16_t) i;
#endif

        INIT_LIST_HEAD(&testlist);
        assert(list_empty(&testlist));

        for (i = 0; i < len; i++) {
            item = (struct listitem *) malloc(sizeof(*item));
            assert(item);
            item->i = values[i];
            list_add_tail(&item->list, &testlist);
        }

        assert(!list_empty(&testlist));

#ifdef RANDOM
        qsort(values, len, sizeof(values[0]), cmpint);
#endif

        if (!strcmp(argv[1], "list_insertsort"))
            ANALYSIS(list_insertsort, testlist);
        else if (!strcmp(argv[1], "list_qsort"))
            ANALYSIS(list_qsort, testlist);
        else if (!strcmp(argv[1], "list_mergesort"))
            ANALYSIS(list_mergesort, testlist);
        else if (!strcmp(argv[1], "list_bubblesort"))
            ANALYSIS(list_bubblesort, testlist);
        else {
            printf("Invalid sorting function\n");
            exit(0);
        }

        correctness_and_free(&testlist, len);
    }
    free(fname);
    fclose(fp);

    return 0;
}

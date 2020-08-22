#include <assert.h>
#include <stdlib.h>
#include "list.h"

#include "common.h"

static uint16_t values[256];

int main(void)
{
    struct list_head testlist;
    struct listitem *item = NULL, *safe = NULL;
    size_t i;

    random_shuffle_array(values, ARRAY_SIZE(values));

    INIT_LIST_HEAD(&testlist);
    assert(list_empty(&testlist));

    for (i = 1; i < ARRAY_SIZE(values); i++) {
        item = (struct listitem *) malloc(sizeof(struct list_item));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }

    assert(!list_empty(&testlist));

    qsort(values, ARRAY_SIZE(values), sizeof(values[0]), cmpint);
    /* Sorting function */
    list_insertsort(&testlist);

    i = 0;
    list_for_each_entry_safe (item, safe, testlist, list) {
        assert(item->i == values[i]);
        list_del(&item->list);
        free(item);
        i++;
    }

    assert(i == ARRAY_SIZE(values));
    assert(list_empty(&testlist));

    return 0;
}

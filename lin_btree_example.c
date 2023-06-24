#include "lin_btree.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    uint32_t key;
    int32_t data;
} foo_t;

/**
 * Comparison callback for foo_t. Works on bst constructed
 * from array sorted in ascending order
 */
int foo_cmp_cb(void *key, void *elem)
{
    uint32_t *key_ = (uint32_t *)key;
    foo_t *elem_ = (foo_t *)elem;

    if (*key_ > elem_->key)
    {
        return 1;
    }
    else if (*key_ < elem_->key)
    {
        return -1;
    }

    return 0;
}

/**
 * An array of foo_t structs, sorted in ascending order by
 * struct member 'key'
 */
foo_t sorted_array[] = {{.key = 10, .data = 134553},
                        {.key = 13, .data = 35235},
                        {.key = 17, .data = 76357},
                        {.key = 43, .data = 90},
                        {.key = 67, .data = -14},
                        {.key = 68, .data = 1414},
                        {.key = 75, .data = 1235226},
                        {.key = 89, .data = 798983},
                        {.key = 91, .data = 23525},
                        {.key = 99, .data = 98347689}};

int main()
{
    size_t arr_elem_size = sizeof(sorted_array[0]);
    size_t arr_elem_cnt = sizeof(sorted_array) / sizeof(sorted_array[0]);

    complete_btree_from_array(sorted_array, arr_elem_size, arr_elem_cnt);

    foo_t *bst = sorted_array;

    uint32_t key;
    bool found;

    key = 10;
    found = linear_bst_search(bst, arr_elem_size, arr_elem_cnt, &key, &foo_cmp_cb) != NULL;
    printf("Key %u: %s\n", key, found ? "FOUND" : "NOT FOUND");

    key = 67;
    found = linear_bst_search(bst, arr_elem_size, arr_elem_cnt, &key, &foo_cmp_cb) != NULL;
    printf("Key %u: %s\n", key, found ? "FOUND" : "NOT FOUND");

    key = 90;
    found = linear_bst_search(bst, arr_elem_size, arr_elem_cnt, &key, &foo_cmp_cb) != NULL;
    printf("Key %u: %s\n", key, found ? "FOUND" : "NOT FOUND");

    key = 10020;
    found = linear_bst_search(bst, arr_elem_size, arr_elem_cnt, &key, &foo_cmp_cb) != NULL;
    printf("Key %u: %s\n", key, found ? "FOUND" : "NOT FOUND");
}
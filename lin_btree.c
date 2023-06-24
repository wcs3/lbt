#include "lin_btree.h"

static void rotate(void *arr, const size_t elem_size, const size_t elem_cnt, int32_t d);
static void reverse(void *arr, const size_t elem_size, const size_t elem_cnt);
static void inv_faro(void *arr, const size_t elem_size, const size_t elem_cnt);

void lin_bst_from_sorted_array(void *arr, const size_t elem_size, const size_t elem_cnt)
{
    uint8_t h = 1;
    while ((2 << h) - 1 < elem_cnt)
    {
        h++;
    }

    for (uint8_t lvl = h; lvl > 0; lvl--)
    {
        size_t es = MIN((2 << lvl) - 1, elem_cnt);
        size_t lc = MIN(1 << lvl, elem_cnt - ((1 << lvl) - 1));

        inv_faro(arr, elem_size, 2 * lc - 1);
        rotate(arr, elem_size, es, lc);
    }
}

void *linear_bst_search(const void *arr,
                     const size_t elem_size,
                     const size_t elem_cnt, void *key,
                     int (*cmp_cb)(void *key, void *node))
{
    assert(cmp_cb != NULL);

    size_t i = 0;
    while (i < elem_cnt)
    {
        int cmp_res = cmp_cb(key, arr + elem_size * i);
        if (cmp_res > 0)
        {
            i = 2 * i + 2;
        }
        else if (cmp_res < 0)
        {
            i = 2 * i + 1;
        }
        else
        {
            return arr + elem_size * i;
        }
    }

    return NULL;
}

static void reverse(void *arr, const size_t elem_size, const size_t elem_cnt)
{
    uint8_t *front = arr;
    uint8_t *back = arr + (elem_cnt - 1) * elem_size;

    while (front < back)
    {
        uint8_t *next_front = front + elem_size;
        while (front < next_front)
        {
            uint8_t tmp = *front;
            *front = *back;
            *back = tmp;

            front++;
            back++;
        }

        back -= elem_size * 2;
    }
}

static void rotate(void *arr, const size_t elem_size, const size_t elem_cnt, int32_t d)
{
    d = d % elem_cnt;
    d = (d < 0) ? d + elem_cnt : d;

    reverse(arr, elem_size, d);
    reverse(arr + d * elem_size, elem_size, elem_cnt - d);
    reverse(arr, elem_size, elem_cnt);
}

static void inv_faro(void *arr, const size_t elem_size, const size_t elem_cnt)
{
    size_t arr_size = elem_size * elem_cnt;
    uint8_t tmp[arr_size];

    size_t i = 0;

    size_t j = 0;
    while (j < arr_size)
    {
        size_t k = i + elem_size;
        while (i < k)
        {
            tmp[i] = ((uint8_t *)arr)[j];
            ++i;
            ++j;
        }
        j += elem_size;
    }

    j = elem_size;
    while (j < arr_size)
    {
        size_t k = i + elem_size;
        while (i < k)
        {
            tmp[i] = ((uint8_t *)arr)[j];
            ++i;
            ++j;
        }
        j += elem_size;
    }

    // copy result back to arr
    for (i = 0; i < arr_size; ++i)
    {
        ((uint8_t *)arr)[i] = tmp[i];
    }
}
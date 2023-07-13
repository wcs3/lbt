#ifndef __LBT_H__
#define __LBT_H__

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Transform, in place, an array of arbitrary type to a 
 * linear, complete binary tree. 
 * 
 * If the array type can be ordered, and the array is sorted by
 * that order, then this function creates a complete binary 
 * search tree.
 * 
 * For example, the sorted array of integers 
 *      [0, 1, 3, 4, 6, 7, 9]
 * would be transformed to
 *      [4, 1, 7, 0, 3, 6, 9]
 * which is the linear form of
 *                4
 *              /   \
 *             1     7
 *            / \   / \
 *           0   3 6   9
 * , i.e. a complete binary search tree.
 *
 * @param arr pointer to arbitrary type array
 * @param elem_size size of single array element in bytes
 * @param elem_cnt number of elements in array
 */
void lbt_from_array(void *arr,
                               const size_t elem_size,
                               const size_t elem_cnt);

/**
 * @brief Search a linear bst for an element with a given key
 *
 * The user provides a callback to the function that compares
 * the search key and current search node, and returns a value
 * to direct the search:
 *
 * - return value > 0: search continues through
 *   the right child-node of the current node.
 *
 * - return value < 0: search continues through
 *   the left child-node of the current node.
 *
 * - return value = 0: search terminates, and the current
 *   node is returned.
 *
 * @param lin_bst pointer to linear binary search tree array
 * @param elem_size size of single array element in bytes
 * @param elem_cnt number of elements in array
 * @param key the key whose element we are in search of
 * @param cmp_cb key comparison callback
 * @return pointer to node if found, NULL if not.
 */
void *lbst_search(const void *lin_bst,
                     const size_t elem_size,
                     const size_t elem_cnt,
                     void *key,
                     int (*cmp_cb)(void *key, void *node));

#endif // __LBT_H__

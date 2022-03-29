/***********************************************
 * Recursive Balanced Binary Search Tree (AVL) *
 * Developer: Tomer Alayof                     *
 * Written: 2021-01-26                         *
 *                                             *
 * Reviewer: Daniella                          *
 **********************************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct avl avl_t;

typedef int (*avl_cmp_func_t)(const void *left, const void *right);
typedef int (*avl_action_func_t)(void *data, void *param);

typedef enum traversal_order
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    NUM_OF_ORDERS
} order_t;


/* DESCRIPTION: 
 * creates a Recursive Binary Search Tree. return NULL in case of failure.
 * call BSTDestroy upon done using, to free the memory.
 *
 * PARAMS: 
 * avl_cmp_func_t - pointer to the function which decides how to sort the tree
 *
 * RETURN:
 * pointer to the created BST.
 *
 * Complexity: O(1) time, O(1) space.
 */
avl_t *AVLCreate(avl_cmp_func_t cmp_func);

/* DESCRIPTION: 
 * destroy the BST and free its memory.
 *
 * PARAMS: 
 * avl_t - tree to be destroyed
 *
 * RETURN:
 * none
 *
 *Complexity: O(n) time, O(log n) average space. 
 */
void AVLDestroy(avl_t *avl);

/* DESCRIPTION: 
 * return the number of nodes in the tree
 *
 * PARAMS: 
 * const avl_t * - tree to be checked
 *
 * RETURN:
 * number of nodes in the tree 
 *
 * Complexity: O(n) time, O(log n) average space. 
*/
size_t AVLSize(const avl_t *avl);

/* DESCRIPTION: 
 * checks if the tree is empty. if yes return 1, else return 0.
 *
 * PARAMS: 
 * const avl_t * - tree to be checked
 *
 * RETURN:
 * int - 1 for true, 0 for false.
 *
 * Complexity: O(1) time, O(1) space. 
*/
int AVLIsEmpty(const avl_t *avl);

/* DESCRIPTION: 
 * Insert new element to the tree.
 *
 * PARAMS: 
 * avl_t * - tree to be inserted to.
 * void * - data for the new element
 *
 * RETURN:
 * int - 0 in case of success, otherwise failure result.
 *
 * Complexity: O(log n) average time, O(log n) average space. 
 */
int AVLInsert(avl_t *avl, void *data);

/* Complexity: O(log n) average time, O(log n) average space. */
void AVLRemove(avl_t *avl, const void *data);

/* DESCRIPTION: 
 * Complexity: O(1) time, O(1) space. */
/* Height of an empty tree is 0. Height of a non empty tree with only one node is 1. 
*/
size_t AVLHeight(const avl_t *avl);

/* DESCRIPTION: 
 * find an element with data_to_find in the tree. if found, return it.
 * if not found, returns BSTEnd(tree) 
 *
 * PARAMS: 
 * bst_t - tree to find on.
 * void * - data to search for.
 *
 * RETURN:
 * bst_iter_t - element that was found (or not).
 *

Complexity: O(log n) average time, O(log n) average space.
*/
void *AVLFind(const avl_t *avl, const void *data);

/*DESCRIPTION: 
 * traverse (in in user decition method) the tree and active action_func on each element, using param.
 *
 * PARAMS: 
 * avl_t * - tree to traverse.
 * avl_action_func_t - action to make
 * void * -  parameter for the action function.
 * order_t - method(pre,in,post).
 * RETURN:
 * int - 0 in case of success, otherwise failure result.
 *
 * Complexity: O(n) time, O(log n) average space. 
*/
int AVLForEach(avl_t *avl, avl_action_func_t action_func, void *param, order_t order);

#ifdef DEBUG
void PrintTreeInOrder(avl_t *tree);
void PrintTreeByLevels(avl_t *tree);
#endif

#endif /* __AVL_H__ */
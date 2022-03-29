/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          18/1/22                                                 ***
 *** Reviewer:      Gal 		                                            ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** header file for BST.		                                            ***
 ******************************************************************************
 \*****************************************************************************/


#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node* bst_iter_t;

typedef int (*bst_cmp_func_t)(const void *data1, const void *data2);
typedef int (*bst_action_func_t)(void *data, void *param);


/* DESCRIPTION: 
 * creates a Binary Search Tree. return NULL in case of failure.
 * call BSTDestroy upon done using, to free the memory.
 *
 * PARAMS: 
 * bst_cmp_func_t - pointer to the function which decides how to sort the tree
 *
 * RETURN:
 * pointer to the created BST.
 *
 *  Complexity: O(1) time, O(1) space.
 */
bst_t *BSTCreate(bst_cmp_func_t cmp_func);

/* DESCRIPTION: 
 * destroy the BST and free its memory.
 *
 * PARAMS: 
 * bst_t - tree to be destroyed
 *
 * RETURN:
 * none
 *
 *time complexity: O(n), space complexity O(1) 
 */
void BSTDestroy(bst_t *tree);

/* DESCRIPTION: 
 * checks the size of the tree
 *
 * PARAMS: 
 * bst_t - tree to checks its size
 *
 * RETURN:
 * size_t - size of the tree
 *
 *time complexity: O(n), space complexity O(1) 
 */
size_t BSTSize(const bst_t *tree);

/* DESCRIPTION: 
 * checks if the tree is empty. if yes return 1, else return 0.
 *
 * PARAMS: 
 * bst_t - tree to be checked
 *
 * RETURN:
 * int - 1 for true, 0 for false.
 *
 *time complexity: O(1), space complexity O(1) 
 */
int BSTIsEmpty(const bst_t *tree);

/* DESCRIPTION: 
 * Insert new element to the tree.
 *
 * PARAMS: 
 * bst_t - tree to be inserted to.
 * void - data for the new element
 *
 * RETURN:
 * bst_iter_t - the new element that was inserted.
 *
  Complexity: O(log n) average time. O(1) space.
 */
bst_iter_t BSTInsert(bst_t *tree, void *data);

/* DESCRIPTION: 
 * remove the element iter from the tree
 *
 * PARAMS: 
 * bst_iter_t - element to be removed
 *
 * RETURN:
 * none
 *
  Complexity: O(log n) average time. O(1) space.
 */
void BSTRemove(bst_iter_t iter);

/* DESCRIPTION: 
 * get the first element of the tree for InOrder traversal
 *
 * PARAMS: 
 * bst_t - the tree
 *
 * RETURN:
 * bst_iter_t - the begging of inorder traversal element
 *
  Complexity: O(log n) average time. O(1) space.
 */
bst_iter_t BSTBegin(const bst_t *tree);

/* DESCRIPTION: 
 * get the last element of the tree for InOrder traversal
 * (this line is not good, shall the user know that end is stub?)
 *
 * PARAMS: 
 * bst_t - the tree
 *
 * RETURN:
 * bst_iter_t - the end of inorder traversal element
 *
  Complexity: O(1) average time. O(1) space.
 */
bst_iter_t BSTEnd(const bst_t *tree);

/* DESCRIPTION: 
 * get the previous element of iter, according to inorder traversal
 *
 * PARAMS: 
 * bst_iter_t - element to get its prev
 *
 * RETURN:
 * bst_iter_t - the element prev to iter, according to inorder traversal
 *
  Complexity: O(log n) average time. O(1) space.
 */
bst_iter_t BSTPrev(bst_iter_t iter);

/* DESCRIPTION: 
 * get the next element of iter, according to inorder traversal
 *
 * PARAMS: 
 * bst_iter_t - element to get its next
 *
 * RETURN:
 * bst_iter_t - the element next to iter, according to inorder traversal
 *
  Complexity: O(log n) average time. O(1) space.
 */
bst_iter_t BSTNext(bst_iter_t iter);

/* DESCRIPTION: 
 * checks if two iterators are equal.
 *
 * PARAMS: 
 * bst_iter_t - first iterator
 * bst_iter_t - second iterator
 *
 * RETURN:
 * boolean integer, 1 for true and 0 for false
 *
  Complexity: O(1) average time. O(1) space.
 */
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);

/* DESCRIPTION: 
 * get the data of iter
 *
 * PARAMS: 
 * bst_iter_t - element to get its data
 *
 * RETURN:
 * void pointer to the data of iter
 *
  Complexity: O(1) average time. O(1) space.
 */
void *BSTGetData(bst_iter_t iter);

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
  Complexity: O(log n) average time. O(1) space.
 */
bst_iter_t BSTFind(const bst_t *tree, void *data_to_find);

/* DESCRIPTION: 
 * traverse (in inorder method) the tree from element "from"
 * to element "to" and active action_func on each element, using param.
 *
 * PARAMS: 
 * bst_iter_t - from where to start to search
 * bst_iter_t - to where to search (to not included!)
 * vst_action_func_t - pointer to action functions to active on elements
 * void * - parameter for the action function.
 *
 * RETURN:
 * integer with status: 0 for success and -1 for failure.
 *
  Complexity: O(n) average time. O(1) space.
 */
int BSTForEach(bst_iter_t from, bst_iter_t to,
	bst_action_func_t action_func, void *param);

#endif /* __BST_H__ */









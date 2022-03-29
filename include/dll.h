#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

/*
struct dlist
{
	struct dlist_node *head;
	struct dlist_node *tail;
};

typedef struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
} dlist_node_t;
*/

typedef struct dlist dlist_t;
typedef struct dlist_node* dlist_iter_t;
typedef int (*match_func_t)(const void *data, void *param);
typedef int (*action_func_t)(void *data, void *param);

/* O(1) time, O(1) memory */
dlist_t *DListCreate(void);

/* O(n) time, O(1) memory */
void DListDestroy(dlist_t *dll);

/* O(1) time, O(1) memory */
int DListIsEmpty(const dlist_t *dll);

/* O(n) time, O(1) memory */
size_t DListSize(const dlist_t *dll);

/* O(1) time, O(1) memory */
dlist_iter_t DListInsert(dlist_iter_t iter, void *data);

/* O(1) time, O(1) memory */
dlist_iter_t DListRemove(dlist_iter_t iter);

/* O(1) time, O(1) memory */
dlist_iter_t DListPushFront(dlist_t *dll, void *data);

/* O(1) time, O(1) memory */
dlist_iter_t DListPushBack(dlist_t *dll, void *data);

/* O(1) time, O(1) memory */
void *DListPopFront(dlist_t *dll);

/* O(1) time, O(1) memory */
void *DListPopBack(dlist_t *dll);

/* O(1) time, O(1) memory */
void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);

/* O(1) time, O(1) memory */
dlist_iter_t DListBegin(const dlist_t *dll);

/* O(1) time, O(1) memory */
dlist_iter_t DListEnd(const dlist_t *dll);

/* O(1) time, O(1) memory */
dlist_iter_t DListNext(dlist_iter_t iter);

/* O(1) time, O(1) memory */
dlist_iter_t DListPrev(dlist_iter_t iter);

/* O(1) time, O(1) memory */
void *DListGetData(dlist_iter_t iter);

/* O(1) time, O(1) memory */
int DListIsEqual(dlist_iter_t iter1, dlist_iter_t iter2);

/* O(n) time, O(1) memory */
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param);

/* O(n) time, O(1) memory */
int DListMultiFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param, dlist_t *result_list);

/* O(n) time, O(1) memory */
int DListForEach(dlist_iter_t from, dlist_iter_t to,
	action_func_t action_func, void *param);

#endif /* __DLIST_H__ */








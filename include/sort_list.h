#ifndef __SORT_LIST_H__
#define __SORT_LIST_H__

/*#include "../dll/dll.h"*/

#include "dll.h"

typedef int (*cmp_func_t)(const void *left, const void *right);

typedef struct sort_list sort_list_t;
typedef struct sort_list_iter sort_list_iter_t;

struct sort_list_iter
{
    dlist_iter_t it;
#ifdef DEBUG
    sort_list_t *slist;
#endif
};


/*to know 2 iterators from same list*/ 

/* Complexity: O(1) time, O(1) memory. */
sort_list_t *SortListCreate(cmp_func_t sort_func);

/* Complexity: O(n) time, O(1) memory. */
void SortListDestroy(sort_list_t *slist);

/* Complexity: O(n) time, O(1) memory. */
size_t SortListSize(const sort_list_t *slist);

/* Complexity: O(1) time, O(1) memory. */
int SortListIsEmpty(const sort_list_t *slist);

/* Complexity: O(n) time, O(1) memory. */
sort_list_iter_t SortListInsert(sort_list_t *slist, void *data);

/* Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListRemove(sort_list_iter_t iter);

/* Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListBegin(const sort_list_t *slist);

/* Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListEnd(const sort_list_t *slist);

/* Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListNext(sort_list_iter_t iter);

/* Complexity: O(1) time, O(1) memory. */
sort_list_iter_t SortListPrev(sort_list_iter_t iter);

/* Complexity: O(1) time, O(1) memory. */
void *SortListGetData(sort_list_iter_t iter);

/* Complexity: O(1) time, O(1) memory. */
int SortListIterIsEqual(sort_list_iter_t iter1, sort_list_iter_t iter2);

/* Complexity: O(1) time, O(1) memory. */
void *SortListPopFront(sort_list_t *slist);

/* Complexity: O(1) time, O(1) memory. */
void *SortListPopBack(sort_list_t *slist);

/* Complexity: O(n) time, O(1) memory. */
/* ifdef NDEBUG: checks that 'from' and 'to' are from the same list */
int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, 
    action_func_t action_func, void *param);

/* Complexity: O(n) time, O(1) memory. */
void SortListMerge(sort_list_t *dest, sort_list_t *src);

/* Complexity: O(n) time, O(1) memory. */
sort_list_iter_t SortListFind(sort_list_t *slist, sort_list_iter_t from, 
    sort_list_iter_t to, const void *data);

/* Complexity: O(n) time, O(1) memory. */
sort_list_iter_t SortListFindIf(sort_list_iter_t from, sort_list_iter_t to, 
    match_func_t match_func, const void *param);


#endif /* __SORT_LIST_H__ */







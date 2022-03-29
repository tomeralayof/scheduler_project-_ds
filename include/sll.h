#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>  /* size_t */

typedef struct slist slist_t;
typedef struct slist_node* slist_iter_t; 

typedef int (*match_func_t)(const void *data, void *param);
typedef int (*action_func_t)(void *data, void *param);

/*
 time complexity: O(1), space complexity O(1)

	params: no param
	motivation: create a node consist of data equal to null and next node equal to null to init our list.
	function return a pointer to the first node of the list
*/
slist_t *SListCreate(void);

/* time complexity: O(n), space complexity O(1) */
void SListDestroy(slist_t *slist);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListInsertBefore( slist_iter_t where,  void *data); 

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListInsertAfter(slist_iter_t where, void *data);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListRemove(slist_iter_t iterator);

/* time complexity: O(n), space complexity O(1) */
size_t SListCount( slist_t *slist);

/* time complexity: O(1), space complexity O(1) */
int SListIsEmpty(const slist_t *slist);

/* time complexity: O(n), space complexity O(1) */
slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to, match_func_t is_match, void *param); 

/* time complexity: O(n), space complexity O(1) */
int SListForEach(const slist_iter_t from, const slist_iter_t to, action_func_t action_func, void *param);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListBegin(slist_t *slist);

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListEnd( slist_t *slist); 
/* we want the list to work with exactly one dummy for something. after we will read about dummies we will know what for*/

/* time complexity: O(1), space complexity O(1) */
slist_iter_t SListNext(const slist_iter_t iterator);

/* time complexity: O(1), space complexity O(1) */
void *SListGetData(const slist_iter_t iterator);

/* time complexity: O(1), space complexity O(1) */
void SListSetData(slist_iter_t iterator, void *data);

/* time complexity: O(1), space complexity O(1) */
int SListIsEqual(const slist_iter_t iterator1, const slist_iter_t iterator2);

void SListAppend(slist_t *dest, slist_t *src);

#endif /* __SLIST_H__ */















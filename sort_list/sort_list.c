#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/

#include "../include/sort_list.h"

/*reviewed by shoshana*/

struct sort_list
{
	dlist_t * dll;
	cmp_func_t compare_function;
};

sort_list_t *SortListCreate(cmp_func_t sort_func)
{
	
	sort_list_t *sort_list = NULL;
	
	assert(NULL != sort_func);
	
	sort_list = (sort_list_t *)malloc(sizeof(sort_list_t));
	if(NULL == sort_list)
	{
		return NULL;
	}
	
	sort_list-> dll = DListCreate();
	if(NULL == sort_list-> dll)
	{
		free(sort_list);
		sort_list = NULL;
		return NULL;
		
	}
	sort_list-> compare_function = sort_func;
	
	return sort_list;
}

void SortListDestroy(sort_list_t *slist)
{
	
	assert(NULL != slist);

	DListDestroy(slist->dll);
	slist->dll = NULL;
	
	free(slist);
	slist = NULL;
}

sort_list_iter_t SortListInsert(sort_list_t *slist, void *data)
{

	sort_list_iter_t iter_runner = {0};
	sort_list_iter_t end_of_list = {0};
	
	assert(NULL != slist);
	
	iter_runner = SortListBegin(slist);
	
	end_of_list = SortListEnd(slist);
	
	while (!SortListIterIsEqual(iter_runner, end_of_list) && slist->compare_function(data,SortListGetData(iter_runner)) > 0 )
	{
		iter_runner = SortListNext(iter_runner);
	}
	
	iter_runner.it = DListInsert(iter_runner.it,data);
	
	return iter_runner;
}

sort_list_iter_t SortListRemove(sort_list_iter_t iter)
{
	
	iter.it = DListRemove(iter.it);
		
	return iter;
}

int SortListIsEmpty(const sort_list_t *slist)
{
	
	assert(NULL != slist);

	return DListIsEmpty(slist->dll);
}

size_t SortListSize(const sort_list_t *slist)
{
	
	assert(NULL != slist);

	return DListSize(slist->dll);
}


sort_list_iter_t SortListNext(sort_list_iter_t iter)
{

	assert(NULL != iter.it);
	
	iter.it = DListNext(iter.it);
	
	return iter;
}


sort_list_iter_t SortListPrev(sort_list_iter_t iter)
{
	
	assert(NULL != iter.it);
	
	iter.it = DListPrev(iter.it);
	
	return iter;
}

void *SortListGetData(sort_list_iter_t iter)
{
	assert(NULL != iter.it);
	
	return DListGetData(iter.it);
}


int SortListIterIsEqual(sort_list_iter_t iter1, sort_list_iter_t iter2)
{
	assert(NULL != iter1.it);
	assert(NULL != iter2.it);
	
	return DListIsEqual(iter1.it,iter2.it);
}

sort_list_iter_t SortListBegin(const sort_list_t *slist)
{
	
    sort_list_iter_t iter = {0};
    
    assert(NULL != slist);
        
	iter.it = DListBegin(slist->dll);
	
	
	#ifdef DEBUG
		iter.slist = (sort_list_t *)slist; 
	#endif	
	
	return iter;
}

sort_list_iter_t SortListEnd(const sort_list_t *slist)
{

    sort_list_iter_t iter = {0};
    
    assert(NULL != slist);
    
	iter.it =  DListEnd(slist->dll);
	
	#ifdef DEBUG
		iter.slist = (sort_list_t *)slist; /*recognize the list on debug mode*/
	#endif
	
	return iter;
}

void *SortListPopFront(sort_list_t *slist)
{	

	assert(NULL != slist);
	
	return DListPopFront(slist->dll);
}

void *SortListPopBack(sort_list_t *slist)
{
	assert(NULL != slist);
	
	return DListPopBack(slist->dll);
}


int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, action_func_t action_func, void *param)
{

	assert(NULL != action_func);
	assert(NULL != from.it);
	assert(NULL != to.it);
	
	#ifdef DEBUG
    assert(from.slist == to.slist);
	#endif

	return DListForEach(from.it,to.it,action_func,param);
}

sort_list_iter_t SortListFindIf(sort_list_iter_t from, sort_list_iter_t to,match_func_t match_func, const void *param)
{
	assert(NULL != match_func);

    from.it = DListFind(from.it, to.it, match_func, (void *)param);

	return from;	
}

sort_list_iter_t SortListFind(sort_list_t *slist, sort_list_iter_t from, sort_list_iter_t to, const void *data)
{

	assert(NULL != slist);

	while(!SortListIterIsEqual(from,to) && 0 != slist->compare_function(SortListGetData(from),data))
	{
		from = SortListNext(from);
	}

	return from;
}



 void SortListMerge(sort_list_t *dest, sort_list_t *src)
{

	sort_list_iter_t where;
	sort_list_iter_t to;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	where = SortListBegin(dest);
	to = SortListBegin(src);
	
	while(!SortListIterIsEqual(where,SortListEnd(dest)) && !SortListIterIsEqual(to,SortListEnd(src)))
	{	
	
		while(!SortListIterIsEqual(where,SortListEnd(dest)) && ((dest->compare_function(SortListGetData(where), SortListGetData(to)) <= 0)))
		{
			where = SortListNext(where);		
		}
			
		while(!SortListIterIsEqual(to,SortListEnd(src)) && (dest->compare_function(SortListGetData(where), SortListGetData(to)) > 0))
		{
			to = SortListNext(to);
		}
				
		DListSplice(where.it,DListBegin(src->dll),to.it);
	}
} 

 
 
 
 



















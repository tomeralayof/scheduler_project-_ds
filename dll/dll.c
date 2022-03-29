#include <stdlib.h> /*malloc*/
#include <assert.h>

#include "../include/dll.h" 

/*reviewed by shai*/

static int CountHelper(void *data, void *param);
static void ConnectList2WithList1(dlist_iter_t where,dlist_iter_t from);
static void ConnectList1WithList2(dlist_iter_t to_prev, dlist_iter_t where);
static void ConnectList1ToItself(dlist_iter_t from_prev, dlist_iter_t to,dlist_iter_t to_prev);
static dlist_iter_t GetEndOfList(dlist_iter_t iter);

#define FAILURE (-1)
#define SUCCESS (0)

struct dlist_node
{
	void * data;
	dlist_iter_t next;
	dlist_iter_t prev;
};

struct dlist
{
	dlist_iter_t head;
	dlist_iter_t tail;
};

dlist_t *DListCreate(void)
{
	
	dlist_iter_t dummy_start = NULL;
	dlist_iter_t dummy_end = NULL;
		
	dlist_t * dlist = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == dlist)
    {
        return NULL;
    }

	dummy_start = malloc(sizeof(struct dlist_node));
	if (NULL == dummy_start)
    {
        free(dlist);
        dlist = NULL;
        return NULL;
    }
	
	dummy_end = malloc(sizeof(struct dlist_node));
	if (NULL == dummy_end)
    {
    	free(dummy_start);
        dummy_start = NULL;
        free(dlist);
        dlist = NULL;
        return NULL;
    }
    
	dummy_start->data = NULL;
	dummy_start->next = dummy_end;
	dummy_start->prev = NULL; 

	dlist->head = dummy_start;
		
	dummy_end->data = NULL;
	dummy_end->next = NULL;
	dummy_end->prev = dummy_start;
	dlist->tail = dummy_end;
	
	return dlist;
}

int DListIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{

	assert(NULL != iter1);
	
	assert(NULL != iter2);

	return iter1 == iter2;
}

void *DListGetData(dlist_iter_t iter)
{	
	assert(NULL != iter);

	return iter->data;
}

int DListIsEmpty(const dlist_t *dll)
{
	
	return dll->head->next == dll->tail;
}

dlist_iter_t DListPrev(dlist_iter_t iter)
{
	
	assert(NULL != iter);

	return iter->prev;
}

dlist_iter_t DListBegin(const dlist_t *dll)
{
	assert(NULL != dll);
	
	return dll->head->next;
}


dlist_iter_t DListInsert(dlist_iter_t iter, void *data)
{

	dlist_iter_t new_node = malloc(sizeof(struct dlist_node));
	if( NULL == new_node)
	{
		 return GetEndOfList(iter);
	}
	
	new_node->data = data;
	new_node->prev = iter->prev;
	new_node->next = iter;
	
	iter->prev->next = new_node;
	iter->prev = new_node;

	return new_node;

}

dlist_iter_t DListEnd(const dlist_t *dll)
{
	
	assert(NULL != dll);

	return dll->tail;
}

void DListDestroy(dlist_t *dll)
{
	
	dlist_iter_t curr = dll->head;
	dlist_iter_t next = NULL;
	
	assert(NULL != dll);
	
	while( curr != NULL)
	{
		next = curr ->next;
		free(curr);
		curr = next;
	}

	free(dll);
	dll = NULL;
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
	assert(NULL != iter);

	return iter->next;
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param)
{
	
	dlist_iter_t iterator = from;
	int error_code = 0;
	
	assert(NULL != from);
	assert(NULL != to);		
	
	while(!DListIsEqual(iterator,to) && (SUCCESS == error_code))
	{
		error_code = action_func(iterator->data, param);
		iterator = iterator->next;
	}
	
	return error_code;
}

static int CountHelper(void *data, void *param)
{

	++(*(size_t *)param);
	
	(void)data;
	
	return SUCCESS;
}

size_t DListSize(const dlist_t *dll)
{
	
	size_t count = 0;
	
	assert(NULL != dll);
	
	DListForEach(DListBegin(dll), DListEnd(dll),CountHelper,&count);
	
	return count;
}

dlist_iter_t DListRemove(dlist_iter_t iter)
{
		 
	iter->next->prev = iter->prev;
	iter->prev->next = iter->next;
	
	assert(NULL != iter);

	iter->next = NULL;
	iter->prev = NULL;
	
	free(iter);
	 
	return iter;
}

void *DListPopFront(dlist_t *dll)
{	

	void * data = DListGetData(DListBegin(dll));
	
	assert(!DListIsEmpty(dll));
	
	DListRemove(DListBegin(dll));	
	 
	 return data;
}


void *DListPopBack(dlist_t *dll)
{

	void * data = DListGetData(DListPrev(dll -> tail));
	
	dlist_iter_t prev = DListPrev(dll -> tail);
	
	assert(!DListIsEmpty(dll));
	
	DListRemove(prev);	
	
	return data;

}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *param)
{

	dlist_iter_t iterator = from;
	
	assert(NULL != from);
	assert(NULL != to);
	
	while(!DListIsEqual(iterator,to) && !is_match(iterator->data,param))
	{
		iterator = iterator->next;
	}
	
	return iterator;
}


dlist_iter_t DListPushFront(dlist_t *dll, void *data)
{

	assert(NULL != dll);

	return DListInsert(DListBegin(dll), data);
}

dlist_iter_t DListPushBack(dlist_t *dll, void *data)
{
	assert(NULL != dll);
	
    return DListInsert(DListEnd(dll), data);
}


int DListMultiFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *param, dlist_t *result_list)
{

	dlist_iter_t curr = from;	
	
	assert(NULL != from);
	assert(NULL != to);
	
	while(!DListIsEqual(curr,to))
	{
		if(is_match(DListGetData(curr),param))
		{
			if (NULL == DListPushFront(result_list, param))
			{
				return FAILURE;
			}
		}
		
		curr = curr->next;
	}
	
	return SUCCESS;
}


void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{

	dlist_iter_t from_prev = DListPrev(from);
	dlist_iter_t to_prev = DListPrev(to);
	
	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);

	ConnectList2WithList1(where,from);
	
	ConnectList1WithList2(to_prev,where);
	
	ConnectList1ToItself(from_prev, to,to_prev);	
}

static void ConnectList2WithList1(dlist_iter_t where,dlist_iter_t from )
{
	where->prev->next = from;
	from->prev = where->prev;
}

static void ConnectList1WithList2(dlist_iter_t to_prev, dlist_iter_t where)
{
	to_prev->next = where;
	where->prev = to_prev;
}

static void ConnectList1ToItself(dlist_iter_t from_prev, dlist_iter_t to, dlist_iter_t to_prev)
{
	from_prev->next = to;
	to->prev = from_prev;
}


static dlist_iter_t GetEndOfList(dlist_iter_t iter)
{
    assert(NULL != iter);

    while(NULL != iter)
    {
        iter = iter->next;
    }

    return iter;
}


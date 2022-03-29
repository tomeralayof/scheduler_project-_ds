#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "../include/pq.h"

struct pqueue
{
	sort_list_t *pq_list;
};

pq_t *PQCreate(cmp_func_t cmp_func)
{
	
	pq_t *priority_queue = (pq_t *)malloc(sizeof(pq_t));
	if(NULL == priority_queue)
	{
		return NULL;
	}

	assert(NULL != cmp_func);
	
	priority_queue-> pq_list = SortListCreate(cmp_func);
	if(NULL == priority_queue-> pq_list )
	{
		free(priority_queue);
		priority_queue = NULL;
		return NULL;
	}
	
	return priority_queue;
}

void PQDestroy(pq_t *pq)
{
	
	assert(NULL != pq);
	
	SortListDestroy(pq->pq_list);
	
	free(pq);
	
	pq = NULL;	
}

int PQIsEmpty(const pq_t *pq)
{	
	assert(NULL != pq);

	return SortListIsEmpty(pq->pq_list);
}

size_t PQSize(const pq_t *pq)
{

	assert(NULL != pq);
	
	return SortListSize(pq -> pq_list);
}


/*0 success 1 failure*/
int PQEnqueue(pq_t *pq, void *data)
{
	
	assert(NULL != pq);
	
	return SortListIterIsEqual(SortListInsert(pq->pq_list, data), SortListEnd(pq->pq_list));	
}

void *PQPeek(const pq_t *pq)
{

	assert(NULL != pq);
	
	return SortListGetData(SortListBegin(pq->pq_list));
}

void PQClear(pq_t *pq)
{
	
	assert(NULL != pq);

	while(!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void *PQDequeue(pq_t *pq)
{

	assert(NULL != pq);

	return SortListPopFront(pq->pq_list); 

}

void *PQErase(pq_t *pq, match_func_t match_func, void *param)
{

	void * data = NULL;	
	
	sort_list_iter_t where;
	
	where = SortListFindIf(SortListBegin(pq->pq_list),SortListEnd(pq->pq_list), match_func ,param);
	
	if(!(SortListIterIsEqual(where,SortListEnd(pq->pq_list))))
	{
		data = SortListGetData(where);
		SortListRemove(where);	
	}
	
	return data;
}
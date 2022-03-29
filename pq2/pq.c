#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "../include/pq2.h"

static int MatchFunc(const void *element, const void *param);

struct pqueue
{
	heap_t *pq_list;
};

pq_t *PQCreate(pq_cmp_func_t cmp_func)
{
	pq_t *priority_queue =NULL;
	
	assert(NULL != cmp_func);

 	priority_queue = (pq_t *)malloc(sizeof(pq_t));
	if(NULL == priority_queue)
	{
		return NULL;
	}

	priority_queue-> pq_list = HeapCreate(cmp_func);
	if(NULL == priority_queue-> pq_list)
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
	
	HeapDestroy(pq->pq_list);
	pq->pq_list = NULL;
	
	free(pq);
	pq = NULL;	
}

int PQIsEmpty(const pq_t *pq)
{	
	assert(NULL != pq);

	return HeapIsEmpty(pq->pq_list);
}

size_t PQSize(const pq_t *pq)
{

	assert(NULL != pq);
	
	return HeapSize(pq -> pq_list);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);

	return HeapPush(pq->pq_list,data);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPeek(pq->pq_list);
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

	return HeapRemove(pq->pq_list,MatchFunc,HeapPeek(pq->pq_list));
}

void *PQErase(pq_t *pq, heap_is_match_func_t match_func, void *param)
{
	return HeapRemove(pq->pq_list,match_func,param);
}

static int MatchFunc(const void *element, const void *param)
{
	return element == param;
}
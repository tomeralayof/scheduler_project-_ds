#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "../include/queue.h"
/*#include "sll.h"*/

/*reviewed by shai*/

struct queue
{
	slist_t * queue_list;
};

queue_t *QueueCreate()
{
	queue_t * queue = (queue_t *)malloc(sizeof(queue_t));	
	if (NULL == queue)
	{
	  	return NULL;
	}
	
	queue -> queue_list = SListCreate();
	if(NULL == queue->queue_list)
	{
		free(queue);
		queue = NULL;
	}
	
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);	
	
	SListDestroy(queue -> queue_list);
	free(queue);
	queue = NULL;
}

size_t QueueSize(const queue_t *queue)
{
	assert(NULL != queue);	
	
	return SListCount(queue -> queue_list);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);	
	
	return SListIsEmpty (queue -> queue_list);
}


int QueueEnqueue(queue_t *queue, void *data)
{
	slist_iter_t insert;

	assert(NULL != queue);
	assert(NULL != data);

	insert = SListEnd(queue->queue_list);
	insert = SListInsertBefore(insert, data);

	return SListIsEqual(insert, SListEnd(queue->queue_list));
}

void QueueDequeue(queue_t *queue)
{	
	assert(NULL != queue);	

	SListRemove(SListBegin(queue -> queue_list));
}


void *QueuePeek(const queue_t *queue)
{
	
	assert(NULL != queue);	
	
	return SListGetData(SListBegin(queue -> queue_list));
}

void QueueAppend(queue_t *dest, queue_t *src)
{

	assert(NULL != dest);	
	assert(NULL != src);	
	
	SListAppend(dest -> queue_list , src -> queue_list);
}





#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "../include/sll.h"

static int CountingFunc(void *data, void *param);

#define SUCCESS (0)

struct slist_node
{
	void *data;
	slist_iter_t next;
};

struct slist
{
	slist_iter_t head;
	slist_iter_t end;
};

slist_t * SListCreate(void)
{

	slist_iter_t dummy = NULL;
	
	slist_t *slist = (slist_t *)malloc(sizeof(slist_t));	
	if (NULL == slist)
	{
		return NULL;
	}
		
	dummy = malloc(sizeof(struct slist_node));
	if (NULL == dummy)
	{
		return NULL;
	}
		
	dummy -> data = slist;
	dummy -> next = NULL;	
	 
	slist -> head = dummy;
    slist -> end = dummy; 

	return slist;
}

int SListIsEmpty(const slist_t *slist)
{	 

	assert(NULL != slist);
	
	return slist -> head -> next ==  NULL;
}


void SListSetData(slist_iter_t iterator, void *data)
{
	iterator -> data = data;
}


slist_iter_t SListNext(const slist_iter_t iterator)
{
	return iterator -> next;
}

void *SListGetData(const slist_iter_t iterator)
{
	return (void *)iterator -> data;
}


slist_iter_t SListInsertAfter(slist_iter_t where, void *data)
{

	slist_iter_t new_node = malloc(sizeof(struct slist_node));
	if(NULL == new_node)
	{
		new_node = where;
		while(NULL != new_node->next)
		{
			new_node = new_node->next;
		}

		return new_node;
	}
		
	new_node -> data = data;	
	new_node -> next = where -> next;
	where -> next = new_node;
	
	return new_node;
	
}

slist_iter_t SListInsertBefore( slist_iter_t where,  void *data)
{

	slist_iter_t new_node = NULL;
		
	new_node = malloc(sizeof(struct slist_node));
	if(NULL == new_node)
	{
		new_node = where;
		while(NULL != new_node->next)
		{
			new_node = new_node->next;
		}

		return new_node;
	}
		
	if (NULL == where -> next)
	{	
		((slist_t *)(where -> data)) -> end = new_node;			
	}
		
	new_node -> data = where -> data;
	new_node -> next = where -> next;
	where -> data = data;	
		
	where -> next = new_node;
		
	return where;
}

slist_iter_t SListRemove(slist_iter_t iterator)
{
	
	slist_iter_t new_node;
	
	assert(iterator != NULL);	
	
	new_node = iterator -> next;
	
	iterator -> data = iterator -> next -> data;
	iterator -> next = iterator -> next -> next;
	
	free(new_node);
	
	return iterator;
}

int SListIsEqual(const slist_iter_t iterator1, const slist_iter_t iterator2)
{
	return iterator1 == iterator2;
}


int SListForEach(const slist_iter_t from, const slist_iter_t to, action_func_t action_func, void *param)
{

  	slist_iter_t temp = from;
  	int result = 0;
  	
  	assert(from != NULL);
	assert(to != NULL);
  
	while(!SListIsEqual(temp, to -> next))
	{
	
	 	result = action_func((void *)temp -> data, param);
	 	
	 	if(0 == result)
	 	{
	 		return result;
	 	}
	 	
	 	temp = SListNext(temp);
	 	
	}
	
	return result;
	
}

slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to, match_func_t is_match, void *param)
{

	slist_iter_t temp = from;
	
	assert(from != NULL);
	assert(to != NULL);
	
	while(!SListIsEqual(temp, to -> next))
	{
		if (is_match((void *)temp -> data , param))
		{
			return temp;
		}
		
		temp = SListNext(temp);
	}
	
	return NULL;
}

size_t SListCount( slist_t *slist)
{	
	size_t counter = 0;

	assert(NULL != slist);

	SListForEach(slist->head, slist->end, CountingFunc, &counter);

    return counter;
}

static int CountingFunc(void *data, void *param)
{	
	assert(NULL != param);

	++(*(size_t *)param);

	(void)data;
	return SUCCESS;
}

void SListDestroy(slist_t *slist)
{
		
	slist_iter_t temp = slist -> head;
	
	slist_iter_t temp2 = NULL;
	
	assert(slist != NULL);
	
	while(temp != NULL)
	{
		temp2 = temp -> next;
		free(temp);
		temp = temp2;
	}
	
	free(slist);
	slist = NULL;
}


slist_iter_t SListEnd( slist_t *slist)
{
	assert(slist != NULL);

	return (slist_iter_t)slist -> end;
}

slist_iter_t SListBegin(slist_t *slist)
{	
	
	assert(slist != NULL);

	return (slist_iter_t)slist -> head;
}


void SListAppend(slist_t *dest, slist_t *src)
{

	assert(NULL!= dest);
	assert(NULL!= src);

	dest -> end -> data = src -> head -> data;
	dest -> end -> next = src -> head -> next;
	dest -> end = src -> end;
	dest -> end -> data = dest;
	
	src -> head -> data = src;
	src -> head -> next = NULL;	
	src -> end = src -> head;
			
}











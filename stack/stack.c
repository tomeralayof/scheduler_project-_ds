#include <stdlib.h> /* size_t, malloc(), free() */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy() */
#include "../include/stack.h"


#define AFTER_LAST (1)

struct stack
{
    void *head;
    void *iter;
    void *tail;
    size_t elem_size;
};


stack_t *StackCreate(size_t num_of_elements, size_t element_size)
{
    stack_t *sptr = malloc(sizeof(stack_t) + (num_of_elements * element_size));
    if (NULL == sptr)
    {
        return NULL;
    }

    sptr->head = (char *)sptr + sizeof(stack_t);
    sptr->iter = sptr->head;
    sptr->tail = ((char *)sptr->head +
        (num_of_elements + AFTER_LAST) * element_size);
    sptr->elem_size = element_size;

    return sptr;
}

void StackDestroy(stack_t *sptr)
{
    assert(NULL != sptr);

    sptr->head = NULL;
    sptr->iter = NULL;
    sptr->tail = NULL;
    sptr->elem_size = 0;

    free(sptr);
    sptr = NULL;
}


void StackPush(stack_t *sptr, const void *element)
{
    assert(NULL != sptr);
    assert(sptr->tail > sptr->iter);

    memcpy(sptr->iter, element, sptr->elem_size);
    *(char **)&sptr->iter += sptr->elem_size;
}

void *StackPeek(const stack_t *sptr)
{
    assert(NULL != sptr);
    assert(sptr->head < sptr->iter);

    return ((char *)sptr->iter - sptr->elem_size);
}

void StackPop(stack_t *sptr)
{
    assert(NULL != sptr);
    assert(sptr->head < sptr->iter);

    *(char **)&sptr->iter -= sptr->elem_size;
}


int StackIsEmpty(const stack_t *sptr)
{
    assert(NULL != sptr);

    return (sptr->iter == sptr->head);
}

size_t StackSize(const stack_t *sptr)
{
    assert(NULL != sptr);

    return ((size_t)sptr->iter - (size_t)sptr->head)/(sptr->elem_size);
}

size_t StackCapacity(const stack_t *sptr)
{
    assert(NULL != sptr);

    return ((size_t)sptr->tail - (size_t)sptr->head)/(sptr->elem_size);
}



/*
#include <string.h>
#include <assert.h>


#include "../include/stack.h"

#define EMPTY_STACK 0

struct stack
{
	size_t element_size; 
	size_t curr_num_of_stored_elements; 
	size_t num_of_elements; 
	void ** arr;
};


stack_t *StackCreate(size_t num_of_elements, size_t element_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	
	if(NULL == stack)
	{
		return NULL;
	}
	stack -> element_size = element_size;	
	stack -> num_of_elements = num_of_elements;	
	stack -> curr_num_of_stored_elements = EMPTY_STACK;	
    stack -> arr = malloc(num_of_elements * element_size);    
    if(NULL == stack -> arr)
	{
		return NULL;
	}
   
	return stack;	
}

int StackIsEmpty(const stack_t *sptr)
{
	return sptr -> curr_num_of_stored_elements == EMPTY_STACK;
}

void StackPush(stack_t *sptr, const void *element)
{
	memcpy(sptr -> arr + sptr -> curr_num_of_stored_elements, element, sptr -> element_size);
	++(sptr -> curr_num_of_stored_elements);
}

size_t StackSize(const stack_t *sptr)
{
	return sptr -> curr_num_of_stored_elements;
}


size_t StackCapacity(const stack_t *sptr)
{	
	return sptr -> num_of_elements;
}

void StackPop(stack_t *sptr)
{
	--(sptr -> curr_num_of_stored_elements);
}

void *StackPeek(const stack_t *sptr)
{
	return  sptr -> arr + sptr -> curr_num_of_stored_elements - 1;
}

void StackDestroy(stack_t *sptr)
{
	free(sptr -> arr);
	sptr -> arr = NULL;
	free(sptr);
	sptr = NULL;
}
*/






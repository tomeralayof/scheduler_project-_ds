/******************************************************************************
 ******************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          12/01/21                                                ***
 *** Reviewer:     David 			                                     	***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for heap data structure.                                ***
 ******************************************************************************
 \*****************************************************************************/

#include <assert.h> /*assert()*/
#include <stdlib.h> /*malloc ??*/
#include <string.h> /*memcpy()*/

#ifdef DEBUG
	#include <stdio.h> /*printf()*/
#endif

#include "../include/heap.h"
#include "../include/vector.h"

#define INITIAL_CAP (10)
#define ROOT_IDX (0)

static void HeapifyUp(heap_t *heap,size_t i);
static void HeapifyDown(heap_t *heap,size_t i);
static void SwapPtr(void **x,void **y);
static int IsStop(heap_t * heap,void * current,void * right_child,void * left_child);
static void CheckLeftChild(size_t i,heap_t *heap,size_t size);
static void * RemoveNode(heap_t *heap,size_t i);
static int HasTwoChilds(size_t i,size_t size);
static void SwapAndPop(heap_t *heap,size_t idx1,size_t idx2, size_t idx3);

enum
{
	FAILURE = -1,
	SUCCESS = 0
};

enum
{
	FALSE,
	TRUE
};

struct heap
{
    heap_cmp_func_t cmp_func;
    vector_t *vec;
};

heap_t *HeapCreate(heap_cmp_func_t comp_func)
{
	heap_t *heap = NULL;
	
	assert(NULL != comp_func);

	heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		return NULL;
	}

	heap->cmp_func = comp_func;
	heap->vec = VectorCreate(sizeof(void *), INITIAL_CAP);
	if (NULL == heap->vec)
	{
		free(heap);
		heap = NULL;
	}

	return heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);

	VectorDestroy(heap->vec);
	heap->vec = NULL;

	free(heap);
	heap = NULL;
}

int HeapIsEmpty(const heap_t *heap)
{	
	assert(NULL != heap);

	return 0 == HeapSize(heap);
}


size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);

	return VectorSize(heap->vec);
}

int HeapPush(heap_t *heap, void *data)
{
	assert(NULL != heap);
	assert(NULL != data);

	if(SUCCESS != VectorPushBack(heap->vec,&data))
	{
		return FAILURE;
	}

	HeapifyUp(heap,HeapSize(heap) -1);

	return SUCCESS;
}

void *HeapPeek(const heap_t *heap)
{
	assert(NULL != heap);

	return *(void **)VectorGetAccessToElement(heap->vec,ROOT_IDX);
}

void HeapPop(heap_t *heap)
{
	assert(NULL != heap);

	SwapAndPop(heap,HeapSize(heap)-1,0,0);
}

void *HeapRemove(heap_t *heap, heap_is_match_func_t match_func, void *param)
{	
	int is_match = FALSE;
	size_t size = HeapSize(heap);
	size_t i = 0;

	assert(NULL != match_func);
	assert(NULL != param);

	for (i = 0; i < size && !is_match; i++)
	{
		is_match = match_func(*(void **)VectorGetAccessToElement(heap->vec,i),param);
	}

	return !is_match ? NULL : RemoveNode(heap,i);
}

static void *RemoveNode(heap_t *heap,size_t i)
{
	void *data = *(void **)VectorGetAccessToElement(heap->vec,i-1);
	SwapAndPop(heap,i-1,HeapSize(heap)-1,i-1);
	HeapifyUp(heap,i-1);
	
	return data;
}

/*remove index 3.., put the macro*/
static void SwapAndPop(heap_t *heap,size_t idx1,size_t idx2, size_t idx3)
{
	void **swapper_1 = VectorGetAccessToElement(heap->vec,idx1);
	void **swapper_2 = VectorGetAccessToElement(heap->vec,idx2);

	SwapPtr(swapper_1,swapper_2);
	VectorPopBack(heap->vec);
	HeapifyDown(heap,idx3);
}

static void HeapifyDown(heap_t *heap,size_t i)
{
	size_t size = HeapSize(heap);

	while (HasTwoChilds(i,size))
	{
		void **left_child = VectorGetAccessToElement(heap->vec,2*i+1);
		void **right_child = VectorGetAccessToElement(heap->vec,2*i+2);
		void **current = VectorGetAccessToElement(heap->vec,i);
		int is_stop = IsStop(heap,*current,*right_child,*left_child);
		
		if (is_stop)
		{
			break;
		}
		if (heap->cmp_func(*left_child,*right_child) < 0)
		{
			SwapPtr(current,left_child);
			i = 2*i+1;
		}
		else if (heap->cmp_func(*left_child,*right_child) > 0)
		{
			SwapPtr(current,right_child);
			i = 2*i+2;
		}
	}

	CheckLeftChild(i,heap,size);
}

static int HasTwoChilds(size_t i,size_t size)
{
	return 2*i+2 < size;
}

static void CheckLeftChild(size_t i,heap_t *heap,size_t size)
{
	if (2*i + 1 < size)
	{
		void **left_child = VectorGetAccessToElement(heap->vec,2*i+1);
		void **current = VectorGetAccessToElement(heap->vec,i);
		if (heap->cmp_func(*current,*left_child) > 0)
		{
			SwapPtr(current,left_child);
			i = 2*i+1;
		}
	}
}

static int IsStop(heap_t * heap,void * current,void * right_child,void * left_child)
{
	return (heap->cmp_func(current,left_child) < 0 && heap->cmp_func(current,right_child) < 0);
}

static void HeapifyUp(heap_t *heap,size_t i)
{
	int compare_factor = 0;
	void **parent = VectorGetAccessToElement(heap->vec,(i - 1) / 2);
	void **child = VectorGetAccessToElement(heap->vec,i);

	if(0 == i)
	{
		return;
	}
	compare_factor = heap->cmp_func(*parent,*child);
	if(compare_factor < 0)
	{
		return;
	}

	SwapPtr(parent,child);
	HeapifyUp(heap,(i - 1) / 2);
}

static void SwapPtr(void **x,void **y)
{
	void *temp = *x;
	*x = *y;
	*y = temp;
}

#ifdef DEBUG
void PrintVector(heap_t *heap)
{
	size_t size = HeapSize(heap);
	size_t i = 0;

	printf("{ ");

	for (i = 0; i < size; i++)
	{	
		printf("%d, ",**(int **)VectorGetAccessToElement(heap->vec,i));
	}

	printf("} ");
	printf("\n");
}
#endif
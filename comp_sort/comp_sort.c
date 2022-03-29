/******************************************************************************
 ******************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          12/01/21                                                ***
 *** Reviewer:     Shoshana Huri                                        	***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for comparasion sort .                                  ***
 ******************************************************************************
 \*****************************************************************************/

#include <assert.h> /*assert()*/
#include <stdlib.h> /*malloc()*/
#include <string.h> /*memcpy()*/
#include <stdio.h> /*printf()*/

#include "../include/comp_sort.h"

/*recursive binary search*/
static int RecSearch(int left, int right, int *arr,int num);

/*merge sort*/
static void SortForMerge(int *left,int *right,int *new_arr,size_t size);
static void SortRest(int *left,int *end_left,int *right,int *end_right,int i,int *new_arr);
static void RecMergeSort(int *arr_to_sort, size_t size,int *new_arr);

/*quick sort*/
static char *Partition(char *low,char *high,compar_func_t cmp_func,size_t size);
static void RecQuickSort(char *low,char *high,compar_func_t compar_func_t,size_t size);
static void GenericSwap(void *x,void *y,size_t size);

enum sort
{
	FALSE = 0,
	TRUE = 1
};

enum
{
	FAILURE = -1,
	SUCCESS = 0
	
};

void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	int is_sorted = FALSE;
	
	assert(NULL != arr);
	
	for (i = 0; i < size && (FALSE == is_sorted); ++i)
	{
		is_sorted = TRUE;	
		for (j = i + 1; j < size; ++j)
		{
			if(arr[i] > arr[j])
			{		
				GenericSwap(&arr[i], &arr[j],sizeof(int));
				is_sorted = FALSE;
			}
		}		
	}		
}

void SelectionSort(int *arr, size_t arr_size)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	
	for (i = 0; i < arr_size; ++i)
	{
		int min = i;
		
		for (j = i + 1; j < arr_size; ++j)
		{
			if(arr[min] > arr[j])
			{
				min = j;	
			}	
		}
		GenericSwap(&arr[i], &arr[min],sizeof(int));
	}
}

void InsertionSort(int *arr, size_t arr_size)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for (i = 1; i < arr_size ; ++ i)
	{
		int insert = arr[i];
		int j = i - 1;
			
		while (j >= 0 && insert < arr[j])
		{
			arr[j + 1] = arr[j];
			--j; 
		}		
		
		arr[j + 1] = insert;
	}
} 

int BinarySearchIter(int *arr,size_t size,int num)
{
	int left = 0;
	int right = size -1;
	int middle = 0;

	assert(NULL != arr);
	assert(0 < size);

	while (left <= right)
	{
		middle = (left + right) / 2;

		if(arr[middle] > num)
		{
			right = middle - 1;
		}
		else if(arr[middle] < num)
		{
			left = middle + 1;
		}
		else
		{
			return middle;
		}
	}

	return FAILURE;
}

int BinarySearchRec(int *arr,size_t size,int num)
{
	int left = 0;
	int right = size - 1;

	assert(NULL != arr);
	assert(0 < size);

	return RecSearch(left,right,arr,num);
}

int MergeSort(int *arr_to_sort,size_t size)
{
	int *new_arr = NULL;

	assert(NULL != arr_to_sort);
	assert(0 < size);

	new_arr = malloc(sizeof(int) * size);
	if (new_arr == NULL)
	{
		return FAILURE;
	}

	RecMergeSort(arr_to_sort,size,new_arr);

	free(new_arr);
	new_arr = NULL;

	return SUCCESS;
}

void QSort(void *base, size_t nmemb, size_t size, compar_func_t cmp_func)
{	
	char *low = NULL; 
	char *high = NULL; 

	assert(NULL != base);
	assert(NULL != cmp_func);
	assert(0 < size);
	assert(0 < nmemb);

	low = (char *)base;
	high = (char *)base + ((nmemb - 1) * size);

	RecQuickSort(low,high,cmp_func,size);
}

static void RecQuickSort(char *low,char *high,compar_func_t cmp_func,size_t size)
{
	char *pivot = NULL;

	if(low >=high)
	{
		return;
	}

	pivot = Partition(low,high,cmp_func,size);
	RecQuickSort(low,pivot - size,cmp_func,size);
	RecQuickSort(pivot + size,high,cmp_func,size);
}

static char *Partition(char *low,char *high,compar_func_t cmp_func,size_t size)
{
	char *pivot = high;
	char *runner = low;
	char *swapper = low - size;

	for (runner = low; runner < high; runner += size)
	{
		if (cmp_func(pivot,runner) > 0)
		{
			GenericSwap(swapper+=size,runner,size);
		}
	}

	GenericSwap(swapper + size,runner,size);

	return swapper + size;
}

static void GenericSwap(void *x,void *y,size_t size)
{	
	while (size > sizeof(size_t))
	{
		size_t temp = *(size_t *)x;
		*(size_t *)x = *(size_t *)y;
		*(size_t *)y = temp;
		++*(size_t **)&x;
		++*(size_t **)&y;
		size -= sizeof(size_t);
	}

	while (size > 0)
	{
		char temp = *(char *)x;
		*(char *)x = *(char *)y;
		*(char *)y = temp;
		++*(char **)&x;
		++*(char **)&y;
		--size;
	}	
}

static void RecMergeSort(int *arr_to_sort ,size_t size,int *new_arr)
{
	if(size == 1)
	{
		return;
	}

	RecMergeSort(arr_to_sort,size/2,new_arr);
 	RecMergeSort(arr_to_sort + size/2,size /2,new_arr);

	SortForMerge(arr_to_sort,arr_to_sort + size/2,new_arr,size);
	memcpy(arr_to_sort,new_arr,sizeof(int) * size);
}

static void SortForMerge(int *left,int *right,int *new_arr,size_t size)
{
	int i = 0;

	int *end_right = right + size / 2;
	int *end_left = left + size / 2;
	
	while (left < end_left && right < end_right)
	{
		if (*left < *right)
		{

			new_arr[i] = *left;
			++left;
		}
		else
		{
			new_arr[i] = *right;
			++right;
		}
		++i;
	}

	SortRest(left,end_left,right,end_right,i,new_arr);
}

static void SortRest(int *left,int *end_left,int *right,int *end_right,int i,int *new_arr)
{
	while (left < end_left)
	{
		new_arr[i] = *left;
		++i;
		++left;
	}
	
	while (right < end_right)
	{
		new_arr[i] = *right;
		++i;
		++right;
	}
}

static int RecSearch(int left, int right, int *arr,int num)
{
	int middle = (right + left) / 2;

	if(left > right)
	{
		return FAILURE;
	}

	if(arr[middle] == num)
	{
		return middle;
	}

	if(arr[middle] > num)
	{
		return RecSearch(left,middle - 1,arr,num);
	}

	return RecSearch(middle + 1,right,arr,num);
}
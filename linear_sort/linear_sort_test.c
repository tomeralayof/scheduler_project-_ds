/*
 * written by: Tomer Alayof
 * reviewed by: Shaked
 * date: 13/1/22
 * linear_sort 
*/

#include <stdio.h> /*printf()*/
#include <stdlib.h> /*malloc()*/

#include "../include/linear_sort.h"

void TestCountSort();
void TestRadixSort();

static void PrintArr(int *arr, size_t size);
static void CreateArr(int *arr,size_t size);

int main()
{
	/*TestCountSort();*/

	TestRadixSort();

	return 0;
}


void TestRadixSort()
{	

	int digit_cunk = 3;
	size_t size = 5000;
	
	int *arr = (int *)malloc(sizeof(int) * size);
	
	CreateArr(arr,size);
	
	RadixSort(arr,size,digit_cunk);
	
	PrintArr(arr,size);
	
	free(arr);
}


void TestCountSort()
{
	size_t size = 5000;
	
	int *arr = (int *)malloc(sizeof(int) * size);
	
	CreateArr(arr,size);
	
	CountSort(arr,size);
	
	PrintArr(arr,size);
	
	free(arr);
}

static void CreateArr(int *arr,size_t size)
{
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100;
	}
}

static void PrintArr(int *arr, size_t size)
{

	size_t i = 0;
	
	for(i =0; i < size; ++i)
	{
		printf("%d ",arr[i]);
	}
	
	printf("\n");
}













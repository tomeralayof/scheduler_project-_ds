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
 
#include <stdio.h> /*printf()*/
#include <stdlib.h> /*malloc() qsort()*/
#include <time.h> /* clock_t */
#include <assert.h>
#include <string.h>


#include "../include/comp_sort.h"

clock_t TestBubbleSort();
clock_t TestSelectionSort();
clock_t TestInsertionSort();
clock_t QuickSort();
clock_t QuickSortTomer();
void QsortTimeTomerInvestigation();

void TimeInvastigator();
void TestBinarySearchIter();
void TestBinarySearchRec();
void TestMergeSort();
void BinarySearchTestShai();
void TestQuickSort();
void TestBinaryIterr();

static void SetRandomArr(int *arr, size_t size);
static void PrintArr(int *arr, size_t size);
static int Compare(const void *a,const void *b);


void sortedArrayqSort();

int main()
{
	/*
	TimeInvastigator();
	TestBinarySearchIter();
	TestBinarySearchRec();
	TestMergeSort();
	TestQuickSort();
	BinarySearchTestShai();
	QsortTimeTomerInvestigation();
	*/

	sortedArrayqSort();




	return 0;
}

void sortedArrayqSort()
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
	int size = sizeof(arr) / sizeof(int);
	QSort(arr,size,sizeof(int),&Compare);
	PrintArr(arr,size);
}

void QsortTimeTomerInvestigation()
{
	time_t time_bubble = TestBubbleSort();
	time_t time_q_sort_tomer = QuickSortTomer();
	time_t time_q_sort_lib = QuickSort();
	printf("quick sort tomer time:  %ld\n",time_q_sort_tomer);
	printf("quick sort lib time:  %ld\n",time_q_sort_lib);
	printf("bubble sort time:  %ld\n",time_bubble);
}

clock_t QuickSortTomer()
{
	int *arr = (int *)malloc(sizeof(int) * 5000);
	size_t size = 5000;
	clock_t start = clock();
	clock_t end = 0;
	
	SetRandomArr(arr, size);
	QSort(arr,size,sizeof(int),&Compare);
	
	end = clock();
	
	free(arr);
	arr = NULL;
	
	return end - start;
}

void TimeInvastigator()
{
	time_t time_bubble = TestBubbleSort();
	time_t time_selection_sort = TestSelectionSort();
	time_t time_insertion_sort = TestInsertionSort();
	time_t time_q_sort = QuickSort();

	printf("bubble sort time: %ld\n",time_bubble);
	printf("selection sort time: %ld\n",time_selection_sort);
	printf("insertion sort time: %ld\n",time_insertion_sort);
	printf("quick sort time:  %ld\n",time_q_sort);
}




void TestBinaryIterr()
{
	int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
	int size = sizeof(arr) / sizeof(int);
	int num1 = 0;
	int num2 = 10;
	int num3 = -10;
	int num4 = 1;
	int num5 = 100000000;
	int num6 = 9;
	int num7 = 20000;
	int num8 = 1;
	int num9 = 2;

	assert(0 ==  BinarySearchIter(arr,size,num1));
	assert(10 ==  BinarySearchIter(arr,size,num2));
	assert(-1 ==  BinarySearchIter(arr,size,num3));
	assert(1 ==  BinarySearchIter(arr,size,num4));
	assert(-1 ==  BinarySearchIter(arr,size,num5));
	assert(9 ==  BinarySearchIter(arr,size,num6));
	assert(-1 ==  BinarySearchIter(arr,size,num7));
	assert(1 ==  BinarySearchIter(arr,size,num8));
	assert(0 ==  BinarySearchIter(arr,size,num1));
	assert(2 ==  BinarySearchIter(arr,size,num9));
}

void TestBinarySearchRec()
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int arr2[10] = {0};

	size_t size = sizeof(arr) / sizeof(int);
	int num = 1;
	size_t idx_result = 0;
	int i = 0;
	idx_result = BinarySearchRec(arr,size,num);

	printf("result index: %ld\n",idx_result);


    for (i = 0; i < 9; ++i)
    {
        arr2[i] = i;
    }

    for (i = 0; i < 9; ++i)
    {
      printf("%d ,",arr2[i]);
    }

	printf("%d\n",arr2[0]);

	idx_result =  BinarySearchRec(arr2,100,0);
	printf("%ld\n",idx_result);

}


void BinarySearchTestShai()
{
    int arr[100] = {0};
    int i = 0;
    int index = -1;

    for (i = 0; i < 100; ++i)
    {
        arr[i] = i;
    }

    index = BinarySearchRec(arr, 100, 8);
    assert(8 == arr[index]);

    index = BinarySearchRec(arr, 100, 0);
    assert(0 == arr[index]);
	
    index = BinarySearchRec(arr, 100, 99);
    assert(99 == arr[index]);
	
    assert((int)-1 == BinarySearchRec(arr, 100, 200));

    assert(-1 == BinarySearchRec(arr, 100, -1000));
	

    printf("if you see this messege, your binary search is PERFECT\n");
}

void TestMergeSort()
{
	int arr[] = {4,6,1,3,2,9,8,10};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	MergeSort(arr,size);

	for (i = 0; i < size; i++)
	{
		printf("%d , ",arr[i]);
	}
}

void TestBinarySearchIter()
{  
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	size_t size = sizeof(arr) / sizeof(int);
	int num =2;
	size_t idx_result = 0;

	idx_result = BinarySearchIter(arr,size,num);

	printf("result index: %ld\n",idx_result);
}





clock_t QuickSort()
{
	int *arr = (int *)malloc(sizeof(int) * 5000);
	size_t size = 5000;
	clock_t start = clock();
	clock_t end = 0;
	
	SetRandomArr(arr, size);
	qsort(arr,size,sizeof(int),&Compare);
	
	end = clock();
	
	free(arr);
	arr = NULL;
	
	return end - start;
}



clock_t TestBubbleSort()
{
	int *arr = (int *)malloc(sizeof(int) * 5000);
	size_t size = 5000;
	
	clock_t start = clock();
	clock_t end = 0;
	
	SetRandomArr(arr, size);
	
	BubbleSort(arr,size);
	
	end = clock();
	
	free(arr);
	arr = NULL;
	
	return end - start;
}

clock_t TestSelectionSort()
{
	int *arr = (int *)malloc(sizeof(int) * 5000);
	size_t size = 5000;
	
	clock_t start = clock();
	clock_t end = 0;
	
	SetRandomArr(arr, size);
	
	SelectionSort(arr,size);
	
		PrintArr(arr,size);
	
	end = clock();
	
	free(arr);
	arr = NULL;
	
	return end - start;
}

clock_t TestInsertionSort()
{
	int *arr = (int *)malloc(sizeof(int) * 5000);
	size_t size = 5000;
	
	clock_t start = clock();
	clock_t end = 0;
	
	SetRandomArr(arr, size);
	
	InsertionSort(arr,size);
	
	end = clock();
	
	free(arr);
	arr = NULL;
	
	return end - start;
}



static void SetRandomArr(int *arr, size_t size)
{
	size_t i = 0;
	
	for( i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100;
	}
}

static void PrintArr(int *arr, size_t size)
{
	size_t i = 0;

	for(i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}	
	printf("\n");
}


void TestQuickSort()
{
	int arr[] = {10,80,30,90,40,50,70};
	size_t size = sizeof(arr) / sizeof(int);

	QSort(arr,size,sizeof(int),&Compare);

	PrintArr(arr,size);
}

static int Compare(const void *a,const void *b)
{
	return *(int *)a - *(int *)b;
}

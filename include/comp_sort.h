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

#ifndef __COMP_SORT_H__
#define __COMP_SORT_H__

#include <stddef.h>

typedef int (*compar_func_t)(const void *data1, const void *data2);

/*complexity: time: O(n^2) space: O(1)*/
void BubbleSort(int *arr, size_t arr_size);

/*complexity: time: O(n^2) space: O(1)*/
void SelectionSort(int *arr, size_t arr_size);

/*complexity: time: O(n^2) space: O(1)*/
void InsertionSort(int *arr, size_t arr_size);

int BinarySearchIter(int *arr,size_t size,int num);

int BinarySearchRec(int *arr,size_t size,int num);

int MergeSort(int *arr_to_sort,size_t size);

void QSort(void *base, size_t nmemb, size_t size, compar_func_t cmp_func);


#endif /*__COMP_SORT_H__ */

/*
 * written by: Tomer Alayof
 * reviewed by: Shaked
 * date: 13/1/22
 * linear_sort 
*/

#ifndef __LINEAR_SORT_H__
#define __LINEAR_SORT_H__

#include <stddef.h>

/*
 *  DESCRIPTION:
 *	the function used for sorting an array of integers using counting 
 * 	sort. this way of sorting is consider to be quite fast and recommend 
 * 	for use in case lack of memory is not an issue. this way of sorting 
 * 	is not recommended for numbers with high value range , in that case use radix sort.  
 *
 *  Complexity: O(n) time, O(n+k) space.
 * 
 *  PARAMS: 
 *   arr1 - pointer to array of integers
 *	 arr_size - contain the number of elements in the array 
 *
 *  RETURN:
 *  void
*/
void CountSort(int *arr1, size_t arr_size);

/*
 *  DESCRIPTION:
 *	the function used for sorting an array of integers using counting 
 * 	sort. this way of sorting is consider to be quite fast and recommend 
 * 	for use in case lack of memory is not an issue. this way of sorting 
 * 	is recommended for numbers with high value range but is slower that counting sort
 * 	for low number range.
 *    
 *
 *  Complexity: O(n) time, O(n+k) space.
 * 
 *  PARAMS: 
 *   arr - pointer to array of integers
 *	 arr_size - contain the number of elements in the array 
 *	 digit_cunk - the number of digits to cheak on each itertion
 *   passing number lower than 1 is undefined behaviour
  
 *  RETURN:
 *  void
 */
void RadixSort(int *arr, size_t arr_size,int digit_cunk);


#endif /* __LINEAR_SORT_H__ */




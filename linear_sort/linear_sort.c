/*
 * written by: Tomer Alayof
 * reviewed by: Shaked
 * date: 13/1/22
 * linear_sort 
*/

#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/

#include "../include/linear_sort.h"

#define MAX(a,b) ((a)>(b)?(a):(b))

/*count sort static functions*/
/*find the max value in the given array*/
static size_t FindMx(int *arr, size_t size);

/*initialize lookup table*/
static void InitialLut(int *arr,int *lut,size_t size,size_t mx_val);

/*initialize target array for count sort*/
static void InitialTargetArray(int *arr2, int *arr1,int *lut, size_t arr_size);

/*radix static functions*/
/*count the number of digit inside a single num*/
static int ElemDigitNum(int num);

/*find the make digit inside the array*/
static int FindMxNumOfDigits(int mx_d,int *arr,size_t arr_size);

/*make count sort espacially for radix*/
static void CountRadixSort(int *arr,size_t arr_size,int devide_factor,int mod);

/*initial the second array regarding to source one*/
static void InitialTargetArrRadix(int *arr1,size_t arr_size,int *lut, int *arr2,int devide_factor, int mod);

/*initialize the histograma for radix */
static void InitialLutRadix(int *arr,int *lut,size_t size,size_t mx_val, int devide_factor,int mod);

/*reverse mod according to user request*/
static int ReverseMod(int mod, int digit_cunk);

void CountSort(int *arr1,size_t arr_size)
{
	size_t mx_val = 0;
	int *lut = NULL;
	
	int *arr2 = (int *)malloc(sizeof(int) * arr_size);
	if(NULL == arr2)
	{
		return;
	}
	
	assert(NULL != arr1);
	
	mx_val = FindMx(arr1,arr_size);
	
	lut = (int *)calloc(mx_val, sizeof(int));
	if(NULL == lut)
	{
		free(arr2);
		return;
	}
	
	InitialLut(arr1,lut,arr_size,mx_val);
	
	InitialTargetArray(arr2,arr1,lut,arr_size);
	
	memcpy(arr1,arr2,arr_size * sizeof(int));
	
	free(lut);
	free(arr2); 
}

void RadixSort(int *arr, size_t arr_size,int digit_cunk)
{
	int mx_d = 0;
	int devide_factor = 1;
	int mod = 10;
	
	assert(NULL != arr);
	assert(0 < digit_cunk);
	
	mod = ReverseMod(mod,digit_cunk);
	mx_d = FindMxNumOfDigits(mx_d,arr,arr_size);
		
	while(mx_d > 0)
	{
		CountRadixSort(arr,arr_size,devide_factor,mod);
		devide_factor*=mod;
		mx_d -= digit_cunk;
	}
}

/*statics for radix*/
static int FindMxNumOfDigits(int mx_d,int *arr,size_t arr_size)
{
	size_t i = 0;
	
	for(i = 0; i < arr_size; ++i)
	{
		mx_d = MAX(mx_d,ElemDigitNum(arr[i]));		
	}
	
	return mx_d;
}

static int ElemDigitNum(int num)
{
	int count = 0;
	
	while(num > 0)
	{
		num/=10;	
		++count;	
	}
	return count;
}

static int ReverseMod(int mod, int digit_cunk)
{
	int i = 0;
	
	for(i = 1; i < digit_cunk; ++i)
	{
		mod*=10;
	}

	return mod;
}

static void CountRadixSort(int *arr,size_t arr_size,int devide_factor,int mod)
{
	int *lut = NULL;

	int *arr2 = (int *)malloc(sizeof(int) * arr_size);
	if(NULL == arr)
	{
		return;
	}
	
	lut = (int *)calloc(mod, sizeof(int));
	if(NULL == lut)
	{
		free(arr2);
		return;
	}
	
	InitialLutRadix(arr,lut,arr_size,mod,devide_factor,mod);
	
	InitialTargetArrRadix(arr,arr_size,lut,arr2,devide_factor,mod);
	
	memcpy(arr,arr2,arr_size * sizeof(int));
	
	free(arr2);	
	free(lut);
}

static void InitialLutRadix(int *arr,int *lut,size_t size,size_t mx_val, int devide_factor,int mod)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		++lut[(arr[i] / devide_factor) % mod];
	}
	
	for(i = 1; i < mx_val; ++i)
	{
		lut[i] += lut[i -1];
	}
}

static void InitialTargetArrRadix(int *arr1,size_t arr_size,int *lut, int *arr2,int devide_factor, int mod)
{
	int i = 0;	
	
	for(i = (int)arr_size -1; i >= 0; --i)
	{
		arr2[lut[(arr1[i] / devide_factor) % mod ] -1] = arr1[i];
		--lut[(arr1[i] / devide_factor) % mod];
	}
}

/*statics for count sort*/
static size_t FindMx(int *arr, size_t size)
{
	size_t i = 0;
	
	int max = arr[0];
	
	for (i = 0; i < size; ++i)
	{
		max = MAX(max,arr[i]);
	}
		
	return max + 1;
}

static void InitialLut(int *arr,int *lut,size_t size,size_t mx_val)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		++lut[arr[i]];
	}
	
	for (i = 1; i < mx_val; ++i)
	{
		lut[i] += lut[i -1];
	}
}

static void InitialTargetArray(int *arr2, int *arr1,int *lut, size_t arr_size)
{
	int i = 0;	
	
	for(i = (int)arr_size -1; i >= 0; --i)
	{
		arr2[lut[arr1[i]] -1] = arr1[i];
		--lut[arr1[i]];
	}
}













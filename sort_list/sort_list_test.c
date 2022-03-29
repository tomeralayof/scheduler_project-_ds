#include <stdio.h>  /* printf() */
#include <assert.h>	/* assert() */

#include "../include/sort_list.h"

void test1();
void test2();
void Test1shai();
void Test2shai();
void Test3shai();
void Test4();

#define CASTING(type, var) (*(type *)&(var))

enum status
{
	SUCCESS,
	FAILURE
};

int IsEven(void *data, void *param)
{
	if (*CASTING(int *, data) % *CASTING(int *, param) == 0)
	{
		*CASTING(int *, data) += 1;
	}
	return 0;
}


int IntCmp(const void *val1, const void *val2)
{
	return *(int *)val1 - *(int *)val2;
}

int DoesIntMatch(const void *val1, void *val2)
{
	return *(int *)val1 == *(int *)val2;
}

int SortIntIncreasingOrder(const void *left, const void *right)
{
	if (NULL == left)
	{
		return *CASTING(int *, right);
	}
	if (NULL == right)
	{
		return *CASTING(int *, left);
	}
	return *CASTING(int *, left) - *CASTING(int *, right);
}

int IsBig(const void *data, void *param)
{
	return (*CASTING(int *, data) > *CASTING(int *, param)) ? *CASTING(int *, data) : 0;
}




static void PrintIntList(sort_list_t *list)
{
	sort_list_iter_t runner = SortListBegin(list);
	void *p = NULL;
	printf("list contain: ");
	while (!SortListIterIsEqual(runner,SortListEnd(list)))
	{
		p = SortListGetData(runner);
		printf("%d, ", *CASTING(int *, p));
		runner = SortListNext(runner);
	}
	printf("\n");
}





int main()
{

	
	/*Test2shai();
	Test4();
	*/
	 Test2shai();	
	
	

	return 0;
}


	
void test2()
{

	sort_list_t *list = NULL;
	
	sort_list_iter_t it1;
	sort_list_iter_t it2;
	
	int x1 = 32;
	int x2 = 368;
	int x3 = 12;
	int x4 = 9;
	
	size_t count = 0;

	list = SortListCreate(&IntCmp);
	assert(NULL != list);
	assert(SortListIsEmpty(list));
	
	
	assert(0 == SortListSize(list));
	it1 = SortListEnd(list);
	assert(NULL != it1.it);
	
	

	
	it1 = SortListInsert(list, &x1); 
	assert(x1 == *(int *)SortListGetData(it1));
	assert(!SortListIsEmpty(list));
	assert(SortListIterIsEqual(it1, SortListBegin(list)));
	
	
	it1 = SortListInsert(list, &x2); 
	assert(x2 == *(int *)SortListGetData(it1));
	assert(!SortListIterIsEqual(it1, SortListBegin(list)));
	assert(x1 == *(int *)SortListGetData(SortListBegin(list)));
	
	
	
	it2 = SortListInsert(list, &x3); 
	assert(x3 == *(int *)SortListGetData(it2));
	assert(x2 == *(int *)SortListGetData(it1));
	it1 = SortListBegin(list);
	assert(x3 == *(int *)SortListGetData(it1));
	it1 = SortListPrev(SortListEnd(list));
	assert(x2 == *(int *)SortListGetData(it1));
	
	
	SortListInsert(list, &x4); 
	assert(x2 == *(int *)SortListGetData(it1));
	it1 = SortListPrev(it1);
	assert(x1 == *(int *)SortListGetData(it1));
	it1 = SortListPrev(it1);
	assert(x3 == *(int *)SortListGetData(it1));
	
	
	it1 = SortListRemove(it1); 
	count = SortListSize(list);
	printf("count = %ld\n",count);
	
	assert(0 == SortListIsEmpty(list));
	
	

	
	SortListDestroy(list); list = NULL;

	printf("SUCCESS\n");
}






void test1()
{
	sort_list_t *list = NULL;
	sort_list_iter_t it1;
	sort_list_iter_t it2;
	int x1 = 32;
	int x2 = 368;
	int x3 = 12;
	int x4 = 9;
	
	size_t len = 0;
	
	list = SortListCreate(&IntCmp);
	assert(NULL != list);
	assert(SortListIsEmpty(list));
	assert(0 == SortListSize(list));
	it1 = SortListEnd(list);
	assert(NULL != it1.it);

	it1 = SortListInsert(list, &x1); 
	

	
	assert(x1 == *(int *)SortListGetData(it1));
	assert(!SortListIsEmpty(list));
	assert(SortListIterIsEqual(it1, SortListBegin(list)));
	
	it1 = SortListInsert(list, &x2); 

	
	
	assert(x2 == *(int *)SortListGetData(it1));
	assert(!SortListIterIsEqual(it1, SortListBegin(list)));
	assert(x1 == *(int *)SortListGetData(SortListBegin(list)));

	
	it2 = SortListInsert(list, &x3);
	
		
	assert(x3 == *(int *)SortListGetData(it2));
	assert(x2 == *(int *)SortListGetData(it1));
	it1 = SortListBegin(list);
	assert(x3 == *(int *)SortListGetData(it1));
	it1 = SortListPrev(SortListEnd(list));
	assert(x2 == *(int *)SortListGetData(it1));

	SortListInsert(list, &x4);  
		
	assert(x2 == *(int *)SortListGetData(it1));
	it1 = SortListPrev(it1);
	assert(x1 == *(int *)SortListGetData(it1));
	it1 = SortListPrev(it1);
	assert(x3 == *(int *)SortListGetData(it1));

	PrintIntList(list);
	len = SortListSize(list);
	printf("size = %ld\n",len);
	
	it1 = SortListRemove(it1);
	len = SortListSize(list);
	
	printf("size = %ld\n",len);
	
	
	
	
	SortListDestroy(list);

	printf("SUCCESS\n");
}






void Test1shai()
{
	sort_list_t *my_list = SortListCreate(&SortIntIncreasingOrder);
	int x1 = 7;
	int x2 = 3;
	int x3 = 12;
	int x4 = 1;
	int x5 = 5;
	int x6 = 13;
	sort_list_iter_t temp = {0};
	printf("--------------------Test 1-----------------\n");
	SortListInsert(my_list, &x1);
	SortListInsert(my_list, &x2);
	temp = SortListInsert(my_list, &x3);
	SortListInsert(my_list, &x4);
	SortListInsert(my_list, &x5);
	SortListInsert(my_list, &x6);
	printf("list after 6 (not sorted) inserts: \n");
	PrintIntList(my_list);
	SortListRemove(temp);
	printf("list after removing 12: \n");
	PrintIntList(my_list);
	SortListPopFront(my_list);
	SortListPopBack(my_list);
	printf("list after popfront and popback: \n");
	PrintIntList(my_list);
	SortListDestroy(my_list);
}



void Test2shai()
{
	sort_list_t *my_list = SortListCreate(&SortIntIncreasingOrder);
	sort_list_t *my_list2 = SortListCreate(&SortIntIncreasingOrder);
	int x1 = 7;
	int x2 = 3;
	int x3 = 12;
	int y4 = 0;
	int y5 = -2;
	int y6 = 20;
	printf("--------------------Test 2-----------------\n");
	SortListInsert(my_list, &x1);
	SortListInsert(my_list, &x2);
	SortListInsert(my_list, &x3);
	/*
	SortListInsert(my_list2, &y4);
	SortListInsert(my_list2, &y5);
	SortListInsert(my_list2, &y6);
	*/
		SortListInsert(my_list2, &y6);
	printf("list 1: \n");
	PrintIntList(my_list); 
	printf("list 2: \n");
	PrintIntList(my_list2);
	printf("merge list 1 and 2: \n");
	SortListMerge(my_list, my_list2);
	PrintIntList(my_list);
	printf("merge list size = %ld\n", SortListSize(my_list));
	SortListDestroy(my_list);
	SortListDestroy(my_list2);
}


void Test3shai()
{
	sort_list_t *my_list = SortListCreate(&SortIntIncreasingOrder);
	int x1 = 79;
	int x2 = 3;
	int x3 = 123;
	int x4 = -1;
	int x5 = 56;
	int x6 = -14;
	int x0 = 100;
	void *p = NULL;
	sort_list_iter_t temp = {0};
	printf("--------------------Test 3-----------------\n");
	SortListInsert(my_list, &x1);
	SortListInsert(my_list, &x2);
	SortListInsert(my_list, &x3);
	SortListInsert(my_list, &x4);
	SortListInsert(my_list, &x5);
	SortListInsert(my_list, &x6);
	printf("list after 6 inserts: \n");
	PrintIntList(my_list);
	temp = SortListFind(my_list, SortListBegin(my_list), SortListEnd(my_list), &x4);
	p = SortListGetData(temp);
	printf("search -1 in the list with find: \n");
	printf("%d\n", *CASTING(int *, p));
	temp = SortListFindIf(SortListBegin(my_list), SortListEnd(my_list), &IsBig, &x0);
	p = SortListGetData(temp);
	printf("search a number that greater than 100 in the list with findif: \n");
	printf("%d\n", *CASTING(int *, p));
	SortListDestroy(my_list);
}



void Test4()
{
	sort_list_t *my_list = SortListCreate(&SortIntIncreasingOrder);
	int x1 = 9;
	int x2 = 3;
	int x3 = 2;
	int x4 = 11;
	int x5 = 7;
	int x6 = 8;
	int even = 2;
	printf("--------------------Test 4-----------------\n");
	SortListInsert(my_list, &x1);
	SortListInsert(my_list, &x2);
	SortListInsert(my_list, &x3);
	SortListInsert(my_list, &x4);
	SortListInsert(my_list, &x5);
	SortListInsert(my_list, &x6);
	printf("list after 6 inserts: \n");
	PrintIntList(my_list);
	SortListForEach(SortListBegin(my_list), SortListEnd(my_list), &IsEven, &even);
	printf("using ForEach that increase 1 to all even numbers in the list: \n");
	PrintIntList(my_list);
	SortListDestroy(my_list);
}








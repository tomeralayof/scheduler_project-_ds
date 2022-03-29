#include <stdio.h>	/* printf() */

#include "../include/sll.h"

void test1();
void test2();

int DoesIntMatch(const void *element_1, void *element_2)
{
	return *(int *)element_1 == *(int *)element_2;
}



int main()
{


	/*test1();*/
	
	test2();



	

	return 0;
}




void test1()
{
slist_t *my_list = NULL;

	slist_iter_t iterator_1 = NULL;
	slist_iter_t iterator_2 = NULL;
		
	int x = 10;
	int y = 20;
	
	void *data1 = &x;
	void *data2 = &y;
	
	size_t size = 0;
	
	my_list = SListCreate();

	
	iterator_1 = SListEnd(my_list);
	iterator_1 = SListInsertBefore(iterator_1, &data1);
	
	iterator_2 = SListEnd(my_list);
	iterator_2 = SListInsertBefore(iterator_2, &data2);
	
	
	
	size =  SListCount(my_list);
	
	printf("the size of the list is: %ld\n",size);

	SListDestroy(my_list);
}


void test2()
{
slist_t *my_list = NULL;
	slist_t *my_list_2 = NULL;
	slist_iter_t iterator_1 = NULL;
	slist_iter_t iterator_2 = NULL;
	slist_iter_t iterator_3 = NULL;
	slist_iter_t iterator_4 = NULL;
	int val = 32;
	int val_2 = 53;
	int val_3 = 12;
	int val_4 = 132;
	int val_5 = 153;
	int val_6 = 112;
	void *element = NULL;
	
	printf("\n");
	
	my_list = SListCreate();
	
	printf("Is empty: %s\n", SListIsEmpty(my_list) ? "Ok" : "FAILED");	

	iterator_1 = SListBegin(my_list);
	
	iterator_2 = SListInsertBefore(iterator_1, &val);
	element = SListGetData(iterator_2);
	printf("Insert before & Get Data: %s\n", *(int*)element == val ? "Ok" : "FAILED");	

	printf("Is empty: %s\n", !SListIsEmpty(my_list) ? "Ok" : "FAILED");	

	iterator_3 = SListInsertBefore(iterator_2, &val);
	element = SListGetData(iterator_3);
	printf("Insert before & Get Data: %s\n", *(int*)element == val ? "Ok" : "FAILED");	

	SListSetData(iterator_3, &val_2);
	element = SListGetData(iterator_3);
	printf("Set Data: %s\n", *(int*)element == val_2 ? "Ok" : "FAILED");	

	iterator_4 = SListInsertBefore(iterator_3, &val);
	SListSetData(iterator_4, &val_3);


	iterator_1 = SListBegin(my_list); /* restarted because of the insert before */
	iterator_2 = SListBegin(my_list); /* restarted because of the insert before */
	iterator_3 = SListBegin(my_list); /* restarted because of the insert before */

	iterator_1 = SListNext(iterator_1);
	iterator_2 = SListNext(SListNext(iterator_1));
	iterator_3 = SListNext(SListNext(iterator_1));
	
	printf("Next & Is Equal 1: %s\n", SListIsEqual(iterator_2, iterator_3) ? "Ok" : "FAILED");	
	printf("Next & Is Equal 2: %s\n", !SListIsEqual(iterator_1, iterator_3) ? "Ok" : "FAILED");	
	
	iterator_1 = SListBegin(my_list);


	iterator_4 = SListFind(iterator_1, iterator_3, &DoesIntMatch, &val_2);
	element = SListGetData(iterator_4);
	printf("List Find: %s\n", *(int*)element == val_2 ? "Ok" : "FAILED");	
	iterator_4 = SListFind(SListNext(iterator_1), iterator_2, &DoesIntMatch, &val_3);
	printf("List Find: %s\n", iterator_2 == iterator_4 ? "Ok" : "FAILED");	

	iterator_4 = SListInsertAfter(iterator_1, &val);
	element = SListGetData(iterator_4);
	printf("Insert after & Get Data: %s\n", *(int*)element == val ? "Ok" : "FAILED");	
	
	iterator_4 = SListRemove(iterator_4);
	element = SListGetData(iterator_4);
	printf("Remove & Get Data: %s\n", *(int*)element == val_2 ? "Ok" : "FAILED");	

	iterator_1 = SListBegin(my_list);
	iterator_2 = SListEnd(my_list);

	printf("End & For Each & Count: %s\n", 3 == SListCount(my_list) ? "Ok" : "FAILED");	


	my_list_2 = SListCreate();


	iterator_1 = SListBegin(my_list_2);
	iterator_2 = SListInsertBefore(iterator_1, &val_4);
	iterator_3 = SListInsertBefore(iterator_2, &val_5);
	iterator_4 = SListInsertBefore(iterator_3, &val_6);

	SListAppend(my_list, my_list_2);

	iterator_1 = SListBegin(my_list);
	iterator_2 = SListEnd(my_list);
	printf("Append 1: %s\n", 6 == SListCount(my_list) ? "Ok" : "FAILED");	


	printf("Append 2: %s\n", SListIsEmpty(my_list_2) ? "Ok" : "FAILED");	

	iterator_1 = SListBegin(my_list_2);
	iterator_3 = SListInsertBefore(iterator_1, &val);
	iterator_2 = SListInsertBefore(iterator_3, &val_3);

	printf("Append 3: %s\n", 2 == SListCount(my_list_2) ? "Ok" : "FAILED");	

	SListDestroy(my_list);
	SListDestroy(my_list_2);

	printf("\n\n");

}

















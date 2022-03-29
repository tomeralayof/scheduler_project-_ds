#include "../include/dll.h" 
#include <stdio.h>
#include <assert.h>


void TomerTest();
void Test1();
static void PrintCharList(dlist_t *list);
void Test2();
void TestSplice();

#define CASTING(type, var) (*(type *)&(var))

int DoesIntMatch(const void *element_1, void *element_2)
{
	return *(int *)element_1 == *(int *)element_2;
}

int TurnDataToSeven(void *data, void *param)
{
	(void)param;
	*CASTING(int *, data) = 7;
	return 0;
}


int main()
{
	
	
	/*TomerTest();*/
	/*Test1();*/
	/*Test1();*/
	/*Test2();*/
	
	/*Test1();*/
	
	TestSplice();
	return 0;
}


void TomerTest()
{
	
	dlist_iter_t iterator_1 = NULL;
	dlist_iter_t iterator_2 = NULL;
	dlist_iter_t iterator_3 = NULL;
	dlist_iter_t iterator_4 = NULL;	
	dlist_iter_t iterator_6 = NULL;
	dlist_iter_t iterator_7 = NULL;
	
	dlist_iter_t iterator_find = NULL;
 	
	size_t count = 0;
	
	int x = 10;
	int y = 20;
	
	int k = 30;
	int a = 100;
	
	void *data1 = &x;
	void *data2 = &y;
	void *data3 = &k;
	void *data4 = &a;
	
	/*list 2*/
	dlist_iter_t iterator_l_2_1 = NULL;
	dlist_iter_t iterator_l_2_2 = NULL;
	dlist_iter_t iterator_l_2_3 = NULL;
	dlist_iter_t iterator_l_2_4 = NULL;	
	
	dlist_t *doubly_linked_list = DListCreate();
	dlist_t *doubly_linked_list2 = DListCreate();
	
	
	/*tests for list 1*/	
	assert(iterator_1 = DListEnd(doubly_linked_list));
	assert(DListIsEmpty(doubly_linked_list) == 1);
	assert(DListBegin(doubly_linked_list) != NULL);	
	iterator_2 = DListInsert(iterator_1, data1);
	iterator_3 = DListInsert(iterator_2,data2);
	assert(iterator_2 == DListPrev(iterator_1));
	assert(iterator_3 == DListPrev(iterator_2));
	assert(DListIsEmpty(doubly_linked_list) == 0);
	assert(iterator_3 == DListBegin(doubly_linked_list));
	assert(iterator_1 != DListBegin(doubly_linked_list));
	assert(iterator_1 == DListEnd(doubly_linked_list));
	
	count = DListSize(doubly_linked_list);
	assert(count == 2);
	
	iterator_4 = DListInsert(iterator_3,data3);
	count = DListSize(doubly_linked_list);
	assert(count == 3);
	assert(iterator_4 == DListBegin(doubly_linked_list));


	DListRemove(iterator_4);
	count = DListSize(doubly_linked_list);
	assert(count == 2);
	assert(iterator_3 == DListBegin(doubly_linked_list));
	
	iterator_4 = DListInsert(iterator_3,data3);
	count = DListSize(doubly_linked_list);
	assert(count == 3);
	assert(iterator_4 == DListBegin(doubly_linked_list));
	
	
	DListPopFront(doubly_linked_list);
	count = DListSize(doubly_linked_list);
	assert(count == 2);
	assert(iterator_3 == DListBegin(doubly_linked_list));
	assert(iterator_1 = DListEnd(doubly_linked_list));
	
	assert(NULL == DListGetData(iterator_1));
	assert(data1 == DListGetData(iterator_2));
	assert(data2 == DListGetData(iterator_3));
	
	
	iterator_find = DListFind(DListBegin(doubly_linked_list), DListEnd(doubly_linked_list), &DoesIntMatch,data2);
	assert(DListIsEqual(iterator_find, iterator_3) == 1);
	
	
	iterator_4 = DListPushFront(doubly_linked_list,data3);
	assert(iterator_4 == DListBegin(doubly_linked_list));
	
	count = DListSize(doubly_linked_list);
	assert(count == 3);
	
	
	iterator_6 = DListPushBack(doubly_linked_list,data4);
	count = DListSize(doubly_linked_list);
	assert(count == 4);
	assert(iterator_1 ==DListEnd(doubly_linked_list)); 
	
	
	iterator_7 = DListPushBack(doubly_linked_list,data1);
	count = DListSize(doubly_linked_list);
	assert(count == 5);
	
	
	DListRemove(iterator_7);
	DListRemove(iterator_6);		
	DListRemove(iterator_4);
	DListRemove(iterator_3);
	DListRemove(iterator_2);
	count = DListSize(doubly_linked_list);				
	assert(count == 0);
	
	
	iterator_2 = DListInsert(iterator_1, data1);
	iterator_3 = DListInsert(iterator_2,data2);
	iterator_4 = DListInsert(iterator_3,data2);
	iterator_6 = DListInsert(iterator_4,data2);
	iterator_7 = DListInsert(iterator_6,data2);
	count = DListSize(doubly_linked_list);				
	assert(count == 5); 
	
	
	
	/*tests for list 1 and 2*/
	assert(iterator_l_2_1 = DListEnd(doubly_linked_list2));
	iterator_l_2_2 = DListInsert(iterator_l_2_1, data1);
	iterator_l_2_3 = DListInsert(iterator_l_2_2,data1);
	iterator_l_2_4 = DListInsert(iterator_l_2_3,data1);
	
	count = DListSize(doubly_linked_list2);				
	assert(count == 3);
	
	
	
	
	printf("SUCCESS!!!\n");
	
	
	DListDestroy(doubly_linked_list);
	DListDestroy(doubly_linked_list2);
	
}

int MatchSeven(const void *data, void *param)
{
	return *CASTING(int *, data) == *CASTING(int *, param);
}

static void PrintIntList(dlist_t *list)
{
	dlist_iter_t runner = DListBegin(list);
	void *p = NULL;
	printf("list contain: ");
	while (runner != DListEnd(list))
	{
		p = DListGetData(runner);
		printf("%d, ", *CASTING(int *, p));
		runner = DListNext(runner);
	}
	printf("\n");
}

void Test1()
{
	dlist_t *result_list = DListCreate();
	dlist_t *my_list = DListCreate();
	int x1 = 2;
	int x2 = 4;
	int x3 = 8;
	int x4 = 16;
	int x0 = 1;
	int param = 7;
	void *p = &param;
	void *stam = &x0;
	dlist_iter_t end_node = DListBegin(my_list);
	dlist_iter_t first_node = DListInsert(end_node, &x1);
	dlist_iter_t second_node = DListInsert(end_node, &x2);
	dlist_iter_t third_node = DListInsert(end_node, &x3);
	dlist_iter_t forth_node = DListInsert(end_node, &x4);
	printf("-------------------Test 1---------------------\n");
	assert(0 == DListIsEmpty(my_list));
	printf("list should contain after 4 inserts: 2, 4, 8, 16\n");
	PrintIntList(my_list);
	assert(4 == DListSize(my_list));
	DListPushFront(my_list, &x0);
	printf("list should contain after pushfront: 1, 2, 4, 8, 16\n");
	PrintIntList(my_list);
	assert(5 == DListSize(my_list));
	DListRemove(third_node);
	printf("list after removing 8:\n");
	PrintIntList(my_list);
	assert(4 == DListSize(my_list));
	DListForEach(DListBegin(my_list), forth_node, &TurnDataToSeven, stam);
	printf("list after setting nodes 1-3 to 7:\n");
	PrintIntList(my_list);
	DListMultiFind(DListBegin(my_list), DListEnd(my_list), &MatchSeven, p, result_list);
	printf("result list after multifind 7 contain:\n");
	PrintIntList(result_list);
	DListSplice(forth_node, DListBegin(result_list), DListEnd(result_list));
	printf("list after splicing result list into the end of list:\n");
	PrintIntList(my_list);

	DListDestroy(my_list);
	DListDestroy(result_list);
}



/*
static void PrintCharList(dlist_t *list)
{
	dlist_iter_t runner = DListBegin(list);
	void *p = NULL;
	printf("list contain: ");
	while (runner != DListEnd(list))
	{
		p = DListGetData(runner);
		printf("%c, ", *CASTING(char *, p));
		runner = DListNext(runner);
	}
	printf("\n");
}
*/






static void PrintCharList(dlist_t *list)
{
	dlist_iter_t runner = DListBegin(list);
	void *p = NULL;
	printf("list contain: ");
	while (runner != DListEnd(list))
	{
		p = DListGetData(runner);
		printf("%ld, ", (size_t)p);
		runner = DListNext(runner);
	}
	printf("\n");
}

















int MatchChar(const void *data, void *param)
{
	return *CASTING(char *, data) == *CASTING(char *, param);
}

void Test2()
{
	dlist_t *my_list = DListCreate();
	char c1 = 'd';
	char c2 = 'o';
	char c3 = 'r';
	char c4 = 'i';
	char c5 = 'g';
	char c6 = 'l';
	char c7 = 'e';
	char c8 = 'r';
	void *p = &c5;
	void *data = NULL;
	dlist_iter_t end_node = DListBegin(my_list);
	dlist_iter_t first_node = DListInsert(end_node, &c1);
	dlist_iter_t second_node = DListPushBack(my_list, &c2);
	dlist_iter_t third_node = DListPushBack(my_list, &c3);
	dlist_iter_t forth_node = DListPushBack(my_list, &c4);
	dlist_iter_t fifth_node = DListPushBack(my_list, &c5);
	dlist_iter_t sixth_node = DListPushBack(my_list, &c6);
	dlist_iter_t seventh_node = DListPushBack(my_list, &c7);
	dlist_iter_t eighth_node = DListPushBack(my_list, &c8);
	dlist_iter_t find_node = NULL;
	printf("-------------------Test 2---------------------\n");
	printf("list after several pushback should be \"dorigler\"\n");
	PrintCharList(my_list);
	DListPopFront(my_list);
	printf("list after poping first element: \n");
	PrintCharList(my_list);
	DListPushFront(my_list, &c1);
	printf("that not nice, lets put the 'd' back with pushfront: \n");
	PrintCharList(my_list);
	find_node = DListFind(DListBegin(my_list), DListEnd(my_list), &MatchChar, p);
	data = DListGetData(find_node);
	printf("let search letter 'g' using find: \nsearch result: \n");
	printf("%c\n", *CASTING(char *, data));
	DListDestroy(my_list);
}

void TestSplice()
{
	dlist_t *test_list1 = DListCreate();
	dlist_t *test_list2 = DListCreate();
	dlist_iter_t iterator_from = NULL;
	dlist_iter_t iterator_to = NULL;
	dlist_iter_t iterator_where = NULL;
	dlist_iter_t iterator = NULL;
	DListPushBack(test_list1, (void *) 0);
	iterator_from = DListPushBack(test_list1, (void *) 1);
	DListPushBack(test_list1, (void *) 2);
	iterator_to = DListEnd(test_list1);

	iterator_where = DListPushBack(test_list2, (void *) 3);
	DListPushBack(test_list2, (void *) 4);
	DListPushBack(test_list2, (void *) 5);
	
	DListSplice(iterator_where, iterator_from, iterator_to);

	assert(1 == DListSize(test_list1));
	assert(5 == DListSize(test_list2));
	
	iterator = DListBegin(test_list2);
	assert(1 == (size_t) DListGetData(iterator));
	
	iterator = DListNext(iterator);
	assert(2 == (size_t) DListGetData(iterator));
	
	iterator = DListNext(iterator);
	assert(3 == (size_t) DListGetData(iterator));
	
	iterator = DListNext(iterator);
	assert(4 == (size_t) DListGetData(iterator));
	
	iterator = DListNext(iterator);
	assert(5 == (size_t) DListGetData(iterator));
	iterator = DListNext(iterator);
	
	PrintCharList(test_list1);
	printf("\n");
	PrintCharList(test_list2);



	DListDestroy(test_list1);
	DListDestroy(test_list2);
	
	printf("test clear\n");
	
	
}











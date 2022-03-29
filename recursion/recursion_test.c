/**********************************\
* RECURSION                        *
* Developer: Tomer Alayof          *
* Written: 2021-1-25               *
*                                  *
* Reviewer:  Shaked Maman          *
\**********************************/

#include <stdio.h>
#include <assert.h>

#include "../include/recursion.h"

void FibonachiRecursionTest();
void TestRecursionFlipList();
void TestStrLen();
void TestStrCmp();
void TestStrCpy();
void TestStrCat();
void TestRecStack();
void FibonachiIterativeTest();
void TestStrStr();

int main()
{
 	FibonachiRecursionTest();
	TestRecursionFlipList();
	TestStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrCat();
	TestRecStack();
	FibonachiIterativeTest();
	TestStrStr();

 	printf("SUCCESS\n");

	return 0;
}

void FibonachiRecursionTest()
{
	int result = 0;
	int idx = 5;
	result = RecFibonacci(idx);

	assert(result == 5);
}

void FibonachiIterativeTest()
{
	int result = 0;
	int idx = 5;
	result = IterFibonacci(idx);
	assert(result == 5);
}


void TestRecursionFlipList()
{
	node_t *first_node = (node_t *)malloc(sizeof(struct node));
	node_t *second_node = (node_t *)malloc(sizeof(struct node));
	node_t *third_node = (node_t *)malloc(sizeof(struct node));
	node_t *fourt_node = (node_t *)malloc(sizeof(struct node));
	node_t *fifth_node = (node_t *)malloc(sizeof(struct node));

	first_node->next = second_node;
	second_node->next = third_node;
	third_node->next = fourt_node;
	fourt_node->next = fifth_node;
	fifth_node->next = NULL;

	RecFlipList(first_node);

	assert(first_node->next == NULL);
	assert(second_node->next == first_node);
	assert(third_node->next == second_node);
	assert(fourt_node->next == third_node);
	assert(fifth_node->next == fourt_node);

	free(first_node);
	free(second_node);
	free(third_node);
	free(fourt_node);
	free(fifth_node);
}

void TestStrLen()
{
    const char *str = "tomer";
    const char *str1 = "";

    assert(5 == RecStrLen(str));
    assert(0 == RecStrLen(str1));

    printf("STRLEN SUCCESS\n");
}


void TestStrCmp()
{
	const char * s1 = "tomer";
	const char * s2 = "tomer";

	int res = RecStrCmp(s1,s2);

	printf("result: %d\n",res);
}

void TestStrCpy()
{

	char *src = "tomer alayof";
	char dest[15] = {0};

	RecStrCpy(dest,src);

	printf("%s\n",dest);
}

void TestStrCat()
{
	char dest[100] = "tomer";
	const char *src = "alayof";
	char *ptr = NULL;

	printf("gaza\n");

	ptr = RecStrCat(dest,src);

	printf("%s\n",ptr);
	printf("%s\n",dest);

}

void TestRecStack()
{
	int x1 = -3;
	int x2 = 14;
	int x3 = 18;
	int x4 = -5;
	int x5 = 30;
	int res = 0;

	int i = 0;

	stack_t *stack1 = StackCreate(5,sizeof(int));

	StackPush(stack1,&x1);
	StackPush(stack1,&x2);
	StackPush(stack1,&x3);
	StackPush(stack1,&x4);
	StackPush(stack1,&x5);

	RecSort(stack1);

	for (i = 0; i < 5; ++i)
	{
		res = *(int*)StackPeek(stack1);
		StackPop(stack1);
		printf("%d ", res);
	}

	printf("\n");

	free(stack1);

}

void TestStrStr()
{
	const char *needle = "shai";
	const char *hystack = "infinishai";

	hystack = RecStrStr(hystack,needle);

	printf("%s\n",hystack);
}
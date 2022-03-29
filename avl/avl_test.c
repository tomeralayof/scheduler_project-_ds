/***********************************************
 * Recursive Balanced Binary Search Tree (AVL) *
 * Developer: Tomer Alayof                     *
 * Written: 2021-01-26                         *
 *                                             *
 * Reviewer:  Daniella                         *
 **********************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/avl.h"

void TestInsert();
void TestForEachInOrder();
void TestForEachInPreOderer();
void TestForEachInPostOderer();
void TestCountEmptyTree();
void TestFreeEmptyTree();
void Test5();
void Test6();

void AvlInsert();
void TestBalanceRemove();

static int actionFunc(void *data, void *param);
static int Comp_Func(const void *data1, const void *data2);

void TestFind();

int main()
{
	/*Test6();

	AvlInsert();
	
	Test5();
	
	TestCountEmptyTree();
	TestInsert();
	TestFind();
	TestForEachInPreOderer();	
	TestForEachInPostOderer();
	TestFreeEmptyTree();

	AvlInsert();*/

 	/*TestBalanceRemove();*/
/*
 	TestForEachInPostOderer();
 	TestForEachInOrder();
 	TestForEachInPreOderer();
*/
 	TestBalanceRemove();

	printf("SUCCESS\n");
	
	return 0;
}

void TestBalanceRemove()
{
	avl_t *avl_tree = AVLCreate(&Comp_Func);

	int x1 = 10;
	int x2 = 2;
	int x3 = 1;
	int x4 = 15;
	int x5 = 9;
	int x7 = 11;
	int x8 = 7;
	int x9 = 8;
	int x10 = 6;
	int x11 = 5;
	int x12 = 20;
	int x13 = 22;
	
	AVLInsert(avl_tree, &x1);
	AVLInsert(avl_tree, &x2);
	AVLInsert(avl_tree, &x3);
	AVLInsert(avl_tree, &x4);
	AVLInsert(avl_tree, &x5);
	AVLInsert(avl_tree, &x7);
	AVLInsert(avl_tree, &x8);
	AVLInsert(avl_tree, &x9);
	AVLInsert(avl_tree, &x10);
	AVLInsert(avl_tree, &x11);
	AVLInsert(avl_tree, &x12);
	AVLInsert(avl_tree, &x13);

	PrintTreeByLevels(avl_tree);

	printf("After remove:\n");

	AVLRemove(avl_tree, &x13);
	AVLRemove(avl_tree, &x10);
	AVLRemove(avl_tree, &x1);

	PrintTreeByLevels(avl_tree);

	AVLDestroy(avl_tree);
	printf("\nTestBalanceRemove SUCCESS\n");
}


static int Comp_Func(const void *left, const void *right)
{
	return *(int *)left - *(int *)right;
}



void AvlInsert()
{
	avl_t *avl_tree = AVLCreate(&Comp_Func);
	int x1 = 9;
	int x2 = 15;
	int x3 = 20;
	int x4 = 8;
  	int x5 = 7;
 	int x6 = 13;

	AVLInsert(avl_tree, &x1);
	AVLInsert(avl_tree, &x2);
	AVLInsert(avl_tree, &x3);
	AVLInsert(avl_tree, &x4);
	AVLInsert(avl_tree, &x5);
	AVLInsert(avl_tree, &x6);

	PrintTreeInOrder(avl_tree);
	PrintTreeByLevels(avl_tree);

	AVLDestroy(avl_tree);
}

void Test6()
{
	avl_t *avl_tree = AVLCreate(&Comp_Func);
	int x1 = 10;
	int x2 = 2;
	int x3 = -1;
	int x4 = 15;
	int x5 = 9;
	/*int x6 = -2;*/
	int x7 = 11;
	int x8 = 7;
	int x9 = 8;
	int x10 = 6;
	int x11 = 5;
	int x12 = 20;
	int x13 = 22;
	AVLInsert(avl_tree, &x1);
	AVLInsert(avl_tree, &x2);
	AVLInsert(avl_tree, &x3);
	AVLInsert(avl_tree, &x4);
	AVLInsert(avl_tree, &x5);
	/*AVLInsert(avl_tree, &x6);*/
	AVLInsert(avl_tree, &x7);
	AVLInsert(avl_tree, &x8);
	AVLInsert(avl_tree, &x9);
	AVLInsert(avl_tree, &x10);
	AVLInsert(avl_tree, &x11);
	AVLInsert(avl_tree, &x12);
	AVLInsert(avl_tree, &x13);

	PrintTreeInOrder(avl_tree);
	PrintTreeByLevels(avl_tree);
	PrintTreeInOrder(avl_tree);

	AVLDestroy(avl_tree);
	printf("\nTEST 6 SUCCESS\n");
}


void Test5()
{
	avl_t *avl_tree = AVLCreate(&Comp_Func);
	int x1 = 10;
	int x2 = 2;
	int x3 = -1;
	int x4 = 15;
	int x5 = 9;
	int x6 = -2;
	int x7 = 11;
	int x8 = 7;
	int x9 = 8;
	int x10 = 6;
	int x11 = 5;
	int x12 = 20;
	int x13 = 22;

	AVLInsert(avl_tree, &x1);
	AVLInsert(avl_tree, &x2);
	AVLInsert(avl_tree, &x3);
	AVLInsert(avl_tree, &x4);
	AVLInsert(avl_tree, &x5);
	AVLInsert(avl_tree, &x6);
	AVLInsert(avl_tree, &x7);
	AVLInsert(avl_tree, &x8);
	AVLInsert(avl_tree, &x9);
	AVLInsert(avl_tree, &x10);
	AVLInsert(avl_tree, &x11);
	AVLInsert(avl_tree, &x12);
	AVLInsert(avl_tree, &x13);

	printf("before remove 2: \n");
	PrintTreeInOrder(avl_tree);
	/* node to remove has two childrens and his next is deep in his right sub tree */
	AVLRemove(avl_tree, &x2);

	printf("after remove 2:\n");  
	PrintTreeInOrder(avl_tree);
	/* node to remove has two childrens and his next is directly his right child */

	
	AVLRemove(avl_tree, &x8);
	PrintTreeInOrder(avl_tree);

	
	AVLRemove(avl_tree, &x4);
	PrintTreeInOrder(avl_tree);
	

	AVLDestroy(avl_tree);
	printf("\nTEST 5 SUCCESS\n");
}

void TestFreeEmptyTree()
{
	avl_t *avl = AVLCreate(&Comp_Func);

	AVLDestroy(avl);
}


void TestCountEmptyTree()
{
	avl_t *avl = AVLCreate(&Comp_Func);
	size_t count = 0;
	int data1 = 4;

	count = AVLSize(avl);
	printf("size sould be 0: %ld\n",count);

	AVLInsert(avl, &data1);

	count = AVLSize(avl);
	printf("size sould be 1: %ld\n",count);

	AVLDestroy(avl);
}

void TestInsert()
{
	avl_t *avl = AVLCreate(&Comp_Func);

	int data1 = 4;
	int data2 = 11;
	int data3 = 3;
	int data4 = 5;
	int data5 = 2;
	int data6 = 1;

	assert(1 == AVLIsEmpty(avl));

	AVLInsert(avl, &data1);
	AVLInsert(avl, &data2);
	AVLInsert(avl, &data3);
	AVLInsert(avl, &data4);
	AVLInsert(avl, &data5);
	AVLInsert(avl, &data6);

	PrintTreeInOrder(avl);

	AVLDestroy(avl);
}

void TestFind()
{
	avl_t *avl_tree = AVLCreate(&Comp_Func);

	int x1 = 10;
	int x2 = 8;
	int x3 = 4;
	int x4 = 12;
	int x5 = 9;
	int x6 = 1;
	int x7 = 11;
	int x8 = 93784;

	void *find = NULL;

	AVLInsert(avl_tree, &x1);
	AVLInsert(avl_tree, &x2);
	AVLInsert(avl_tree, &x3);
	AVLInsert(avl_tree, &x4);
	AVLInsert(avl_tree, &x5);
	AVLInsert(avl_tree, &x6);
	AVLInsert(avl_tree, &x7);

	PrintTreeInOrder(avl_tree);
	find = AVLFind(avl_tree, &x5);

	printf("searched for 9 in the tree and found: %d\n", *(int *)find);

	find = AVLFind(avl_tree, &x8);
	assert(NULL == find);

	AVLDestroy(avl_tree);

	printf("Test Find  SUCCESS\n");
}

void TestForEachInOrder()
{

	avl_t *avl = AVLCreate(&Comp_Func);

	int data1 = 4;
	int data2 = 2;
	int data3 = 1;
	int data4 = 3;
	int data5 = 11;
	int data6 = 23;
	int data7 = 6;

	int dataTest = 10;
	size_t size = 0;

	assert(1 == AVLIsEmpty(avl));

	AVLInsert(avl, &data1);
	AVLInsert(avl, &data2);
	AVLInsert(avl, &data3);
	AVLInsert(avl, &data4);
	AVLInsert(avl, &data5);
	AVLInsert(avl, &data6);
	AVLInsert(avl, &data7);

	PrintTreeInOrder(avl);

	printf("in order: ");
	AVLForEach(avl,&actionFunc, &dataTest,IN_ORDER);

	printf("\n");

	size = AVLSize(avl);

	printf("size should be 7: %ld\n",size);

	AVLDestroy(avl);
}

void TestForEachInPreOderer()
{

	avl_t *avl = AVLCreate(&Comp_Func);

	int data1 = 4;
	int data2 = 2;
	int data3 = 1;
	int data4 = 3;
	int data5 = 11;
	int data6 = 23;
	int data7 = 6;

	int dataTest = 10;
	size_t size = 0;

	assert(1 == AVLIsEmpty(avl));

	AVLInsert(avl, &data1);
	AVLInsert(avl, &data2);
	AVLInsert(avl, &data3);
	AVLInsert(avl, &data4);
	AVLInsert(avl, &data5);
	AVLInsert(avl, &data6);
	AVLInsert(avl, &data7);

	PrintTreeInOrder(avl);

	printf("pre order:(4,2,1,3,11,6,23) ");
	AVLForEach(avl,&actionFunc, &dataTest,PRE_ORDER);

	printf("\n");

	size = AVLSize(avl);

	printf("size should be 7: %ld\n",size);
	AVLDestroy(avl);
}

void TestForEachInPostOderer()
{
	avl_t *avl = AVLCreate(&Comp_Func);

	int data1 = 4;
	int data2 = 2;
	int data3 = 1;
	int data4 = 3;
	int data5 = 11;
	int data6 = 23;
	int data7 = 6;

	int dataTest = 10;
	size_t size = 0;

	assert(1 == AVLIsEmpty(avl));

	AVLInsert(avl, &data1);
	AVLInsert(avl, &data2);
	AVLInsert(avl, &data3);
	AVLInsert(avl, &data4);
	AVLInsert(avl, &data5);
	AVLInsert(avl, &data6);
	AVLInsert(avl, &data7);

	PrintTreeInOrder(avl);

	printf("post order:(1,3,2,6,23,11,4) ");
	AVLForEach(avl,&actionFunc, &dataTest,POST_ORDER);

	printf("\n");

	size = AVLSize(avl);

	printf("size should be 7: %ld\n",size);

	AVLDestroy(avl);
}

static int actionFunc(void *data, void *param)
{
	(void)param;
	printf("%d ",*(int *)data);

	if (*(int *)data  ==  11)
	{
		return 1;
	}

	return 0;
}

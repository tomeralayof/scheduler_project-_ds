/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          18/1/22                                                 ***
 *** Reviewer:      Gal 		                                            ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** testing for BST.			                                            ***
 ******************************************************************************
 \*****************************************************************************/

#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/

#include "../include/bst.h"

void TestInsertFind();
void TestNext();
void TestCount();
void TestForEach();
void TestRemoveWithoutDoubleChilds();
void TestRemoveDoubleChilds();
void TestRemoveShoshana();

static int Compare(const void *data1,const void *data2);
static int PrintEven(void *data, void *param);
static void PrintTree(bst_t *tree);


int main()
{	
	TestInsertFind();
	TestNext();
	TestCount();
	TestForEach();
	TestRemoveWithoutDoubleChilds();
	TestRemoveDoubleChilds();
	TestRemoveShoshana();
	TestRemoveDoubleChilds();
	TestRemoveWithoutDoubleChilds();
	
	printf("SUCCESS\n");

	return 0;
}

void TestInsertFind()
{
	int data1 = 4;
	int data2 = 2;
	int data3 = 11;

	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	
	bst_t * bst = BSTCreate(&Compare);
	
	assert(1 == BSTIsEmpty(bst));
	
	iter1 = BSTInsert(bst, &data1);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	
	assert(0 == BSTIsEmpty(bst));
	
	assert(4 == *(int *)BSTGetData(iter1));
	assert(2 == *(int *)BSTGetData(iter2));
	assert(11 == *(int *)BSTGetData(iter3));
	
	
	assert(iter1 == BSTFind(bst,&data1));
	assert(iter2 == BSTFind(bst,&data2));
	assert(iter3 == BSTFind(bst,&data3));
	
	assert(iter2 == BSTBegin(bst));	
	
	assert((size_t)3 == BSTSize(bst));
	
	BSTDestroy(bst);
}

void TestNext()
{
	int data1 = 4;
	int data2 = 2;
	int data3 = 3;
	int data4 = 1;
	
	int data5 = 11;
	int data6 = 12;
	int data7 = 23;
	
	int data8 = 5;
	int data9 = 7;
	int data10 = 9;
	
	int data11 = 6;
		
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	
	bst_t * bst = BSTCreate(&Compare);
	
	iter1 = BSTInsert(bst, &data1);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	
	iter4 = BSTInsert(bst, &data4);
	iter5 = BSTInsert(bst, &data5);
	iter6 = BSTInsert(bst, &data6);
	
	iter7 = BSTInsert(bst, &data7);
	iter8 = BSTInsert(bst, &data8);
	iter9 = BSTInsert(bst, &data9);
	
	iter10 = BSTInsert(bst, &data10);
	iter11 = BSTInsert(bst, &data11);
	
	
	assert(4 == *(int *)BSTGetData(iter1)); 
	assert(2 == *(int *)BSTGetData(iter2)); 
	assert(3 == *(int *)BSTGetData(iter3)); 
	assert(1 == *(int *)BSTGetData(iter4)); 
	assert(11 == *(int *)BSTGetData(iter5)); 
	assert(12 == *(int *)BSTGetData(iter6)); 
	assert(23 == *(int *)BSTGetData(iter7)); 
	assert(5 == *(int *)BSTGetData(iter8)); 
	assert(7 == *(int *)BSTGetData(iter9)); 
	assert(9 == *(int *)BSTGetData(iter10)); 
	assert(6 == *(int *)BSTGetData(iter11)); 
	
	
	iter4 = BSTNext(iter4);
	iter10 = BSTNext(iter10);
	iter8 = BSTNext(iter8);
	iter7 = BSTNext(iter7);
	
	assert(1 == BSTIterIsEqual(iter4,iter2));
	assert(1 == BSTIterIsEqual(iter10,iter5));
	assert(1 == BSTIterIsEqual(iter8,iter11));
	
	BSTDestroy(bst);
	
	
}

void TestCount()
{
	int data1 = 4;
	int data2 = 2;
	int data3 = 3;
	int data4 = 1;
	
	size_t size = 0;
	
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	
	bst_t * bst = BSTCreate(&Compare);
	
	iter1 = BSTInsert(bst, &data1);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	iter4 = BSTInsert(bst, &data4);
	
	(void)iter1;
	(void)iter2;
	(void)iter3;
	(void)iter4;
	
	size = BSTSize(bst);
	
	assert((size_t)4 == size);
	
	BSTDestroy(bst);
}

void TestForEach()
{
	int data1 = 4;
	int data2 = 2;
	int data3 = 3;
	int data4 = 1;
	
	int e = 2;
	
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	bst_iter_t iter4 = NULL;
	
	bst_t * bst = BSTCreate(&Compare);
	
	iter1 = BSTInsert(bst, &data1);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	iter4 = BSTInsert(bst, &data4);
	
	(void)iter1;
	(void)iter2;
	(void)iter3;
	(void)iter4;
	
	printf("suppose to print 2 and 4: \n");
	BSTForEach(BSTBegin(bst), BSTEnd(bst), &PrintEven, &e);
	printf("\n");
	
	BSTDestroy(bst);
	
}

void TestRemoveWithoutDoubleChilds()
{
	int data1 = 4;
	int data2 = 2;
	int data3 = 3;
	int data4 = 1;
	
	int data5 = 11;
	int data6 = 12;
	int data7 = 23;
	
	int data8 = 5;
	int data9 = 7;
	int data10 = 9;
	
	int data11 = 6;
		
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	
	bst_t * bst = BSTCreate(&Compare);
	
	iter1 = BSTInsert(bst, &data1);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	
	iter4 = BSTInsert(bst, &data4);
	iter5 = BSTInsert(bst, &data5);
	iter6 = BSTInsert(bst, &data6);
	
	iter7 = BSTInsert(bst, &data7);
	iter8 = BSTInsert(bst, &data8);
	iter9 = BSTInsert(bst, &data9);
	
	iter10 = BSTInsert(bst, &data10);
	iter11 = BSTInsert(bst, &data11);
	
	
	(void)iter1;
	(void)iter2;
	(void)iter3;
	(void)iter4;
	
	(void)iter5;
	(void)iter6;
	(void)iter7;
	(void)iter8;
	
	(void)iter9;
	(void)iter10;
	(void)iter11;

	assert((size_t)11 == BSTSize(bst));
	
	BSTRemove(iter4);
	assert((size_t)10 == BSTSize(bst));
	
	BSTRemove(iter3);
	assert((size_t)9 == BSTSize(bst));
	
	PrintTree(bst);
	
	
	BSTRemove(iter8);
	assert((size_t)8 == BSTSize(bst));
	PrintTree(bst);
	
	
	BSTDestroy(bst);
	
}

void TestRemoveDoubleChilds()
{
	int data1 = 4;
	int data2 = 2;
	int data3 = 3;
	int data4 = 1;
	
	int data5 = 11;
	int data6 = 12;
	int data7 = 23;
	
	int data8 = 5;
	int data9 = 7;
	int data10 = 9;
	
	int data11 = 6;
		
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	bst_iter_t iter3 = NULL;
	
	bst_iter_t iter4 = NULL;
	bst_iter_t iter5 = NULL;
	bst_iter_t iter6 = NULL;
	
	bst_iter_t iter7 = NULL;
	bst_iter_t iter8 = NULL;
	bst_iter_t iter9 = NULL;
	
	bst_iter_t iter10 = NULL;
	bst_iter_t iter11 = NULL;
	
	bst_t * bst = BSTCreate(&Compare);
	
	iter1 = BSTInsert(bst, &data1);
	iter2 = BSTInsert(bst, &data2);
	iter3 = BSTInsert(bst, &data3);
	
	iter4 = BSTInsert(bst, &data4);
	iter5 = BSTInsert(bst, &data5);
	iter6 = BSTInsert(bst, &data6);
	
	iter7 = BSTInsert(bst, &data7);
	iter8 = BSTInsert(bst, &data8);
	iter9 = BSTInsert(bst, &data9);
	
	iter10 = BSTInsert(bst, &data10);
	iter11 = BSTInsert(bst, &data11);
	
	
	(void)iter1;
	(void)iter2;
	(void)iter3;
	(void)iter4;
	
	(void)iter5;
	(void)iter6;
	(void)iter7;
	(void)iter8;
	
	(void)iter9;
	(void)iter10;
	(void)iter11;
	
	BSTRemove(iter2);
	
	BSTRemove(iter5);
	BSTRemove(iter8);
	
	BSTRemove(iter1);
	
	BSTDestroy(bst);
	
	
}

void TestRemoveShoshana()
{
	bst_t *my_tree = BSTCreate(&Compare);
	int x1 = 10;
	int x2 = 7;
	int x3 = 12;
	int x4 = 8;
	int x5 = 3;
	int x6 = 11;
	int x7 = 1;

	BSTInsert(my_tree, &x1);
	BSTInsert(my_tree, &x2);
	BSTInsert(my_tree, &x3);
	BSTInsert(my_tree, &x4);
	BSTInsert(my_tree, &x5);
	BSTInsert(my_tree, &x6);
	BSTInsert(my_tree, &x7);

	PrintTree(my_tree);

	printf("TREE SIZE IS %ld\n ", BSTSize(my_tree));

	BSTRemove(BSTFind(my_tree, &x2));
	PrintTree(my_tree);
	BSTRemove(BSTFind(my_tree, &x4));
	PrintTree(my_tree);

	printf("TREE SIZE IS %ld\n ", BSTSize(my_tree));
	
	BSTDestroy(my_tree);
}

static int Compare(const void *data1,const void *data2)
{
	return *(int *)data1 - *(int *)data2;
}

static int PrintEven(void *data, void *param)
{
	if (*(int *)data % *(int *)param == 0)
	{
		printf("%d ", *(int *)data);
	}
	
	return 0;
}

static void PrintTree(bst_t *tree)
{
	bst_iter_t runner = BSTBegin(tree);

	printf("tree: {");
	while (!BSTIterIsEqual(runner, BSTEnd(tree)))
	{
		printf("%d, ", *(int *)BSTGetData(runner));
		runner = BSTNext(runner);
	}
	printf("}\n");
}
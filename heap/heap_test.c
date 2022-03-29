/******************************************************************************
 ******************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          12/01/21                                                ***
 *** Reviewer:     David 			                                     	***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for heap data structure.                                ***
 ******************************************************************************
 \*****************************************************************************/


#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../include/heap.h"

static int Compare(const void *data1, const void *data2);
void TestCreate();
void TestPushPop();
void Test2();
void TestPop();
void TestInsert(void);

static int Compare1(const void *data1, const void *data2);
static int MatchFunc(const void *element, const void *param);

void TestUnit2N3();
void TestRemove();
void TestRemoveGal();
void PopTest3();
void RemoveTest3();

int main()
{
    /*
    TestUnit2N3();
    TestCreate();
    TestInsert();
    TestPushPop();
    Test2();
    TestPushPop();
    TestPop();
   
    TestRemove();
    */
   /*TestRemoveGal();*/
    /*TestRemoveGal();*/

   /*PopTest3();
   TestRemoveGal();
   */


    /*RemoveTest3();*/

    PopTest3();
   

    return 0;
}


void RemoveTest3()
{
    heap_t *heap = HeapCreate(&Compare);

    int x1 = 91;
    int x2 = 45;
    int x3 = 78;
    int x4 = 13;
    int x5 = 53;
    int x6 = 10;
    int x7 = 12;

    int not_exist = 200;

    HeapPush(heap, &x1);
    HeapPush(heap, &x2);
    HeapPush(heap, &x3);
    HeapPush(heap, &x4);
    HeapPush(heap, &x5);
    HeapPush(heap, &x6);
    HeapPush(heap, &x7);
    PrintVector(heap);

    printf("remove 10: \n");
    printf("should be 10: %d\n",*(int *)HeapRemove(heap,MatchFunc,&x6));
    PrintVector(heap);

    printf("remove 78: \n");
    printf("should be 78: %d\n",*(int *)HeapRemove(heap,MatchFunc,&x3));
    PrintVector(heap);
    assert(NULL == HeapRemove(heap,MatchFunc,&not_exist));

    printf("remove 45: \n");
    printf("should be 45: %d\n",*(int *)HeapRemove(heap,MatchFunc,&x2));
    PrintVector(heap);

    printf("remove 53: \n");
    printf("should be 53: %d\n",*(int *)HeapRemove(heap,MatchFunc,&x5));
    PrintVector(heap);

    printf("remove 91: \n");
    printf("should be 91: %d\n",*(int *)HeapRemove(heap,MatchFunc,&x1));
    PrintVector(heap);

    printf("remove 12: \n");
    printf("should be 12: %d\n",*(int *)HeapRemove(heap,MatchFunc,&x7));
    PrintVector(heap);

    printf("remove 13: \n");
    printf("should be 13: %d\n",*(int *)HeapRemove(heap,MatchFunc,&x4));
    PrintVector(heap);

    HeapDestroy(heap);
}



void PopTest3()
{
    heap_t *heap = HeapCreate(&Compare);
    int x1 = 0;
    int x2 = 1;
    int x3 = 3;
    int x4 = 7;
    int x5 = 2;
    int x6 = 4;
    int x7 = 5;
    int x8 = 9;
    int x9 = 10;
    int x10 = 15;
    int x11 = 6;

    size_t i = 0;

    HeapPush(heap, &x1);
    HeapPush(heap, &x2);
    HeapPush(heap, &x3);
    HeapPush(heap, &x4);
    HeapPush(heap, &x5);
    HeapPush(heap, &x6);
    HeapPush(heap, &x7);
    HeapPush(heap, &x8);
    HeapPush(heap, &x9);
    HeapPush(heap, &x10);
    HeapPush(heap, &x11);

    for (i = 0; i < 11; i++)
    {
       HeapPop(heap);
       PrintVector(heap);
    }
    

    HeapDestroy(heap);
}

void TestRemoveGal()
{	
	heap_t *heap = NULL;
	int vals[] = {91, 45, 78, 13, 53, 10, 12};
	size_t i = 0;

	heap = HeapCreate(Compare);
	assert(NULL != heap);
	assert(0 == HeapSize(heap));
	assert(HeapIsEmpty(heap));
	
	for(i = 0; i < 7; ++i)
	{		
		assert(i == HeapSize(heap));
		assert(0 == HeapPush(heap, vals + i));
	}
	assert(7 == HeapSize(heap));

	printf("\nHeapRemove Test status: ");
	for(i = 0; i < 7 ; ++i)
	{	
		assert(vals[i] == *(int *)HeapRemove(heap, MatchFunc, vals + i));
        printf("%d\n",*(int *)HeapRemove(heap, MatchFunc, vals + i));
	}
	assert(0 == HeapSize(heap));
	assert(HeapIsEmpty(heap));
	/*assert(NULL == HeapRemove(heap, IntIsEqual, vals));*/

    printf("PASSED\n");

	HeapDestroy(heap);
	heap = NULL;
}

void TestRemove()
{
    heap_t *heap = HeapCreate(&Compare);

    int x1 = 0;
    int x2 = 1;
    int x3 = 3;
    int x4 = 7;
    int x5 = 2;
    int x6 = 4;
    int x7 = 5;
    int x8 = 9;
    int x9 = 10;
    int x10 = 15;
    int x11 = 6;

    int x20 = 300;

    HeapPush(heap, &x1);
    HeapPush(heap, &x2);
    HeapPush(heap, &x3);
    HeapPush(heap, &x4);
    HeapPush(heap, &x5);
    HeapPush(heap, &x6);
    HeapPush(heap, &x7);
    HeapPush(heap, &x8);
    HeapPush(heap, &x9);
    HeapPush(heap, &x10);
    HeapPush(heap, &x11);

    printf("before remove 7:\n");
    PrintVector(heap);

    printf("after remove 7: \n");
    HeapRemove(heap,MatchFunc,&x4);
    PrintVector(heap);

    HeapDestroy(heap);
}

void TestUnit2N3()
{	
	heap_t *heap = NULL;
	int vals[] = {91, 45, 78, 13, 53, 10, 12};
	int ordered_vals[] = {10, 12, 13, 45, 53, 78, 91};
	size_t i = 0;

	heap = HeapCreate(Compare);
	assert(NULL != heap);
	assert(0 == HeapSize(heap));
	assert(HeapIsEmpty(heap));
	
	printf("\nHeapPush & HeapSize & HeapIsEmpty Test status: ");
	for(i = 0; i < 7; ++i)
	{		
		assert(i == HeapSize(heap));
		assert(0 == HeapPush(heap, vals + i));	
	}
	assert(7 == HeapSize(heap));
	assert(!HeapIsEmpty(heap));
     printf("PASSED\n");


    printf("\nHeapPop & HashPeek Test status: ");
	for(i = 0; i < 4 ; ++i)
	{		
		assert(ordered_vals[i] == *(int *)HeapPeek(heap));
		HeapPop(heap);	
	}
	assert(ordered_vals[4] == *(int *)HeapPeek(heap));
	assert(3 == HeapSize(heap));

    printf("PASSED\n");
	HeapDestroy(heap);
	heap = NULL;
}

void TestInsert(void)
{
    int array[] = {1,3,4,5,8,2};

    heap_t *new_heap = NULL;
    new_heap = HeapCreate(Compare);

    printf("heap size = %ld\n",HeapSize(new_heap));
    HeapPush(new_heap,&array[0]);
    printf("heap size = %ld\n",HeapSize(new_heap));
    HeapPush(new_heap,&array[1]);
    printf("heap size = %ld\n",HeapSize(new_heap));
    HeapPush(new_heap,&array[2]);
    printf("heap size = %ld\n",HeapSize(new_heap));
    HeapPush(new_heap,&array[3]);
    printf("heap size = %ld\n",HeapSize(new_heap));
    HeapPush(new_heap,&array[4]);
    printf("heap size = %ld\n",HeapSize(new_heap));
    PrintVector(new_heap);
    HeapPush(new_heap,&array[5]);
    printf("heap size = %ld\n",HeapSize(new_heap));
    PrintVector(new_heap);

    HeapDestroy(new_heap);

}


void TestPop()
{
    heap_t *heap = HeapCreate(&Compare);
    int x1 = 0;
    int x2 = 1;
    int x3 = 3;
    int x4 = 7;
    int x5 = 2;
    int x6 = 4;
    int x7 = 5;
    int x8 = 9;
    int x9 = 10;
    int x10 = 15;
    int x11 = 6;



    HeapPush(heap, &x1);
    HeapPush(heap, &x2);
    HeapPush(heap, &x3);
    HeapPush(heap, &x4);
    HeapPush(heap, &x5);
    HeapPush(heap, &x6);
    HeapPush(heap, &x7);
    HeapPush(heap, &x8);
    HeapPush(heap, &x9);
    HeapPush(heap, &x10);
    HeapPush(heap, &x11);

    printf("vector before poping: \n");
    PrintVector(heap);

    printf("heap after popping: \n");
    HeapPop(heap);
    PrintVector(heap);

    HeapDestroy(heap);


}

void Test2()
{
    heap_t *heap = HeapCreate(&Compare);
    int x1 = 6;
    int x2 = 7;
    int x3 = 8;
    int x4 = 5;
    int x5 = 2;
    int x6 = 1;
    HeapPush(heap, &x1);
    HeapPush(heap, &x2);
    HeapPush(heap, &x3);
    HeapPush(heap, &x4);
    HeapPush(heap, &x5);
    HeapPush(heap, &x6);
    PrintVector(heap);
    HeapDestroy(heap);
}

/*
void Test2()
{

    int x = 

    heap_t *heap = HeapCreate(&Compare1);
    char *x1 = "dhgfbdfghdfghdgfhjfgjfghjmhfjgm";
    char *x2 = "sdcnmsdkcmdfvmdfgibufngbifgnbifgbnufgnbifgnbfigbnfgiubnfigbnfigbnfigbnfigbnufgbn";
    char *x3 = "A";

    HeapPush(heap, x1);
    HeapPush(heap, x2);
    HeapPush(heap, x3);
 
    PrintVector(heap);

    HeapDestroy(heap);

}
*/

void TestCreate()
{
    heap_t * heap = HeapCreate(&Compare);

    assert(0 == HeapSize(heap));
    assert(1 == HeapIsEmpty(heap));

    HeapDestroy(heap);
}

void TestPushPop()
{
    heap_t * heap = HeapCreate(&Compare);

    int x1 = 0;
    int x2 = 1;
    int x3 = 3;
    int x4 = 7;
    int x5 = -7;
    int x6 = 20;
    int x7 = 4;
    int x8 = 9;
    int x9 = 10;
    int x10 = 15;
    int x11 = 6;
    int x12 = -10;
    

    HeapPush(heap,&x1);
    HeapPush(heap,&x2);
    HeapPush(heap,&x3);
    HeapPush(heap,&x4);
    HeapPush(heap,&x5);
    HeapPush(heap,&x6);
    HeapPush(heap,&x7);
    HeapPush(heap,&x8);
    HeapPush(heap,&x9);
    HeapPush(heap,&x10);
    HeapPush(heap,&x11);
    HeapPush(heap,&x12);

    printf("peek: %d\n",*(int *)HeapPeek(heap));

    

    

    /*
    
    HeapPush(heap,&x6);
    HeapPush(heap,&x7);
    HeapPush(heap,&x8);
    HeapPush(heap,&x9);
    HeapPush(heap,&x10);
    HeapPush(heap,&x11);
    */

    PrintVector(heap);

    HeapDestroy(heap);
}


static int Compare(const void *data1, const void *data2)
{
    return *(int *)data1 - *(int *)data2; 
}


static int Compare1(const void *data1, const void *data2)
{
    return strcmp((char *)data1,(char *)data2); 
}

 static int MatchFunc(const void *element, const void *param)
 {
     return *(int *)element == *(int *)param;
 }
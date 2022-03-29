#include <stdio.h>
#include <assert.h>

#include "../include/stack.h"

int main()
{
	
	/*
	stack_t *my_stack = StackCreate(10, 4);
    int num = 57;
    int *ptr = NULL;
    
    printf("-------------- test case 1 -----------\n");
    printf("size: %ld\n", StackSize(my_stack));
    assert(0 == StackSize(my_stack));
    printf("is empty?: %d\n", StackIsEmpty(my_stack));
    assert(1 == StackIsEmpty(my_stack));
    StackPush(my_stack, &num);
    printf("after push:\n");
    printf("size: %ld\n", StackSize(my_stack));
    assert(1 == StackSize(my_stack));
    printf("is empty?: %d\n", StackIsEmpty(my_stack));
    assert(0 == StackIsEmpty(my_stack));
    ptr = (int *)StackPeek(my_stack);
    printf("peek on the last element: %d\n", *ptr);
    assert(57 == *ptr);
    StackDestroy(my_stack);
    printf("SUCCESS\n");
    */
    
    
    
     stack_t *my_stack = StackCreate(10, 4);
    int x1 = 3;
    int x2 = -9;
    int x3 = 27;
    int *px1 = NULL;
    int *px2 = NULL;
    int *px3 = NULL;
    
    printf("-------------- test case 2 -----------\n");
    StackPush(my_stack, &x1);
    StackPush(my_stack, &x2);
    StackPush(my_stack, &x3);
    printf("size after pushes: %ld\n", StackSize(my_stack));
    assert(3 == StackSize(my_stack));
    px3 = (int *)StackPeek(my_stack);
    printf("peek on the last element: %d\n", *px3);
    assert(27 == *px3);
    StackPop(my_stack);
    printf("size after pop: %ld\n", StackSize(my_stack));
    assert(2 == StackSize(my_stack));
    px2 = (int *)StackPeek(my_stack);
    printf("peek on the last element: %d\n", *px2);
    assert(-9 == *px2);
    StackPop(my_stack);
    printf("size after pop: %ld\n", StackSize(my_stack));
    assert(1 == StackSize(my_stack));
    px1 = (int *)StackPeek(my_stack);
    printf("peek on the last element: %d\n", *px1);
    assert(3 == *px1);
    StackPop(my_stack);
    printf("size after pop: %ld\n", StackSize(my_stack));
    assert(0 == StackSize(my_stack));
    StackDestroy(my_stack);
    printf("SUCCESS\n");
	
	return 0;
}











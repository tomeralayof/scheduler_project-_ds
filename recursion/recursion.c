/**********************************\
* RECURSION                        *
* Developer: Tomer Alayof          *
* Written: 2021-1-25               *
*                                  *
* Reviewer:  Shaked Maman          *
\**********************************/

#include <assert.h> /*assert*/

#include "../include/recursion.h"

static void sortedInsert(stack_t *stack,int element);
static int RecStrNCmp(const char *s1, const char *s2, size_t n);

int RecFibonacci(int element_index)
{
	assert(element_index >= 0);

	if (element_index < 2)
	{
		return element_index;
	} 

	return RecFibonacci(element_index -1) + RecFibonacci(element_index -2);
}

int IterFibonacci(int element_index)
{
	int curr = 0;
	int next = 1;
	int i = 0;

	assert(element_index >= 0);

	for (i = element_index; i > 0; --i)
	{
		next += curr;
		curr = next - curr;
	}

	return curr;
}

size_t RecStrLen(const char *strq)
{
	assert(NULL != strq);

	if(*strq == '\0')
	{	
		return 0;
	}

	return  1 + RecStrLen(strq + 1);
}

int RecStrCmp(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);

	return RecStrNCmp(s1,s2 ,RecStrLen(s1));
}

char *RecStrCpy(char *dest, const char *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	*dest = *src;

	if(*(src) == '\0')
	{
		return NULL;
	}

	RecStrCpy(dest + 1,src + 1);

	return dest;
}

char *RecStrCat(char *dest, const char *src)
{
	assert(	NULL != dest);
	assert(NULL != src);

	RecStrCpy(dest + RecStrLen(dest),src);
	
	return dest;
}

node_t *RecFlipList(node_t *node)
{
	node_t *res = NULL;

	assert(NULL != node);

	if(node->next == NULL)
	{
		return node;
	}	

	res = RecFlipList(node->next);

	node->next->next = node;

	node->next = NULL;

   return res; 
}

void RecSort(stack_t *stack)
{
	int temp = 0;

	assert(NULL != stack);

	if(!StackIsEmpty(stack))
	{
		temp = *(int*)StackPeek(stack);
		StackPop(stack);
		RecSort(stack);
		sortedInsert(stack, temp);
	}
}

 char *RecStrStr(const char *haystack, const char *needle)
 {
 	assert(NULL != haystack);
 	assert(NULL != needle);

 	if(*(haystack) == '\0')
 	{
 		return NULL;
 	}

 	if(*(needle) == *(haystack) && 0 == RecStrNCmp(haystack,needle,RecStrLen(needle)))
 	{
 		return (char *)haystack;	
 	}

 	return RecStrStr(++haystack,needle);
 }

static int RecStrNCmp(const char *s1, const char *s2, size_t n)
{
	if (*s1 != *s2 || *s1 == '\0' || (n == 1))
	{
		return *s1 - *s2;
	}

	return RecStrNCmp(s1 + 1, s2 + 1,--n);
}

static void sortedInsert(stack_t *stack,int element)
{
	int temp = 0;

	assert(NULL != stack);

	if(StackIsEmpty(stack) || element > *(int*)StackPeek(stack))
	{
		StackPush(stack,&element);
		return;
	}

	temp = *(int*)StackPeek(stack);
	StackPop(stack);
	sortedInsert(stack,element);
	StackPush(stack,&temp);
}
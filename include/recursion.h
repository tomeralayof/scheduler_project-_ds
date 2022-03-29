/**********************************\
* RECURSION                        *
* Developer: Tomer Alayof          *
* Written: 2021-1-25               *
*                                  *
* Reviewer:  Shaked Maman          *
\**********************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h> /* size_t */

#include "stack.h"

typedef struct node
{
    void *data;
    struct node *next;
}node_t;

int RecFibonacci(int element_index);

int IterFibonacci(int element_index);

node_t *RecFlipList(node_t *node);

void RecSort(stack_t *stack);

size_t RecStrLen(const char *strq);

int RecStrCmp(const char *s1, const char *s2);

char *RecStrCpy(char *dest, const char *src);

char *RecStrCat(char *dest, const char *src);

 char *RecStrStr(const char *haystack, const char *needle);


#endif /* __RECURSION_H__ */
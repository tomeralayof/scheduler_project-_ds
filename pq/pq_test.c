#include <stdio.h>
#include <assert.h>

#include "../include/pq.h"

#define CASTING(type, var) (*(type *)&(var))

void CreateAndInsert();/*create,destroy,empty,size,insert*/
void ClearList(); /*clear,peek,deque*/

int SortIntIncreasingOrder(const void *left, const void *right);
int DoesIntMatch(const void *val1, void *val2);

int main()
{
	
	CreateAndInsert();

	
	return 0;
}

/*test -tomer*/
void CreateAndInsert()/*create,destroy,empty,size,insert*/
{

	pq_t *my_list = PQCreate(SortIntIncreasingOrder);
	
	int x1 = 7;
	int x2 = 3;
	int x3 = 12;
	int x4 = 1;

	assert(1 == PQIsEmpty(my_list));
	assert(0 == PQSize(my_list));	
	

	
	PQDestroy(my_list);
	
	printf("SUCCESS(create,destroy,empty,size,insert)!\n");
}

void ClearList() /*create,peek,deque,clear*/
{
	pq_t *my_list = PQCreate(SortIntIncreasingOrder);
	
	int x1 = 7;
	int x2 = 3;
	int x3 = 12;
	int x4 = 1;
	
	void *data = &x1;
	
	assert(1 == PQEnqueue(my_list, &x1));
	assert(1 == PQEnqueue(my_list, &x2));
	assert(1 == PQEnqueue(my_list, &x3));
	assert(1 == PQEnqueue(my_list, &x4));
	assert(4 == PQSize(my_list));

	PQClear(my_list);
	assert(0 == PQSize(my_list));	
	assert(1 == PQIsEmpty(my_list));
	
	assert(1 == PQEnqueue(my_list, &x1));
	assert(1 == PQEnqueue(my_list, &x2));
	assert(1 == PQEnqueue(my_list, &x3));
	assert(1 == PQEnqueue(my_list, &x4));
	
	assert( 1 == *(int *)PQPeek(my_list));
	
	
	assert(1 == *(int *)PQDequeue(my_list));	
	assert(3 == *(int *)PQDequeue(my_list));	
	assert( 2 == PQSize(my_list));
	
	
	PQErase(my_list,DoesIntMatch,data);
	assert(1 == PQSize(my_list));
	
	PQDestroy(my_list);
			
	printf("SUCCESS (peek,deque,clear,PQErase) !\n");

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


int DoesIntMatch(const void *val1, void *val2)
{
	return *(int *)val1 == *(int *)val2;
}














#include <assert.h>	/* assert() */
#include <stdio.h>	/* printf() */

#define CASTING(type, var) (*(type *)&(var))
#include "../include/queue.h"

void TestCase1();
void TestCase2();


int main()
{
	TestCase2();

	return 0;
}

void TestCase1()
{	
	queue_t *my_list = NULL;
	queue_t *my_list_2 = NULL;

	size_t val = 32;
	size_t val_2 = 53;
	size_t val_3 = 12;
	
	my_list = QueueCreate();
	assert(NULL != my_list);

	my_list_2 = QueueCreate();
	assert(NULL != my_list_2);


	assert(QueueIsEmpty(my_list));
	assert(QueueIsEmpty(my_list_2));

	assert(0 == QueueEnqueue(my_list, &val));
	assert(0 == QueueEnqueue(my_list_2, &val_2));

	assert(!QueueIsEmpty(my_list));
	assert(!QueueIsEmpty(my_list_2));

	assert(0 == QueueEnqueue(my_list_2, &val_3));

	assert(QueueSize(my_list_2) == (QueueSize(my_list) + 1));

	assert(*(size_t *)QueuePeek(my_list_2) == val_2);
	assert(*(size_t *)QueuePeek(my_list) == val);

	QueueDequeue(my_list_2);

	assert(QueueSize(my_list_2) == QueueSize(my_list));

	assert(*(size_t *)QueuePeek(my_list_2) == val_3);

	QueueAppend(my_list_2, my_list);

	assert(QueueSize(my_list_2) == 2);

	assert(QueueIsEmpty(my_list) == 1);

	QueueDestroy(my_list);
	QueueDestroy(my_list_2);

	printf("Test Status: PASSED\n");
}



void TestCase2()
{
	queue_t *my_queue = QueueCreate();
	int x = 6;
	int y = 7;
	int z = 8;
	void *xp = &x;
	void *yp = &y;
	void *zp = &z;
	printf("----------------Test 1------------------\n");
	printf("is empty before inserts? %d\n", QueueIsEmpty((queue_t *)my_queue));
	QueueEnqueue(my_queue, xp);
	QueueEnqueue(my_queue, yp);
	QueueEnqueue(my_queue, zp);
	printf("is empty after inserts? %d\n", QueueIsEmpty((queue_t *)my_queue));
	printf("queue size: %ld\n", QueueSize((queue_t *)my_queue));
	zp = QueuePeek((queue_t *)my_queue);
	QueueDequeue(my_queue);
	printf("queue peek element: %d\n", *CASTING(int *, zp));
	yp = QueuePeek((queue_t *)my_queue);
	QueueDequeue(my_queue);
	printf("queue peek element after deQueue: %d\n", *CASTING(int *, yp));
	xp = QueuePeek((queue_t *)my_queue);
	QueueDequeue(my_queue);
	printf("queue peek element after another deQueue: %d\n", *CASTING(int *, xp));
	/*printf("our queue: %d, %d, %d\n", *CASTING(int *, xp), *CASTING(int *, yp), *CASTING(int *, zp));*/
	QueueDestroy(my_queue);
}





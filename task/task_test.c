#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>


#include "../include/task.h"

void TestShai();
void TestTomer();
int PrintArr(void *arr_ptr);
void freePtr(void *cleanup_args);
void AdvancedTest();

#define CASTING(type, var) (*(type *)&(var))


int SimpleTaskAction(void *task_args)
{
    int i = 0;
    for(i = 0; i < *CASTING(int *, task_args); ++i)
    {
        printf("my task is to print this line task_args times!\n");
    }
    return 0;
}

void DoNothing(void *cleanup_args)
{
    (void)cleanup_args;
}


int main()
{
	

	TestTomer();
	AdvancedTest();
  	return 0;
}



void TestShai()
{
  	int times = 7;
    task_t *task2 = NULL;
    time_t current = time(NULL);
    time_t to_set = time(NULL) + 1000;
    task_t *task = TaskCreate(&SimpleTaskAction, &times, &DoNothing, &times, current);
    current = TaskGetTimeToRun(task);
    printf("task time to run: %ld\n", current);
    TaskSetTimeToRun(task, to_set);
    current = TaskGetTimeToRun(task);
    printf("task time to run after set +1000 seconds: %ld\n", current);
    assert(TaskIsMatch(task, TaskGetUID(task)));
    TaskRun(task);
    current = time(NULL);
    task2 = TaskCreate(&SimpleTaskAction, &times, &DoNothing, &times, current);
    printf("so... using taskcompare with new task output is: %d\n (should be 1000 of course)\n", TasksCompare(task, task2));
    TaskDestroy(task);
    TaskDestroy(task2);
    printf("SUCCESS\n");
  
}


void TestTomer()
{
	
	int times = 10;
	task_t *task1 = NULL;
	
	time_t current = time(NULL);
	time_t to_set = time(NULL) + 1000;
	
	task_t *task = TaskCreate(&SimpleTaskAction, &times,&DoNothing,&times,current);
	current = TaskGetTimeToRun(task);
	
	assert(TaskIsMatch(task, TaskGetUID(task)));
	assert(0 == TaskRun(task));
	
	TaskDestroy(task);
}



void AdvancedTest()
{

	int arr[11] = {0,1,2,3,4,5,6,7,8,9,10};	
	
	int *arr_ptr = malloc(sizeof(arr));
	
	time_t current = time(NULL);
	time_t current2 = time(NULL) + 1000;
	task_t *task2 = NULL;
	
	ilrd_uid_t id = UIDBadUID;
	
	task_t *task = TaskCreate(&PrintArr, arr_ptr,&freePtr,arr_ptr, current);
	assert(NULL != task);

	
	assert(NULL != task);
	
	assert(current == TaskGetTimeToRun(task));

	assert(0 == TaskRun(task));
	assert(NULL != task);
	
	assert(0 == TaskIsMatch(task,id));
	
	assert(1 == TaskIsMatch(task,TaskGetUID(task)));

	TaskDestroy(task);

	
}


int PrintArr(void *arr_ptr)
{
	int i = 0;
	
	for(i = 0; i < 11; ++i)
	{
		 *(((int *)arr_ptr) + i) = 10;
	}
	
	if( ((int *)arr_ptr) == NULL)
	{
		return 1;
	}
	
	for(i = 0; i < 11; ++i)
	{		
		printf("%d\n", (*(int *)arr_ptr));
	}
	
	return 0;
}


void freePtr(void *cleanup_args)
{
	
	free(cleanup_args);
	
}











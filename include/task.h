#ifndef __TASK_H__
#define __TASK_H__

#include <time.h>

#include "uid.h" 

typedef int (*task_func_t)(void *task_args);

typedef void (*cleanup_func_t)(void *cleanup_args);

typedef struct task task_t;

/*
* rational:
	- initialize the struct parameters 

* params:
	- task_func_t task_func : 		pointer to func to ve invoked	
	- void *task_args : 			argument for task_func
	- cleanup_func_t cleanup_func: 	free up memory
	- void *cleanup_args: 			argument for cleanup_func
	- time_t time_to_run 		
															
* return value:
	- pointer to the task struct. 
	- NULL in case of malloc failure
*/
task_t *TaskCreate(task_func_t task_func, void *task_args, cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run);

/*
* rational:
	- invoke to clean up function get from user
	- free the task
	
params:
	- task: pointer to task struct.
			
* return value:
	- no return	    		
*/
void TaskDestroy(task_t *task);

/*
* rational:
	- set a new time to run the function
	will be the absolute time of running (as per the previous time/new time of performance[APOCH])
	
* params: 
	- task_t *task
	- time_t time_to_run
		
*return value:
	- no return 	
*/
void TaskSetTimeToRun(task_t *task, time_t time_to_run); 

/*
* rational:
	- get the time when the function will be invoked
	
* params: 
	- task_t *task
		
*return value:
	- time function should be invoked	
*/
time_t TaskGetTimeToRun(const task_t *task);

/*
* rational:
	- get the user id for this task
	
* params: 
	- task_t *task
		
* return value:
	- user id	
*/
ilrd_uid_t TaskGetUID(task_t *task);

/*
* rational:	
	- compare between 2 times of 2 diffrent tasks
	
* params: 
	
	-const void *task_1
	-const void *task_2
			
* return value:
	
	- 0 if time is eqal
	- grater then 0 if time in task1 is grater
	- less then 0 if task1 is less then task2
*/
int TasksCompare(const void *task_1, const void *task_2);

/*
* rational:	
	- check wether the uid in the dask is equal to the uid created during creation time
	
* params: 	
	-const task_t *task
	-ilrd_uid_t uid
			
* return value:
	- 1 if ids are equal
	- 0 if id are not equal
*/
int TaskIsMatch(const task_t *task, ilrd_uid_t uid); 

/*
* rational:	
	-  invoke the function that was provided by the user
	
* params: 	
	-task_t *task
			
* return value:
	- 0 if the function was invoked successfully 
	- return error number if not invoked successfully
	 (returns the action_func return value)
*/
int TaskRun(task_t *task);

#endif /* __TASK_H__ */
















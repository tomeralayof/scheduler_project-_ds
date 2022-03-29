/******************************************************************************
 ******************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          28/12/21                                                ***
 *** Reviewer:     Dor Igler                                            	***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for scheduler project.                                  ***
 ******************************************************************************
\*****************************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <time.h> /*time*/

#include "task.h" /*task header*/
#include "pq.h" /* pq header */

typedef struct scheduler scheduler_t;


/*
*rational: 
	- create a new task manager by time priority
*params:
	- no params
*return:

	- pointer to scheduler in case of success
	- null in case in failure or creation		 
*/
scheduler_t *SchedCreate(void);

void SchedDestroy(scheduler_t *sched);

/*
*rational: 
	- create a new task manager by time priority	
* params:
	- task_func_t task_func : 		pointer to func to ve invoked
	- void *task_args : 			argument for task_func
	- cleanup_func_t cleanup_func: 	free up memory
	- void *cleanup_args: 			argument for cleanup_func
	- time_t time_to_run 		

return:
	- uid if success
	- bad uid if fail
*/
ilrd_uid_t SchedAddTask(scheduler_t *sched, task_func_t task_func, void *task_args,
						cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run);

/*
*rational:
	- remove task from scheduler if the task exist.
*params:
	- scheduler_t *sched
	- ilrd_uid_t uid
*return:
	- 0 if success to remove
	- -1 if couldnt remove
*/
int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid);

/*
*rational: 
	- run tasks by time priority, if its too early, the function go to a sleeping mood until the next task time.
*params:
	- scheduler_t *sched
*return:
	- status success in case of success
	- number of errror in case of an error
	- return less then 0 in case of invalid return from action function
*/
int SchedRun(scheduler_t *sched);


/*
*rational: 
	- stop the machine of executing tasks
*params:
	- scheduler_t *sched
*return:
	- no return
*/
void SchedStop(scheduler_t *sched);

/*
*rational: 
	-	check how many tasks the sched consist
*params:
	- scheduler_t *sched
*return:
	- number of tasks
*/
size_t SchedSize(const scheduler_t *sched);

/*
*rational: 
	-	check wether the  sched is empty from tasks or not.
*params:
	- scheduler_t *sched
*return:

	- 1 if the sched is empty
	- 0 if the sched is not empty 
*/
int SchedIsEmpty(const scheduler_t *sched);

/*
*rational: 
	-	clear all the tasks from the sched
*params:
	- scheduler_t *sched
*return:
	- no return value 
*/
void SchedClear(scheduler_t *sched);

#endif /* __SCHEDULER_H__ */
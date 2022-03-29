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

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <unistd.h> /* sleep */

#include "../include/scheduler.h" /*scheduler header file*/

/*function declerations*/

/*check uid with the task in order to remove*/
static int MatchTask( const void *task, void * uid); 

/*managing the task executions*/
static int RunCurrTask(int status ,scheduler_t *sched, task_t * task_runner);

enum run_mode_status
{
	OFF = 0,
	ON = 1	
};

enum status
{
	FAILURE = -1,
	SUCCESS = 0,
	PQFAILURE = 1
};

struct scheduler
{
	pq_t *pq_list;	
	int run_mode;	
};

scheduler_t *SchedCreate(void)
{
	scheduler_t *scheduler = (scheduler_t *)malloc(sizeof(scheduler_t)); 
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->pq_list = PQCreate(TasksCompare);
	if (NULL == scheduler->pq_list) 	
	{
		free(scheduler);
		scheduler = NULL;
	}
	
	scheduler->run_mode = ON;
	
	return scheduler;
}

void SchedDestroy(scheduler_t *sched)
{
	assert(NULL != sched);
	
	SchedClear(sched);
	
	PQDestroy(sched->pq_list);
	sched->pq_list = NULL;
	
	free(sched);
	sched = NULL;	
}

ilrd_uid_t SchedAddTask(scheduler_t *sched, task_func_t task_func, void *task_args, cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run)
{	
	task_t *new_task = NULL;
	
	assert(NULL != sched);
	assert(NULL != task_func);
	assert(NULL != cleanup_func);
	
	new_task = TaskCreate(task_func,task_args, cleanup_func, cleanup_args, time_to_run);
	if (NULL == new_task)
	{
		return UIDBadUID;
	}
	
	if (PQFAILURE == PQEnqueue(sched->pq_list, new_task))
	{
		 TaskDestroy(new_task);
		 new_task = NULL;
		 
		 return UIDBadUID;
	}
	
	return TaskGetUID(new_task);	
}

size_t SchedSize(const scheduler_t *sched)
{	
	assert(NULL != sched);

	return PQSize(sched->pq_list);
}

int SchedIsEmpty(const scheduler_t *sched)
{
	assert(NULL != sched);
	
	return PQIsEmpty(sched->pq_list);	
}

void SchedClear(scheduler_t *sched)
{
	task_t *task = NULL;
	
	assert(NULL != sched);
	
	while (!SchedIsEmpty(sched))
	{
		task = (task_t *)PQDequeue(sched->pq_list);
		TaskDestroy(task);
		task = NULL;
	}	
}

int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid)
{
	task_t *removed = NULL;
	int status = FAILURE;
	
	assert(NULL != sched);
	
	removed = (task_t *)PQErase(sched->pq_list, MatchTask , &uid);
	if (NULL != removed)
	{
		status = SUCCESS;
	}
	
	TaskDestroy(removed);
	removed = NULL;
	
	return status;
}

static int MatchTask(const void *task, void *uid)
{
	assert(NULL != task);

	return TaskIsMatch((const task_t *)task, *(ilrd_uid_t *)uid);
}

int SchedRun(scheduler_t *sched)
{	
	task_t *task_runner = NULL;	
	int status = SUCCESS;
	
	assert(NULL != sched);
	
	while (sched->run_mode == ON && status == SUCCESS && !SchedIsEmpty(sched))
	{	
		task_runner = (task_t *)PQPeek(sched->pq_list);		
		
		while (TaskGetTimeToRun(task_runner) > time(NULL))
		{
			sleep(TaskGetTimeToRun(task_runner) - time(NULL));
		}
			
		status = RunCurrTask(status,sched,task_runner);
	}
	
	return status;
}

static int RunCurrTask(int status ,scheduler_t *sched, task_t * task_runner)
{ 
	ilrd_uid_t uid = TaskGetUID(task_runner);
	int exit_status = TaskRun(task_runner);
	int time_to_continue = exit_status; 
	
	if(NULL != PQErase(sched->pq_list, MatchTask, &uid))
	{
		if (0 > exit_status)
		{	
			SchedClear(sched);	
			status = exit_status;
		}	
		else if (SUCCESS == exit_status)
		{
			TaskDestroy(task_runner);
		}		
		else
		{	
			TaskSetTimeToRun(task_runner, time(NULL) + time_to_continue);
			status = PQEnqueue(sched->pq_list, task_runner);
		}	
	}
			
	return status;
}

void SchedStop(scheduler_t *sched)
{	
	assert(NULL != sched);
	
	sched->run_mode = OFF;
}



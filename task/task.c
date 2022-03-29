#include <stdlib.h> /*malloc*/
#include <assert.h> /*include*/

#include "../include/task.h"

/*reviewed by shai*/

struct task
{
	task_func_t action; /*action func*/
	void *task_args;
	cleanup_func_t clean_up;
	void *cleanup_args;
	/*absolute time vs relative time*/
	time_t time_to_run;
	ilrd_uid_t id;
};

task_t *TaskCreate(task_func_t task_func, void *task_args, cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run)
{

	task_t * task = NULL;
	
	assert(NULL != task_func);
	assert(NULL != cleanup_func);
	
	task = (task_t *)malloc(sizeof(task_t));
	if(NULL == task)
	{
		return NULL;
	}
	
	task->action = task_func;
	task->task_args = task_args;
	task->clean_up = cleanup_func;	
	task->cleanup_args = cleanup_args;
	
	task->time_to_run = time_to_run;
	task->id = UIDCreate();
	if(UIDIsSame(task->id,UIDBadUID))
	{
		free(task);
		task = NULL;
		
		return NULL; /*better to leave null for mainainable issues(if i had another logic)*/
	}
	
	return task;
}

void TaskDestroy(task_t *task)
{

	assert(NULL != task);
	/*if task clean up not equal null execute*/
	task->clean_up(task->cleanup_args);
	free(task);
	task = NULL;
}


void TaskSetTimeToRun(task_t *task, time_t time_to_run)
{
	assert(NULL != task);
	
	task->time_to_run = time_to_run;
}


time_t TaskGetTimeToRun(const task_t *task)
{	
	assert(NULL != task);	
	
	return task->time_to_run;
}


ilrd_uid_t TaskGetUID(task_t *task)
{
    assert(NULL != task);

	return task->id;
}

int TasksCompare(const void *task_1, const void *task_2)
{
	
	assert(NULL != task_1);
	assert(NULL != task_2);
	
	return (((task_t *)task_1)->time_to_run - ((task_t *) task_2)-> time_to_run);
}


int TaskIsMatch(const task_t *task, ilrd_uid_t uid)
{
	assert(NULL != task);
	
    return UIDIsSame(task->id, uid);
} 

int TaskRun(task_t *task)
{
	assert(NULL != task);

	return task->action(task->task_args);
}












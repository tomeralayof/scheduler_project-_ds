/******************************************************************************
 ******************************************************************************
 *** Written by:    Tomer Alayof                                             ***
 *** Date:          28/12/21                                                ***
 *** Reviewer:     Dor Igler                                            	***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for scheduler project.                                     ***
 ******************************************************************************
 \*****************************************************************************/

#include <stdio.h> /*printf */
#include <unistd.h> /* sleep */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */


#include "../include/scheduler.h"

#define CASTING(type, var) (*(type *)&(var))

typedef struct memory_pointer
{
	void *ptr;
}memory_pointer_t;

typedef struct flag_ctrl
{
    scheduler_t *shared_sched;
    size_t flag_height;
    size_t shots_heard;
} flag_ctrl_t;

typedef struct self_ctrl
{
    scheduler_t *sched;
    ilrd_uid_t my_uid;
    size_t count;
} self_ctrl_t;

int TaskOneAction(void *task_args)
{
	printf("task 1: task_args value = %d\n", *CASTING(int *, task_args));
	return 4;
}

int TaskTwoAction(void *task_args)
{
	printf("task 2: (task_args) * 2 = %d\n", 2 * (*CASTING(int *, task_args)));
	return 0;
}

int TaskThreeAction(void *task_args)
{
	(void)task_args;
	printf("task 3:\nsegmentation fault (core dumped)\n");
	sleep(3);
	printf("stam stam everything working :)\n");
	return 0;
}

int TaskFourAction(void *task_args)
{
	(void)task_args;
	printf("task4: if you see this, your remove isnt working\n");
	return 0;
}

int TaskFiveAction(void *task_args)
{
	(void)task_args;
	printf("task 5: where is task 4? \n");
	return 0;
}

int TaskSixAction(void *task_args)
{
	(void)task_args;
	printf("task 6: dont worry, task 4 was removed :)\n");
	return 0;
}

int stop(void *task_args)
{	

	SchedStop(task_args);
		
	return 0;
}

void DoNothing(void *cleanup_args)
{
	(void)cleanup_args;
}

int PeriodicTask(void *task_args)
{
	static size_t counter = 0;
	(void)task_args;
	printf("I am a periodic task and i will come again in 10 seconds! (for 5 times)\n");
	++counter;
	return (counter > 4) ? 0 : 3;
}

int CheckWetherStopOrNot(void *task_args)
{
	FILE *fp;
	char buffer[4] = {0};
			
   fp = fopen("stop_me.txt","r");
   fread(buffer, 1 , 4, fp);
   
   if(strcmp(buffer,"stop") == 0)
   {
   		SchedStop(task_args);
   }
   
   fclose(fp);
	fp = NULL;
	
	return 3;
}

int SelfRemovingTask(void *args)
{
    self_ctrl_t *ctrl = (self_ctrl_t *) args;
    printf("removing myself:(\n");
    ++ctrl->count;
    SchedRemoveTask(ctrl->sched, ctrl->my_uid);
    return 1;
}

int SimpleUpdateFlagTask(void *args)
{
    ((flag_ctrl_t *) args)->flag_height = 1;
    return 0;
}

void TestRemovesItself()
{
    scheduler_t *test_sched = SchedCreate();
    self_ctrl_t *self_ctrl = (self_ctrl_t *)malloc(sizeof(self_ctrl_t)); 
    flag_ctrl_t *ctrl_flag = (flag_ctrl_t *) malloc(sizeof(flag_ctrl_t));
    ctrl_flag->flag_height = 0;
    ctrl_flag->shared_sched = test_sched;
    printf("-----------------------Test Gal (task that remove itself)-------------------------------\n");
    self_ctrl->sched = test_sched;
    self_ctrl->my_uid = SchedAddTask(test_sched, SelfRemovingTask, self_ctrl, DoNothing, NULL, time(NULL));
    SchedAddTask(test_sched, SimpleUpdateFlagTask, ctrl_flag, 
                            DoNothing, NULL, time(NULL));
    SchedAddTask(test_sched, SimpleUpdateFlagTask, ctrl_flag, 
                            DoNothing, NULL, time(NULL));
    SchedAddTask(test_sched, SimpleUpdateFlagTask, ctrl_flag, 
                            DoNothing, NULL, time(NULL));
    
    SchedRun(test_sched);

    free(self_ctrl);
    self_ctrl = NULL;
    free(ctrl_flag);
    ctrl_flag = NULL;
    SchedDestroy(test_sched);
    test_sched = NULL;
    printf("SUCCESS\n");
}



void TestWithStop()
{
	int x = 9;
	time_t now = time(NULL);
	scheduler_t *sched = SchedCreate();
	ilrd_uid_t uid4 = {0};
	
	
	printf("-----------------------Test With Stop-------------------------------\n");
	
	printf("is scheduler empty after create? %d\n", SchedIsEmpty(sched));
	SchedAddTask(sched, &TaskOneAction, &x, &DoNothing, &x, now);
	
	/*check if need to stop or not*/	
	SchedAddTask(sched, &CheckWetherStopOrNot, sched, &DoNothing, sched, now);
	
	SchedAddTask(sched, &TaskTwoAction, &x, &DoNothing, &x, now + 10);
	SchedAddTask(sched, &TaskThreeAction, &x, &DoNothing, &x, now + 15);
	uid4 = SchedAddTask(sched, &TaskFourAction, &x, &DoNothing, &x, now + 18);
	SchedAddTask(sched, &TaskFiveAction, &x, &DoNothing, &x, now + 20);
	SchedAddTask(sched, &TaskSixAction, &x, &DoNothing, &x, now + 25);
	
	printf("scheduler size after 6 adds is: %ld\n", SchedSize(sched));
	SchedRemoveTask(sched, uid4);
	printf("is scheduler empty after the adds? %d\n", SchedIsEmpty(sched));
	printf("starting execute tasks in 5 seconds: \n");
	sleep(5);
	
	SchedRun(sched);
	
	SchedDestroy(sched); 
}

void Test2()
{
	int x = 9;
	time_t now = time(NULL);
	scheduler_t *sched = SchedCreate();
	printf("-----------------------Test 2-------------------------------\n");
	SchedAddTask(sched, &PeriodicTask, &x, &DoNothing, &x, now);
	printf("starting execute tasks: \n");
	SchedRun(sched);
	SchedDestroy(sched);
}

static int TaskWithMalloc(void *action_args)
{
    memory_pointer_t *p = (memory_pointer_t *)action_args;
    char *s = (char *)malloc(10);

    strcpy(s, "dorigler");

    p->ptr = s;

    return 0;
}

static void CleanFunc(void *cleanup_args)
{
    memory_pointer_t *p = (memory_pointer_t *)cleanup_args;

    free(p->ptr);
    p->ptr = NULL;
}

void TestClearWithMalloc()
{
    memory_pointer_t my_ptr = {0};
    time_t current = time(NULL);

    scheduler_t *sched = SchedCreate();
    SchedAddTask(sched, &TaskWithMalloc, &my_ptr, &CleanFunc, &my_ptr, current);

    SchedClear(sched);
    assert(1 == SchedIsEmpty(sched));

    SchedDestroy(sched);
}

int main()
{

	/*
	TestWithStop();
	Test2();
	TestClearWithMalloc();
	*/
	TestWithStop();
	/*TestRemovesItself();*/
	return 0;
}
















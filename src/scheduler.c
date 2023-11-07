#include "common.h"
#include "scheduler.h"

/* add any global variables you like .. */

void init_scheduler()
{
    /* initalise them here */
}

/* prepare data for a new task
   the task should _NOT_ start out on the runqueue */
void task_started(struct sched_task *task, u64 pid, char *name)
{
}

/* clean up data associated with a task.
   The OS will not end a task that is on a runqueue */
void task_ended(struct sched_task *task)
{
}

/* A new task has become runnable,
   add it to the runqueue and return either
    DO_PREEMPT   - OS should call dequeue_next_task as soon as possible,
                   as there might be a new preferred task.
    DONT_PREEMPT - The currently running task can continue */
int enqueue_task(struct sched_task *task)
{
    return DONT_PREEMPT;
}

/* called when a new task should be selected to run.
   if the current task's time slice expired the scheduler
   will first enqueue before calling this function */
struct sched_task *dequeue_next_task()
{
    return NULL;
}

/* Called after dqeueue_next_task(),
   return how long this task should run for in microseconds */
long get_timeslice_length(struct sched_task *task)
{
    return 5 * 1000UL; /* 5 ms */
}
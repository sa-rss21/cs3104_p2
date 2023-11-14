#include "common.h"
#include "scheduler.h"



struct sched_task *head = NULL; // Linked list head




void print_state()
{
    printf("Scheduler State:\n");

    // Traverse the linked list of tasks and print information about each task
    struct sched_task *current = head;
    while (current != NULL)
    {
        printf("Task Name: %s\n", current->name);
        printf("Priority: %llu\n", current->priority);

        printf("\n");

        current = current->next;
    }
    printf("End of Scheduler State\n");
}

void init_scheduler()
{
    /* initalise them here */
    head = NULL;
}

/* prepare data for a new task
   the task should _NOT_ start out on the runqueue */
void task_started(struct sched_task *task, u64 pid, char *name)
{
    task->name = name;


    task->next = NULL; // Initialize the next pointer

    task->priority = get_task_prio(task);
}

/* clean up data associated with a task.
   The OS will not end a task that is on a runqueue */
void task_ended(struct sched_task *task)
{
    // Remove the task from the linked list
    if (head == task)
    {
        head = head->next;
    }
    else
    {
        struct sched_task *prev = head;
        while (prev->next != NULL && prev->next != task)
        {
            prev = prev->next;
        }
        if (prev->next != NULL)
        {
            prev->next = prev->next->next;
        }
    }
}

/* A new task has become runnable,
   add it to the runqueue and return either
    DO_PREEMPT   - OS should call dequeue_next_task as soon as possible,
                   as there might be a new preferred task.
    DONT_PREEMPT - The currently running task can continue */
int enqueue_task(struct sched_task *task)
{
    //print_state();
    // If the linked list is empty or the new task has the highest priority, make it the new head.
    if (head == NULL || task->priority < head->priority)
    {
        task->next = head;
        head = task;
    }
    else
    {
        struct sched_task *current = head;
        while (current->next != NULL && current->next->priority <= task->priority)
        {
            current = current->next;
        }
        task->next = current->next;
        current->next = task;
    }

    return DO_PREEMPT;
}

/* called when a new task should be selected to run.
   if the current task's time slice expired the scheduler
   will first enqueue before calling this function */
struct sched_task *dequeue_next_task()
{

    struct sched_task *next_task = head;

    if (head != NULL)
    {
        head = head->next;
        next_task->next = NULL;  // Disconnect the task from the linked list
    }

    return next_task;

}

/* Called after deueue_next_task(),
   return how long this task should run for in microseconds */
long get_timeslice_length(struct sched_task *task)
{
    return 0;
}

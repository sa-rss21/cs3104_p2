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
        printf("PID: %llu\n", current->pid);
   
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

    //calculate priority based on memory requirement using the PID
    
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
    // Add the task to the end of the linked list
    if (head == NULL)
    {
        head = task;
    }
    else
    {
        struct sched_task *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = task;
    }
    print_state();
    return DO_PREEMPT;
}

/* called when a new task should be selected to run.
   if the current task's time slice expired the scheduler
   will first enqueue before calling this function */
struct sched_task *dequeue_next_task()
{
    // Find and return the task with the highest priority
    struct sched_task *current = head;
    struct sched_task *next_task = NULL;
    int highest_priority = 100;

    while (current != NULL)
    {
        if (current->priority < highest_priority)
        {
            highest_priority = current->priority;
            next_task = current;
        }
        current = current->next;
    }

    if (next_task != NULL)
    {
        // Remove the selected task from the linked list
        if (head == next_task)
        {
            head = head->next;
        }
        else
        {
            struct sched_task *prev = head;
            while (prev->next != NULL && prev->next != next_task)
            {
                prev = prev->next;
            }
            if (prev->next != NULL)
            {
                prev->next = prev->next->next;
            }
        }
    }
    return next_task;    
}

/* Called after deueue_next_task(),
   return how long this task should run for in microseconds */
long get_timeslice_length(struct sched_task *task)
{
    return 5 * 1000UL; /* 5 ms */
}



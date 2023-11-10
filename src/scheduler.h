#pragma once

#define DONT_PREEMPT 0
#define DO_PREEMPT 1
#define SYS_OPEN 2
#define SYS_CLOSE 3
#define SYS_READ 0
#define O_RDONLY 0
struct sched_task
{
    u64 pid;
    char *name;
    int priority;
    struct sched_task *next; // Added a pointer to the next task for linked list
};

// Struct for the priority queue
struct priority_queue
{
    struct sched_task *head; // Pointer to the head of the linked list
};

/* see scheduler.c */

void init_scheduler();

void task_started(struct sched_task *task, u64 pid, char *name);

void task_ended(struct sched_task *task);

int enqueue_task(struct sched_task *task);

struct sched_task *dequeue_next_task();

long get_timeslice_length(struct sched_task *task);

void print_state();

int get_memory_usage(u64 pid);

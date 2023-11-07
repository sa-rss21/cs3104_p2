#pragma once
#define DONT_PREEMPT 0
#define DO_PREEMPT 1

struct sched_task
{
    /* add whatever you like here */
};

/* see scheduler.c */

void init_scheduler();

void task_started(struct sched_task *task, u64 pid, char *name);

void task_ended(struct sched_task *task);

int enqueue_task(struct sched_task *task);

struct sched_task *dequeue_next_task();

long get_timeslice_length(struct sched_task *task);
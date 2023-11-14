#include "common.h"
#include "scheduler.h"

struct thread *current_thread = NULL;
static u64 pid_counter = 1;
static struct thread *lst = NULL;

void dump_process_state()
{
    struct thread *task = lst;
    printf("<procs>\n");
    while (task) {
        printf("   PID %2d (%s %s) on_runqueue: %d\n",
        task->pid, task->name, task->arg, task->on_runqueue);
        task = task->nxt;
    }
    printf("</procs>\n");
}

void * _asmcall c_context_switch_1(struct thread *next_thread, void *old_stack) 
{
    if (current_thread) {
        current_thread->stack_ptr = old_stack;
    }
    
    return next_thread->stack_ptr;
}

void c_context_switch_2(struct thread *next_thread)
{
    struct thread *old_thread = current_thread;

    if (old_thread && old_thread->exiting) {

        printf("Freeing %ld %s\n", old_thread->pid, old_thread->arg);

        old_thread->magic = DEAD_THREAD_MAGIC;

        free_page(old_thread->kernel_stack_page);

        if (old_thread->memory_space)
            free_page(paddr(old_thread->memory_space));

        if (old_thread->memory_space)
            free(old_thread);

    	if (lst == NULL) {
        	shutdown();
    	}

    }

    current_thread = next_thread;
}

_naked void context_switch(struct thread *next_thread)
{
    /* Since the function is "naked", the top of the stack is a return address
     * to resume the original thread.
     *
     * When we switch to a thread, we load its stack and execute a retq to pop 
     * this return address.
     */
    asm volatile(SYSV_SAVE_REGS

                 "mov %rsp, %rsi             ;"
                 "pushq %rdi                 ;"
                 "callq c_context_switch_1   ;"

                 "popq %rdi                  ;"
                 "mov %rax, %rsp             ;"
                 "callq c_context_switch_2   ;"

                 SYSV_RESTORE_REGS
                 "retq                       ;");
}


void _asmcall c_thread_start(threadfn func, void *arg)
{
    func(arg);
    exit_thread();
}

static void _naked thread_start()
{
    asm("pop %rsi ; pop %rdi ; callq c_thread_start");
}


u64 thread_init(struct thread *thread, threadfn func, void *arg)
{
    u64   page   = get_free_page(0xAB);
    u64  *stack  = kern_vaddr(page + PAGE_SIZE);

    /* boot args */
    push_stack_64(&stack, (u64) func);
    push_stack_64(&stack, (u64) arg);

    /* return addr */
    push_stack_64(&stack, (u64) thread_start);
    
    for (int i = 0; i < NUM_SYSV_SAVE_REGS; i++)
        push_stack_64(&stack, 0x0);

    memset(thread, 0x0, sizeof(struct thread));
    thread->stack_ptr = stack;
    thread->pid = pid_counter++;

    thread->nxt = lst;
    if (lst)
        lst->prev = thread;
    lst = thread;

    thread->magic = THREAD_MAGIC;
    thread->kernel_stack_page = page;

    return thread->pid;
}

struct thread *find_thread(u64 pid)
{
    struct thread *ptr = lst;
    while (ptr) {
        if (ptr->pid == pid)
            return ptr;
        ptr = ptr->nxt;
    }

    return NULL;
}

void exit_thread()
{   
    log_header();
    printf("thread stopped\n");
    task_ended(&current_thread->sched_handle);
    wake_all(&current_thread->death_waiters);

    if (current_thread->nxt)
        current_thread->nxt->prev = current_thread->prev;

    if (current_thread->prev)
        current_thread->prev->nxt = current_thread->nxt;

    if (lst == current_thread)
        lst = current_thread->nxt;

    current_thread->exiting = 1;
    schedule_now(0x0);
}

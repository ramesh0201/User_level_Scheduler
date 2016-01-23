/*
Ramesh Kumar Thangarajan
*/

#include <ucontext.h>
#include <string.h>

struct TCB {
	ucontext_t context;
	struct TCB *prev;
	struct TCB *next;
};
typedef struct TCB TCB_t;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));       
    getcontext(&tcb->context);              
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);
}

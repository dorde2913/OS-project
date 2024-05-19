#include "../h/syscall_c.h"
#include "../lib/console.h"
void sys_call()
{
    __asm__ volatile("ecall");
}

//U a0 REGISTAR IDE SYSCALL_CODE
//U a1,a2... PARAMETRI SYSCALL

//NAKON ECALL, POVRATNA VREDNOST U a0
void* mem_alloc (size_t size)
{

    __asm__ volatile("mv a1, %0" : : "r" ((uint64)size));
    __asm__ volatile("mv a0, %0" : : "r" (MALLOC_CODE));


    sys_call();

    void* ret;
    __asm__ volatile("mv %0, a0": "=r" (ret));
    return ret;
}
int mem_free(void* adr)
{
    __asm__ volatile("mv a1, %0" : : "r" (adr));
    __asm__ volatile("mv a0, %0" : : "r" (MEMFREE_CODE));


    sys_call();

    int ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg)
{

    //void* stack_space=kernel::Memory_allocator::mem_alloc(DEFAULT_STACK_SIZE);
    void* stack_space = mem_alloc(DEFAULT_STACK_SIZE);
    __asm__ volatile("mv a4, %0" : : "r" (stack_space));
    __asm__ volatile("mv a3, %0" : : "r" (arg));
    __asm__ volatile("mv a2, %0" : : "r" (start_routine));
    __asm__ volatile("mv a1, %0" : : "r" (handle));
    __asm__ volatile("mv a0, %0" : : "r" (THREADCREATE_CODE));


    sys_call();

    int ret=*handle?0:-1;;


    return ret;
}
int thread_exit()
{
    __asm__ volatile("mv a0, %0" : : "r" (THREADEXIT_CODE));

    sys_call();

    int ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
void thread_dispatch()
{
    __asm__ volatile("mv a0, %0" : : "r" (THREADDISPATCH_CODE));

    sys_call();

    //uint64 ra;
    //__asm__ volatile ("mv %0,ra":"=r"(ra));
    //printInt(ra);
    //putc('\n');

}
void thread_join(thread_t handle)
{
    __asm__ volatile("mv a1, %0" : : "r"(handle));
    __asm__ volatile("mv a0, %0" : : "r" (THREADJOIN_CODE));


    sys_call();
}
int sem_open(sem_t* handle, unsigned init)
{
    __asm__ volatile("mv a2, %0" : : "r" (init));
    __asm__ volatile("mv a1, %0" : : "r"(handle));
    __asm__ volatile("mv a0, %0" : : "r" (SEMOPEN_CODE));



    sys_call();

    int ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
int sem_wait(sem_t id)
{
    __asm__ volatile("mv a1, %0" : : "r"(id));
    __asm__ volatile("mv a0, %0" : : "r" (SEMWAIT_CODE));

    sys_call();

    int ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
int sem_signal(sem_t id)
{
    __asm__ volatile("mv a1, %0" : : "r"(id));
    __asm__ volatile("mv a0, %0" : : "r" (SEMSIGNAL_CODE));

    sys_call();

    int ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
int sem_close(sem_t id)
{
    __asm__ volatile("mv a1, %0" : : "r"(id));
    __asm__ volatile("mv a0, %0" : : "r" (SEMCLOSE_CODE));

    sys_call();

    int ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
int time_sleep(time_t t)
{
    __asm__ volatile("mv a1, %0" : : "r"(t));
    __asm__ volatile("mv a0, %0" : : "r" (TIMESLEEP_CODE));

    sys_call();

    int ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
char getc()
{
    __asm__ volatile("mv a0, %0" : : "r" (GETC_CODE));
    sys_call();
    char ret;
    __asm__ volatile("mv %0, a0": "=r"(ret));
    return ret;
}
void putc(char c)
{
    __asm__ volatile("mv a1, %0" : : "r"(c));
    __asm__ volatile("mv a0, %0" : : "r" (PUTC_CODE));

    sys_call();
}
void userMod() {
    __asm__ volatile("mv a0, %0" : : "r" (MUSER_CODE));

    sys_call();
}

void supervisorMod() {
    __asm__ volatile("mv a0, %0" : : "r" (MSUPERVISOR_CODE));

    sys_call();
}



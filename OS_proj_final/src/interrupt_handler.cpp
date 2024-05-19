#include "../h/Memory_allocator.hpp"
#include "../h/syscall_c.h"
#include "../h/Riscv.hpp"
#include "../lib/console.h"
#include "../h/PCB.hpp"
#include "../lib/hw.h"
#include "../h/K_semaphore.hpp"
extern "C" void handle_interrupt()
{
    uint64 code;
    uint64 arg1;
    uint64 arg2;
    uint64 arg3;
    uint64 arg4;

    __asm__ volatile("mv %0, a0": "=r"(code));
    __asm__ volatile("mv %0, a1": "=r"(arg1));
    __asm__ volatile("mv %0, a2": "=r"(arg2));
    __asm__ volatile("mv %0, a3": "=r"(arg3));
    __asm__ volatile("mv %0, a4": "=r"(arg4));
    //uint64 status=Riscv::get_sstatus();
    uint64 cause=Riscv::get_scause();

    if (cause==8 || cause==9) {


        __asm__ volatile("csrr x5,sepc");
        __asm__ volatile("addi x5,x5,4");
        __asm__ volatile("csrw sepc,x5");



        uint64 sepc = Riscv::get_sepc();

        if (code==GETC_CODE)
        {
            __asm__ volatile("csrc sip, 0x02");
            //__asm__ volatile ("csrs sstatus, 0x02");//enable spoljasnji
            __asm__ volatile ("csrc sie,0x02");
        }


        void* ret=nullptr;

        if (code == MALLOC_CODE) {
            size_t size = (size_t)arg1;
            size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 );
            ret = kernel::Memory_allocator::mem_alloc(size);
            __asm__ volatile("mv a0, %0": :"r"(ret));
        }


        else if (code == MEMFREE_CODE) {
            kernel::Memory_allocator::mem_free((void *) arg1);
        }


        else if (code == THREADCREATE_CODE) {
            thread_t* handle = (thread_t*) arg1;
            *handle = kernel::PCB::create_PCB((void (*)(void *)) arg2, (void *) arg3, (void *) arg4);


            __asm__ volatile ("mv a0, %0": :"r"(handle));//upisivanje new_thread u a0

        }

        else if (code == THREADDISPATCH_CODE) {
            //uint64 sepc2 = Riscv::get_sepc();
            kernel::PCB::yield();
            //Riscv::set_sepc(sepc2);

        }

        else if (code == THREADEXIT_CODE) {
            int a = 0;
            kernel::PCB::running->set_finished(true);
            kernel::PCB::yield();
            __asm__ volatile ("mv a0,%0"::"r"(a));
        }

        else if (code == THREADJOIN_CODE) {
            kernel::PCB *handle = (kernel::PCB *) arg1;
            kernel::PCB::running->join(handle);
        }

        else if (code == SEMOPEN_CODE) {
            //arg1 je handle, arg2 je init
            sem_t* semaphore = (sem_t*)arg1;
            *semaphore = K_semaphore::create_sem(arg2);

            int retint;
            if (*semaphore==nullptr)retint = -1;
            else retint = 0;
            __asm__ volatile ("mv a0,%0"::"r"(retint));


        }
        else if (code == SEMCLOSE_CODE)
        {
          K_semaphore* sem = (K_semaphore*)arg1;
          K_semaphore::deactivate_sem(sem);
          K_semaphore::delete_sem(sem);


          int retint=0;
          __asm__ volatile ("mv a0,%0"::"r"(retint));

        }
        else if (code==SEMSIGNAL_CODE)
        {
            K_semaphore* sem = (K_semaphore*)arg1;
            int retint=-1;
            if (sem->is_active())
            {
                sem->signal();
                retint=0;
            }



            __asm__ volatile ("mv a0,%0"::"r"(retint));
        }
        else if (code == SEMWAIT_CODE)
        {

            K_semaphore* sem = (K_semaphore*)arg1;
            int retint=-1;
            if (sem->is_active())
            {
                sem->wait();
                retint=0;
            }
            if (!sem->is_active())
            {
                retint=-1;
            }


            __asm__ volatile ("mv a0,%0"::"r"(retint));

        }
        else if (code == GETC_CODE)
        {

            char c = __getc();
            __asm__ volatile ("mv a0,%0": : "r"(c));
            Riscv::set_sepc(sepc);
        }
        else if (code==PUTC_CODE)
        {

            __putc((char)arg1);
            Riscv::set_sepc(sepc);

        }
        else if (code==MUSER_CODE)
        {
            uint64 mask = 1<<8;
            __asm__ volatile ("csrc sstatus, %0"::"r"(mask));
        }
        else if (code == MSUPERVISOR_CODE)
        {
            uint64 mask = 1<<8;
            __asm__ volatile ("csrs sstatus, %0"::"r"(mask));
        }

       // Riscv::set_sepc(sepc);
    }
    /*
    else if (cause==(1UL<<63|9))
    {
        console_handler();
    }
    */
    else if (cause==(1UL<<63|1))
    {

    }
    else
    {
        printInt(cause);
        __putc('\n');
    }

}
extern "C" void handle_h_interrupt()
{
    console_handler();
}




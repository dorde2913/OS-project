#include "../lib/console.h"
#include "../h/Memory_allocator.hpp"
#include "../h/syscall_c.h"
#include "../test/printing.hpp"
#include "../h/syscall_cpp.hpp"
#include "../h/K_semaphore.hpp"
extern "C" void interrupt();
//ovde treba da se napravi nit nad UserMain i ta nit da se pokrene


//sem_t semafor ;

void test_funkcija(void* args )
{
    //semafor->wait();
    printString("TEST FUNKCIJA \n");

}


int main() {

    uint64 mask = 1;

    __asm__ volatile("csrw stvec, %0"::"r"(interrupt));
    __asm__ volatile ("csrs stvec, %0"::"r"(mask));

    /*
    thread_t kernel_thread;
    thread_create(&kernel_thread,nullptr,nullptr);
    kernel::PCB::running=kernel_thread;

    thread_t test_nit;
    thread_create(&test_nit,test_funkcija, nullptr);

    thread_dispatch();

    delete test_nit;

   */


    thread_t kernel_thread;
    thread_create(&kernel_thread,nullptr,nullptr);


    kernel::PCB::running=kernel_thread;


    thread_t nit;
    thread_create(&nit,kernel::PCB::userMainWrapper,nullptr);




    while (!nit->is_finished())
    {
        thread_dispatch();
    }


    return 0;

}

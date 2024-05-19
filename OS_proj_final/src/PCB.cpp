//
// Created by os on 5/22/23.
//

#include "../h/PCB.hpp"

int kernel::PCB::ID=0;
kernel::PCB* kernel::PCB::running=nullptr;
void* kernel::PCB::operator new(size_t size) {
    size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 );
    //if (size<MEM_BLOCK_SIZE)size=MEM_BLOCK_SIZE;
    return kernel::Memory_allocator::mem_alloc(size);
}
void* kernel::PCB::operator new[](size_t size) {
    size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 );
    //if (size<MEM_BLOCK_SIZE)size=MEM_BLOCK_SIZE;
    return kernel::Memory_allocator::mem_alloc(size);
}
void kernel::PCB::operator delete(void *p)noexcept {
    kernel::Memory_allocator::mem_free(p);
}
void kernel::PCB::operator delete[](void *p)noexcept {
    kernel::Memory_allocator::mem_free(p);
}
kernel::PCB *kernel::PCB::create_PCB(void (*start_routine)(void *), void *arg, void *stack) {
    kernel::PCB* pcb=new kernel::PCB(start_routine,arg,stack);
    if (pcb->body!=nullptr)
    {
        Scheduler::put(pcb);
    }

    return pcb;
}
kernel::PCB::~PCB()
{
    if (this->stack)
    {
        kernel::Memory_allocator::mem_free(this->stack);
    }

}
void kernel::PCB::context_switch(Context* old_context,Context* new_context)
{
    if (old_context==nullptr || new_context==nullptr)
    {
        putc('G');
        putc('\n');
    }
    __asm__ volatile("sd ra,0*8(a0)");
    __asm__ volatile("sd sp,1*8(a0)");

    __asm__ volatile("ld ra,0*8(a1)");
    __asm__ volatile("ld sp,1*8(a1)");
}
void kernel::PCB::dispatch()
{
    kernel::PCB* old=running;
    if (old)
    {
        if (!old->is_finished() && !old->is_blocked()){kernel::Scheduler::put(old);}
    }


    running = kernel::Scheduler::get();

    //if (running->body==nullptr)supervisorMod();
    //else userMod();


    PCB::context_switch(&old->context,&running->context);



}
void kernel::PCB::yield() {

    Riscv::save_registers();

    kernel::PCB::dispatch();

    //supervisorMod();

    Riscv::restore_registers();

}

void kernel::PCB::join(kernel::PCB *handle) {
    while (!handle->is_finished())
    {
        kernel::PCB::dispatch();
    }
}
void kernel::PCB::body_wrapper(void *bbb) {
    if (running->body==nullptr)supervisorMod();
    else userMod();

    running->body(running->arg);
    //supervisorMod();
    thread_exit();
    //running->set_finished(true);
    //dispatch();
}

void kernel::PCB::userMainWrapper(void* arg) {
    userMain();
    supervisorMod();
}
/*
void idle(void* arg) {
    while(true)
        thread_dispatch();
}
*/


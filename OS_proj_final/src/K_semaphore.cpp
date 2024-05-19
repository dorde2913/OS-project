//
// Created by os on 7/25/23.
//
#include "../h/K_semaphore.hpp"

void K_semaphore::block () {
    blocked.push_back(kernel::PCB::running);
    kernel::PCB::running->set_blocked(true);
    kernel::PCB::yield();

}
void K_semaphore::unblock () {
    kernel::PCB* t = blocked.pop_front();
    if (t)
    {
        t->set_blocked(false);
        kernel::Scheduler::put(t);
    }


}
void K_semaphore::wait () {

    if (--val<0) block();
}
void K_semaphore::signal () {

    if (++val<=0) unblock();
}
K_semaphore* K_semaphore::create_sem(uint32 init) {
    return new K_semaphore(init);
}

void *K_semaphore::operator new(size_t size)  {
    size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 );
    //if (size<MEM_BLOCK_SIZE)size=MEM_BLOCK_SIZE; //pretvaranje u blokove
    return kernel::Memory_allocator::mem_alloc(size);
}

void *K_semaphore::operator new[](size_t size)  {
    size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 );
    //if (size<MEM_BLOCK_SIZE)size=MEM_BLOCK_SIZE;
    return kernel::Memory_allocator::mem_alloc(size);
}

void K_semaphore::operator delete(void *p) noexcept  { kernel::Memory_allocator::mem_free(p); }

void K_semaphore::operator delete[](void *p) noexcept  { kernel::Memory_allocator::mem_free(p); }
void K_semaphore::delete_sem(K_semaphore* handle) {

    delete handle;
}
int K_semaphore::deactivate_sem(K_semaphore* handle) {
   if(!handle->is_active())return -1;
   handle->set_active(false);

   int queue_size = handle->blocked.size();
   for (int i=0;i<queue_size;i++)
   {
       kernel::PCB* pcb = handle->blocked.pop_front();
       pcb->set_blocked(false);
       kernel::Scheduler::put(pcb);
   }
   return 0;
}
#include "../h/Memory_allocator.hpp"

kernel::Memory_allocator::free_mem *kernel::Memory_allocator::head=nullptr;

bool kernel::Memory_allocator::is_initialized=false;
void *kernel::Memory_allocator::mem_alloc(size_t size) {

    //size_t alloc_size=(size+1)*(MEM_BLOCK_SIZE);
    //return __mem_alloc(alloc_size);

    if (!is_initialized)
    {
        initialize();
    }

    if (!head)return nullptr;
    if (size<=0) return nullptr;

    size_t alloc_size=(size+1)*(MEM_BLOCK_SIZE);//broj bajtova

    free_mem* curr=head;
    while (curr)
    {
        if (curr->size>=alloc_size) break;//NASLI SEGMENT
    }
    if (!curr) return nullptr; //NEMA PROSTORA


    size_t remaining_size=curr->size-alloc_size;
    curr->size=alloc_size;//vracamo curr





    free_mem* remaining_block=(free_mem*)((size_t)curr+alloc_size);
    remaining_block->size=remaining_size;


    remove_free(curr);
    add_free(remaining_block);



    return (void*)((size_t)curr+MEM_BLOCK_SIZE);

}

int kernel::Memory_allocator::mem_free(void *adr) {

    //return __mem_free(adr);
    free_mem* segment = (free_mem*)((size_t)adr-MEM_BLOCK_SIZE);
    add_free(segment);

    return 0;

}





void kernel::Memory_allocator::initialize() {

    head=(free_mem*)HEAP_START_ADDR;

    head->size= (((size_t)HEAP_END_ADDR-(size_t)HEAP_START_ADDR)/MEM_BLOCK_SIZE-1)*MEM_BLOCK_SIZE;
    head->next=nullptr;

    is_initialized=true;

}
void kernel::Memory_allocator::add_free(free_mem *segment) {
    free_mem* curr = head;
    free_mem* prev = nullptr;
    if (!curr){//empty
        head=segment;
        return;
    }
    if (segment<head)
    {
        segment->next=head;
        head=segment;
        if (head+head->size==head->next)//spajanje segmenata
        {
            head->size+=head->next->size;
            head->next=head->next->next;
        }
        return;
    }
    while (curr<segment && curr!= nullptr)
    {
        prev=curr;
        curr=curr->next;
    }
    if (!curr)
    {
        prev->next=segment;
        if (prev+prev->size==segment)//spajanje segmenata
        {
            prev->size+=segment->size;
            prev->next=nullptr;
        }
        return;
    }
    prev->next=segment;
    segment->next=curr;
    if (prev+prev->size==segment)//spajanje segmenata
    {
        prev->size+=segment->size;
        prev->next=curr;
        segment=nullptr;
    }
    if (!segment)//spojeni prev i segment
    {
        if (prev+prev->size==curr)
        {
            prev->size+=curr->size;
            prev->next=curr->next;
        }
    }
    else//nisu spojeni prev i segment, pokusavamo segment i curr
    {
        if (segment+segment->size==curr)
        {
            segment->size+=curr->size;
            segment->next=curr->next;
        }

    }


}
void kernel::Memory_allocator::remove_free(free_mem* segment) {
    free_mem* curr = head;
    free_mem* prev =nullptr;
    while (curr!=segment)
    {
        prev=curr;
        curr=curr->next;
    }
    if (!curr)return;//greska
    if (!prev)//remove head
    {
        head=nullptr;
        return;
    }
    prev->next=curr->next;
    curr->next=nullptr;


}

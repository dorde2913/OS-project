#ifndef MEMORY_ALLOCATOR_HPP
#define MEMORY_ALLOCATOR_HPP
#include "../lib/hw.h"


namespace kernel {
    class Memory_allocator{
    public:

        struct free_mem{
            size_t size;
            free_mem* next=nullptr;
        };

    private:
        static free_mem* head;

        static bool is_initialized;

        static void add_free(free_mem* segment);
        static void remove_free(free_mem* segment);

    public:
        static void initialize();

        Memory_allocator(const Memory_allocator& )=delete;
        Memory_allocator& operator=(const Memory_allocator& )=delete;
        static void* mem_alloc (size_t size);
        static int mem_free (void* adr);

    };
}

#endif //PROJECT_BASE_MEMORY_ALLOCATOR_HPP

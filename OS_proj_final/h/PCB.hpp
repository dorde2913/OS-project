#ifndef PROJECT_BASE_PCB_HPP
#define PROJECT_BASE_PCB_HPP

#include "../h/Memory_allocator.hpp"
#include "../h/Riscv.hpp"
#include "../h/Scheduler.hpp"
#include "../h/syscall_c.h"
extern void userMain();
namespace kernel
{

    class PCB {

        uint64 time_slice=DEFAULT_TIME_SLICE;
    public:
        struct Context{
            uint64 ra;
            uint64 sp;
        };
        using Body= void(*)(void*);
        explicit PCB(Body b,void* arg,void* stack)
        {
            this->body=b;
            this->arg=arg;
            this->stack=(void*) ((uint64)stack+DEFAULT_STACK_SIZE-1);

            this->context.ra=(uint64)&body_wrapper;
            this->context.sp=(uint64)this->stack;
            while (this->context.sp%16!=0)
            {
                this->context.sp--;
            }
            //if (body!=nullptr) kernel::Scheduler::put(this);

            //stek raste na dole pa treba da u sp metnemo zadnju alociranu lokaciju
        }
        ~PCB();
        static PCB* create_PCB(void(*start_routine)(void*),void* arg,void* stack);
        static void dispatch();
        static PCB* running;//current pcb
        static void yield();//promena konteksta

        static void body_wrapper(void* bbb);



        const int get_id(){return id;}
        bool is_finished(){return finished;}
        bool is_blocked(){return blocked;}
        void set_finished(bool value){finished=value;}
        void set_blocked(bool value){blocked=value;}

        //test metoda
        void set_running()
        {
            running=this;
        }
        static void switch_context(Context* old_context,Context* new_context)
        {
            context_switch(old_context,new_context);
        }
        Context context;
        Body body;
    private:
        static void context_switch(Context* old_context,Context* new_context);


        //funkcija nad kojom radi nit
        void* arg; //argumenti te funkcije
        bool finished=false;
        bool blocked=false;




        void* stack;//pocetna adresa steka






    public:
        static void userMainWrapper(void* arg);
        void join(PCB* handle);
        void *operator new(size_t size);
        void *operator new[](size_t size);
        void operator delete(void *p) noexcept;
        void operator delete[](void *p) noexcept;
    private:
        static int ID;
        int id=ID++;

    };
    void idle(void* arg);


}



#endif //PROJECT_BASE_PCB_HPP

#ifndef PROJECT_BASE_SCHEDULER_HPP
#define PROJECT_BASE_SCHEDULER_HPP
#include "../h/list.hpp"


namespace kernel{

    class PCB;

    class Scheduler{

        static List<kernel::PCB> pcb_list;


        public:

        static void put(kernel::PCB* p);
        static kernel::PCB* get();
        static bool empty();

        //TEST
        static List<kernel::PCB>& get_list(){return pcb_list;}
    };
}



#endif //PROJECT_BASE_SCHEDULER_HPP

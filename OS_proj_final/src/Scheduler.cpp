#include "../h/Scheduler.hpp"

List<kernel::PCB> kernel::Scheduler::pcb_list;

void kernel::Scheduler::put(kernel::PCB* p){

    pcb_list.push_back(p);

}
kernel::PCB* kernel::Scheduler::get() {
    kernel::PCB* ret = pcb_list.pop_front();
    return ret;
}
bool kernel::Scheduler::empty() {
    return pcb_list.size() == 0;
}

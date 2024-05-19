//
// Created by os on 7/25/23.
//

#ifndef PROJECT_BASE_SEMAPHORE_HPP
#define PROJECT_BASE_SEMAPHORE_HPP
#include "../h/list.hpp"
#include "../h/PCB.hpp"
class K_semaphore {
public:
    K_semaphore (unsigned short init=1) : val(init) {}
    void wait ();
    void signal ();
    int value () const { return val; }
    static K_semaphore* create_sem(uint32 init);

    static int deactivate_sem(K_semaphore* handle);
    static void delete_sem(K_semaphore* handle);

    bool is_active(){return active;}
    void set_active(bool a){active=a;}

protected:
    void block ();
    void unblock ();
private:
    int val;
    bool active;


    List<kernel::PCB> blocked;
    //K_semaphore(uint32 init =1 ):val(init),active(true){}



    void *operator new(size_t size);

    void *operator new[](size_t size);

    void operator delete(void *p) noexcept;

    void operator delete[](void *p) noexcept;
};



#endif //PROJECT_BASE_SEMAPHORE_HPP

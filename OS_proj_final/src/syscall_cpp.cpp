//
// Created by os on 5/23/23.
//

#include "../h/syscall_cpp.hpp"



//standardni konstruktor gde nam je argumentom zadata funkcija
Thread::Thread(void (*body)(void *), void *arg) {
    this->body=body;
    this->arg=arg;
}

int Thread::start() {
    thread_create(&this->myHandle,body,arg);
    return 0;
}

void Thread::join() {
    if (myHandle)
    {
        thread_join(myHandle);
    }
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0;
}
//konstruktor koji ce se koristiti ako je run() overriden
Thread::Thread() {
    this->body=run_wrapper;
    this->arg=this;

}
void Thread::run_wrapper(void *arg) {
    ((Thread*)arg)->run();
}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}

char Console::getc() {
    return ::getc();
}
void Console::putc(char c)
{
    return ::putc(c);
}
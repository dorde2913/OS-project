#ifndef SYSCALL_C_H
#define SYSCALL_C_H

#include "../lib/hw.h"
#include "../h/PCB.hpp"
#include "../test/printing.hpp"
static const uint64 MALLOC_CODE = 0x01;
static const uint64 MEMFREE_CODE = 0x02;

static const uint64 THREADCREATE_CODE = 0x11;
static const uint64 THREADEXIT_CODE = 0x12;
static const uint64 THREADDISPATCH_CODE = 0x13;
static const uint64 THREADJOIN_CODE = 0x14;


static const uint64 SEMOPEN_CODE = 0x21;
static const uint64 SEMCLOSE_CODE = 0x22;
static const uint64 SEMWAIT_CODE = 0x23;
static const uint64 SEMSIGNAL_CODE = 0x24;

static const uint64 TIMESLEEP_CODE = 0x31;

static const uint64 GETC_CODE = 0x41;
static const uint64 PUTC_CODE = 0x42;

static const uint64 MUSER_CODE= 0x43;
static const uint64 MSUPERVISOR_CODE= 0x44;

void* mem_alloc (size_t size);
int mem_free (void*);


typedef kernel::PCB* thread_t;
int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg);
int thread_exit ();
void thread_dispatch ();
void thread_join(thread_t handle);

class K_semaphore;
typedef K_semaphore* sem_t;
int sem_open (sem_t* handle, unsigned init);
int sem_close (sem_t handle);
int sem_wait (sem_t id);
int sem_signal (sem_t id);

typedef unsigned long time_t;
int time_sleep (time_t);

const int EOF=-1;
char getc ();
void putc (char);


void userMod();

void supervisorMod();


#endif

#ifndef PROJECT_BASE_RISCV_HPP
#define PROJECT_BASE_RISCV_HPP
#include "../lib/hw.h"

//ova klasa sluzi za lakse get-ovanje i set-ovanje registara procesora
//mozda i cuvanje? nmp



class Riscv {

public:

    static void save_registers();
    static void restore_registers();



    //statusni registar
    static const uint64 get_sstatus();
    static void set_sstatus(uint64 status);

    //
    static const uint64 get_sip();
    static void set_sip(uint64 status);

    static const uint64 get_sie();
    static void set_sie(uint64 status);

    static const uint64 get_scratch();
    static void set_scratch(uint64 status);

    static const uint64 get_sepc();
    static void set_sepc(uint64 status);

    static const uint64 get_scause();
    static void set_scause(uint64 status);

    static const uint64 get_stvec();
    static void set_stvec(uint64 status);


};
inline const uint64 Riscv::get_sepc() {
    uint64 volatile iret;
    __asm__ volatile ("csrr %0, sepc":"=r"(iret));
    return iret;
}
inline void Riscv::set_sepc(uint64 status) {
    __asm__ volatile("csrw sepc, %0" : :"r"(status));
}
inline void Riscv::set_stvec(uint64 status)
{
    __asm__ volatile("csrw stvec, %0" : :"r"(status));
}
inline const uint64 Riscv::get_scause()
{
    uint64 volatile iret;
    __asm__ volatile ("csrr %0, scause":"=r"(iret));
    return iret;
}
inline const uint64 Riscv::get_sstatus() {
    uint64 volatile iret;
    __asm__ volatile ("csrr %0, sstatus":"=r"(iret));
    return iret;
}
inline void Riscv::set_sstatus(uint64 status) {
    __asm__ volatile("csrw sstatus, %0" : :"r"(status));
}
inline void Riscv::restore_registers() {


    __asm__ volatile("ld x1,1*8(sp)");
    __asm__ volatile("ld x2,2*8(sp)");

    __asm__ volatile("ld x3,3*8(sp)");//x0 je zero, x1 i x2 su ra i sp pa ne cuvamo
    __asm__ volatile("ld x4,4*8(sp)");
    __asm__ volatile("ld x5,5*8(sp)");
    __asm__ volatile("ld x6,6*8(sp)");
    __asm__ volatile("ld x7,7*8(sp)");
    __asm__ volatile("ld x8,8*8(sp)");
    __asm__ volatile("ld x9,9*8(sp)");
    __asm__ volatile("ld x10,10*8(sp)");
    __asm__ volatile("ld x11,11*8(sp)");
    __asm__ volatile("ld x12,12*8(sp)");
    __asm__ volatile("ld x13,13*8(sp)");
    __asm__ volatile("ld x14,14*8(sp)");
    __asm__ volatile("ld x15,15*8(sp)");
    __asm__ volatile("ld x16,16*8(sp)");
    __asm__ volatile("ld x17,17*8(sp)");
    __asm__ volatile("ld x18,18*8(sp)");
    __asm__ volatile("ld x19,19*8(sp)");
    __asm__ volatile("ld x20,20*8(sp)");
    __asm__ volatile("ld x21,21*8(sp)");
    __asm__ volatile("ld x22,22*8(sp)");
    __asm__ volatile("ld x23,23*8(sp)");
    __asm__ volatile("ld x24,24*8(sp)");
    __asm__ volatile("ld x25,25*8(sp)");
    __asm__ volatile("ld x26,26*8(sp)");
    __asm__ volatile("ld x27,27*8(sp)");
    __asm__ volatile("ld x28,28*8(sp)");
    __asm__ volatile("ld x29,29*8(sp)");
    __asm__ volatile("ld x30,30*8(sp)");
    __asm__ volatile("ld x31,31*8(sp)");

    __asm__ volatile("addi sp,sp,256");
}
inline void Riscv::save_registers() {
    __asm__ volatile("addi sp,sp,-256");

    __asm__ volatile("sd x1,2*8(sp)");
    __asm__ volatile("sd x2,2*8(sp)");
    __asm__ volatile("sd x3,3*8(sp)");//x0 je zero, x1 i x2 su ra i sp pa ne cuvamo
    __asm__ volatile("sd x4,4*8(sp)");
    __asm__ volatile("sd x5,5*8(sp)");
    __asm__ volatile("sd x6,6*8(sp)");
    __asm__ volatile("sd x7,7*8(sp)");
    __asm__ volatile("sd x8,8*8(sp)");
    __asm__ volatile("sd x9,9*8(sp)");
    __asm__ volatile("sd x10,10*8(sp)");
    __asm__ volatile("sd x11,11*8(sp)");
    __asm__ volatile("sd x12,12*8(sp)");
    __asm__ volatile("sd x13,13*8(sp)");
    __asm__ volatile("sd x14,14*8(sp)");
    __asm__ volatile("sd x15,15*8(sp)");
    __asm__ volatile("sd x16,16*8(sp)");
    __asm__ volatile("sd x17,17*8(sp)");
    __asm__ volatile("sd x18,18*8(sp)");
    __asm__ volatile("sd x19,19*8(sp)");
    __asm__ volatile("sd x20,20*8(sp)");
    __asm__ volatile("sd x21,21*8(sp)");
    __asm__ volatile("sd x22,22*8(sp)");
    __asm__ volatile("sd x23,23*8(sp)");
    __asm__ volatile("sd x24,24*8(sp)");
    __asm__ volatile("sd x25,25*8(sp)");
    __asm__ volatile("sd x26,26*8(sp)");
    __asm__ volatile("sd x27,27*8(sp)");
    __asm__ volatile("sd x28,28*8(sp)");
    __asm__ volatile("sd x29,29*8(sp)");
    __asm__ volatile("sd x30,30*8(sp)");
    __asm__ volatile("sd x31,31*8(sp)");

}

#endif //PROJECT_BASE_RISCV_HPP

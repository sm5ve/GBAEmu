//
// Created by Spencer Martin on 8/9/21.
//

#ifndef GBAEMU_CPU_H
#define GBAEMU_CPU_H

#include <stdint.h>

enum cpu_mode{
    usr = 0b10000, //User
    fiq = 0b10001, //Fast interrupt
    irq = 0b10010, //Interrupt
    svc = 0b10011, //Supervisor
    abt = 0b10111, //Abort
    und = 0b11011, //Undefined
    sys = 0b11111, //System
};
//The order of these fields might need to be reversed
typedef struct program_state_register{
    bool negative : 1;
    bool zero : 1;
    bool carry : 1;
    bool overflow : 1;
    int reserved : 20;
    bool irq_disabled : 1;
    bool fiq_disabled : 1;
    bool state : 1;
    cpu_mode mode : 5;
};

class cpu {
private:
//Registers
//Active registers
//These are what the ARM code can see running in a given mode
//Active GPRs for a given mode
uint32_t active_gprs[16];
//Program specific registers
program_state_register active_cpsr;
program_state_register active_spsr;
//Internal registers
//These are the backups for banked registers
//Mode-specific registers to be updated on mode changes
uint32_t std_regs[7]; //r8-r14
uint32_t fiq_regs[7]; //r8_fiq-r14_fiq
uint32_t svc_regs[2]; //r13_svc-r14_svc
uint32_t abt_regs[2]; //r13_abt-r14_abt
uint32_t irq_regs[2]; //r13_irq-r14_irq
uint32_t und_regs[2]; //r13_und-r14_und
//Banked SPSRs
program_state_register spsr_fiq;
program_state_register spsr_svc;
program_state_register spsr_abt;
program_state_register spsr_irq;
program_state_register spsr_und;

uint32_t* gp_regs() const;
program_state_register& cpsr() const;
program_state_register& spsr() const;
void set_mode(cpu_mode);
};


#endif //GBAEMU_CPU_H

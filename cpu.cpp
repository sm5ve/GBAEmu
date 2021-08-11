//
// Created by Spencer Martin on 8/9/21.
//

#include <cassert>
#include "cpu.h"
#include "bus.h"
#include <iostream>

cpu::cpu(bool skip_to_cart) {
    isa = arm;
    memset(active_gprs, 0, sizeof(active_gprs));
    memset(&fetch_transaction, 0, sizeof(fetch_transaction));
    memset(&execute_transaction, 0, sizeof(execute_transaction));
    if(skip_to_cart){
        active_gprs[15] = 0x08000000;
    }
}

void cpu::execute_cycle(bus & b) {
    bool execute_empty = true;
    if(decode_occupied){
        execute_empty = execute_instruction(decoded_inst, b);
        if(execute_empty){
            instructions_executed++;
        }
        decode_occupied = false;
    }
    if(execute_empty && fetch_occupied && fetch_transaction.fulfilled){
        //std::cout << "Decoding instruction 0x" << std::hex << fetch_transaction.value << std::endl;
        switch (isa) {
            case arm: decode_arm(fetch_transaction.value, decoded_inst); break;
            case thumb: decode_thumb((uint16_t)fetch_transaction.value, decoded_inst); break; //thumb mode unimplemented
        }
        fetch_occupied = false;
        decode_occupied = true;
    }
    if(!fetch_occupied){
        //std::cout << "Fetching at PC 0x" << std::hex << active_gprs[15] << std::endl;
        fetch_transaction.addr = active_gprs[15]; //Get the instruction at the current PC
        //TODO add timing info
        switch (isa) {
            case arm: fetch_transaction.type = read32; active_gprs[15] += 4; break;
            case thumb: fetch_transaction.type = read16; active_gprs[15] += 2; break;
        }
        b.queue_transcation(fetch_transaction);
        fetch_occupied = true;
    }
}

bool cpu::execute_instruction(decoded_instruction& inst, bus& b){
    if(!execute_occupied){
        execute_occupied = true;
        exec_instruction_time = 1;
        active_execute_transaction = false;
    }
    if(active_execute_transaction && !execute_transaction.fulfilled){
        return false;
    }
    if(--exec_instruction_time != 0){
        return false;
    }
    execute_occupied = false;
    std::cout << "executed instruction " << decoded_inst << " (opcode " <<
        std::hex << decoded_inst.raw_opcode << ")" << std::endl;
    return true;
}

void cpu::flush_pipeline(bus& b) {
    b.invalidate_transaction(fetch_transaction);
    decode_occupied = false;
    fetch_occupied = false;
}

//
// Created by Spencer Martin on 8/9/21.
//

#include <cassert>
#include "cpu.h"
#include "bus.h"
#include <iostream>
#include "disassembler.h"

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
        execute_empty = execute_instruction(decoded_instruction_word, b);
        if(execute_empty){
            instructions_executed++;
        }
        decode_occupied = false;
    }
    if(execute_empty && fetch_occupied && fetch_transaction.fulfilled){
        //std::cout << "Decoding instruction 0x" << std::hex << fetch_transaction.value << std::endl;
        switch (isa) {
            case arm: decoded_instruction_word = fetch_transaction.value; break;
            case thumb: assert(false); //thumb mode unimplemented
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

bool cpu::execute_instruction(uint32_t instruction, bus& b){
    if(!execute_occupied){
        execute_occupied = true;
        exec_instruction_time = 1;
        active_execute_transaction = false;
        //Decode instruction
    }
    if(active_execute_transaction && !execute_transaction.fulfilled){
        return false;
    }
    if(--exec_instruction_time != 0){
        return false;
    }
    execute_occupied = false;
    //std::cout << "executed instruction " << disassemble(instruction, isa) << " (opcode " <<
    //    std::hex << instruction << ")" << std::endl;
    return true;
}

void cpu::flush_pipeline(bus& b) {
    b.invalidate_transaction(fetch_transaction);
    decode_occupied = false;
    fetch_occupied = false;
}

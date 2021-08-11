//
// Created by Spencer Martin on 8/9/21.
//

#include <cassert>
#include "cpu.h"
#include "bus.h"
#include <iostream>

cpu::cpu() {
    isa = arm;
    memset(active_gprs, 0, sizeof(active_gprs));
    memset(&fetch_transaction, 0, sizeof(fetch_transaction));
    memset(&execute_transaction, 0, sizeof(execute_transaction));
}

void cpu::execute_cycle(bus & b) {
    bool execute_empty = true;
    if(decode_occupied){
        execute_empty = execute_instruction(decoded_instruction_word, b);
        decode_occupied = false;
    }
    if(execute_empty && fetch_occupied && fetch_transaction.fulfilled){
        std::cout << "Decoding instruction 0x" << std::hex << fetch_transaction.value << std::endl;
        switch (isa) {
            case arm: decoded_instruction_word = fetch_transaction.value; break;
            case thumb: assert(false); //thumb mode unimplemented
        }
        fetch_occupied = false;
        decode_occupied = true;
    }
    if(!fetch_occupied){
        std::cout << "Fetching at PC 0x" << std::hex << active_gprs[15] << std::endl;
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
    std::cout << "instruction word: 0x" << std::hex << instruction << std::endl;
    return true;
}
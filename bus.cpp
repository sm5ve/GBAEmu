//
// Created by Spencer Martin on 8/9/21.
//

#include "bus.h"
#include <iostream>

bus::bus(bios & b, cartridge & c) : the_bios(b), the_cartridge(c) {
    memset(queued_transactions, 0, sizeof(queued_transactions));
    next_free_transaction_slot = 0;
    next_queued_transaction_slot = 0;
}

bus::~bus(){

}

void* bus::operator[](uint32_t addr) {
    if(addr < 0x4000){
        return &the_bios.buffer[addr];
    }
    zero = 0;
    return &zero;
}

void bus::execute_cycle(){
    if(next_free_transaction_slot == next_queued_transaction_slot){
        return;
    }
    if(queued_transactions[next_queued_transaction_slot] == NULL){
        next_queued_transaction_slot = (next_queued_transaction_slot + 1) % MEMORY_TRANSACTION_BUFFER_SIZE;
        return;
    }
    auto& transaction = *queued_transactions[next_queued_transaction_slot];
    if(--transaction.remaining_cycles == 0){
        transaction.fulfilled = true;
        switch (transaction.type) {
            case write8: *(uint8_t*)(*this)[transaction.addr] = (uint8_t)transaction.value; break;
            case write16: *(uint16_t*)(*this)[transaction.addr] = (uint16_t)transaction.value; break;
            case write32: *(uint32_t*)(*this)[transaction.addr] = transaction.value; break;
            case read8: transaction.value = (uint32_t)*(uint8_t*)(*this)[transaction.addr]; break;
            case read16: transaction.value = (uint32_t)*(uint16_t*)(*this)[transaction.addr]; break;
            case read32: transaction.value = *(uint32_t*)(*this)[transaction.addr]; break;
        }
        queued_transactions[next_queued_transaction_slot] = NULL;
        next_queued_transaction_slot = (next_queued_transaction_slot + 1) % MEMORY_TRANSACTION_BUFFER_SIZE;
    }
    return;
}
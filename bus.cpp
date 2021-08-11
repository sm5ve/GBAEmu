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
    if((0x08000000 <= addr) && (addr < 0x0e000000)){
        return &the_cartridge.buffer[addr & 0x01ffffff];
    }
    zero = 0;
    return &zero;
}

void bus::populateTiming(memory_transaction& transaction){
    //TODO implement instruction prefetching
    switch ((transaction.addr >> 24) & 0xff) {
        case 0x0: transaction.remaining_cycles = 1; break;
        case 0x2: transaction.remaining_cycles = 3 * ((transaction.type & 1) + 1); break;
        case 0x5: transaction.remaining_cycles = 1; break; //TODO add 1 cycle if PPU is accessing pallet RAM
        case 0x6: transaction.remaining_cycles = 1; break; //TODO add 1 cycle if PPU is accessing VRAM
        case 0x7: transaction.remaining_cycles = 1 * ((transaction.type & 1) + 1); break; //TODO add 1 cycle if PPU is accessing OAM
        case 0x8: case 0x9: transaction.remaining_cycles = 2 + 3 * ((transaction.type & 1) + 1); break; //TODO different wait states
        case 0xA: case 0xB: transaction.remaining_cycles = 2 + 3 * ((transaction.type & 1) + 1); break; //TODO different wait states
        case 0xC: case 0xD: transaction.remaining_cycles = 2 + 3 * ((transaction.type & 1) + 1); break; //TODO different wait states
        case 0xE: transaction.remaining_cycles = 5; break; //TODO add different wait states
        default: transaction.remaining_cycles = 1; break;
    }
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
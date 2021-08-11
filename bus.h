//
// Created by Spencer Martin on 8/9/21.
//

#ifndef GBAEMU_BUS_H
#define GBAEMU_BUS_H
#include "cartridge.h"
#include "bios.h"
#include "memory_transaction.h"

#define MEMORY_TRANSACTION_BUFFER_SIZE 10 //This will probably require some tuning

class bus {
public:
    bus(bios&, cartridge&);
    ~bus();

    void* operator[](uint32_t addr);
    void queue_transcation(memory_transaction&);
    void invalidate_transaction(memory_transaction&);
    void execute_cycle();
private:
    bios& the_bios;
    cartridge& the_cartridge;
    memory_transaction* queued_transactions[MEMORY_TRANSACTION_BUFFER_SIZE];
    uint32_t next_free_transaction_slot;
    uint32_t next_queued_transaction_slot;
    uint32_t zero;
};


#endif //GBAEMU_BUS_H

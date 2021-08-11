//
// Created by Spencer Martin on 8/9/21.
//

#ifndef GBAEMU_BUS_H
#define GBAEMU_BUS_H
#include "cartridge.h"
#include "bios.h"
#include "memory_transaction.h"

#define MEMORY_TRANSACTION_BUFFER_SIZE 10 //This will probably require some tuning
#define EWRAM_SIZE 0x40000
#define IWRAM_SIZE 0x8000

class bus {
public:
    bus(bios&, cartridge&);
    ~bus();

    void* operator[](uint32_t addr);
    void populateTiming(memory_transaction& transaction);
    inline void queue_transcation(memory_transaction& transaction){
        assert(queued_transactions[next_free_transaction_slot] == NULL); //Ensure we don't overflow the ring buffer.
        queued_transactions[next_free_transaction_slot] = &transaction;
        transaction.index = next_free_transaction_slot;
        next_free_transaction_slot = (next_free_transaction_slot + 1) % MEMORY_TRANSACTION_BUFFER_SIZE;
        transaction.fulfilled = false;
        populateTiming(transaction);
    }
    inline void invalidate_transaction(memory_transaction& transaction) {
        queued_transactions[transaction.index] = NULL;
    }
    void execute_cycle();
private:
    bios& the_bios;
    cartridge& the_cartridge;
    memory_transaction* queued_transactions[MEMORY_TRANSACTION_BUFFER_SIZE];
    uint32_t next_free_transaction_slot;
    uint32_t next_queued_transaction_slot;
    uint32_t zero;
    void* ewram;
    void* iwram;
};


#endif //GBAEMU_BUS_H

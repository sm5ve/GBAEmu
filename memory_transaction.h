//
// Created by Spencer Martin on 8/10/21.
//

#ifndef GBAEMU_MEMORY_TRANSACTION_H
#define GBAEMU_MEMORY_TRANSACTION_H

enum memory_transaction_type{
    read8, write8, read16, write16, read32, write32
};

struct memory_transaction {
    memory_transaction_type type;
    uint32_t addr;
    uint32_t value;
    bool fulfilled;
    uint8_t num_sequential;
    uint8_t num_nonsequential;
    uint8_t remaining_cycles;
    uint32_t index;
};


#endif //GBAEMU_MEMORY_TRANSACTION_H

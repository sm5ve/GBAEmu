//
// Created by Spencer Martin on 8/10/21.
//

#ifndef GBAEMU_MEMORY_TRANSACTION_H
#define GBAEMU_MEMORY_TRANSACTION_H

enum memory_transaction_type{
    read8 = 0x000, write8 = 0x100, read16 = 0x010, write16 = 0x110, read32 = 0x001, write32 = 0x101
};

struct memory_transaction {
    memory_transaction_type type;
    uint32_t addr;
    uint32_t value;
    bool fulfilled;
    uint8_t remaining_cycles;
    uint32_t index;
};


#endif //GBAEMU_MEMORY_TRANSACTION_H

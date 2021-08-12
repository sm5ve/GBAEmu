//
// Created by Spencer Martin on 8/11/21.
//

#ifndef GBAEMU_INSTRUCTION_DECODER_H
#define GBAEMU_INSTRUCTION_DECODER_H

#include <stdint.h>
#include <ostream>

enum instruction_type{
    BRANCH_IMMEDIATE
};

enum condition{
    EQ=0b0000,
    NE=0b0001,
    CS=0b0010,
    CC=0b0011,
    MI=0b0100,
    PL=0b0101,
    VS=0b0110,
    VC=0b0111,
    HI=0b1000,
    LS=0b1001,
    GE=0b1010,
    LT=0b1011,
    GT=0b1100,
    LE=0b1101,
    UNCONDITIONAL=0b1110,
    SPECIAL=0b1111
};

typedef struct branch_data{
    int32_t offset;
    int32_t link_offset;
    bool link;
};

typedef struct decoded_instruction{
    uint32_t raw_opcode;
    instruction_type type;
    condition cond;
    bool undef;
    uint32_t pc;
    union{
        branch_data branchData;
    };
    bool normal_condition;
} decoded_instruction;

void decode_arm(uint32_t opcode, decoded_instruction&, uint32_t pc = (uint32_t)-1);
void decode_thumb(uint16_t opcode, decoded_instruction&, uint32_t pc = (uint32_t)-1);
std::ostream &operator<<(std::ostream &os, decoded_instruction&);

#endif //GBAEMU_INSTRUCTION_DECODER_H

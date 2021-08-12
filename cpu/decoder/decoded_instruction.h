//
// Created by Spencer Martin on 8/12/21.
//

#ifndef GBAEMU_DECODED_INSTRUCTION_H
#define GBAEMU_DECODED_INSTRUCTION_H

#include <stdint.h>
#include <ostream>

enum instruction_type{
    UNDEFINED, BRANCH_IMMEDIATE
};

enum instruction_condition{
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

enum data_processing_ops{
    AND = 0b0000,
    EOR = 0b0001,
    SUB = 0b0010,
    RSB = 0b0011,
    ADD = 0b0100,
    ADC = 0b0101,
    SBC = 0b0110,
    RSC = 0b0111,
    TST = 0b1000,
    TEQ = 0b1001,
    CMP = 0b1010,
    CMN = 0b1011,
    ORR = 0b1100,
    MOV = 0b1101,
    BIC = 0b1110,
    MVN = 0b1111
};

typedef struct branch_data{
    int32_t offset;
    int32_t link_offset;
    bool link;
};

typedef struct decoded_instruction{
    uint32_t raw_opcode;
    instruction_type type;
    instruction_condition cond;
    uint32_t pc;
    union{
        branch_data branchData;
    };
    bool normal_condition;
    bool flush;
    uint8_t icycles;
} decoded_instruction;

#endif //GBAEMU_DECODED_INSTRUCTION_H

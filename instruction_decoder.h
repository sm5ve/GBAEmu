//
// Created by Spencer Martin on 8/11/21.
//

#ifndef GBAEMU_INSTRUCTION_DECODER_H
#define GBAEMU_INSTRUCTION_DECODER_H

enum instruction_type{

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
    UNDEF=0b1111
};

struct decoded_instruction{

};

#endif //GBAEMU_INSTRUCTION_DECODER_H

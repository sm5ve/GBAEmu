//
// Created by Spencer Martin on 8/11/21.
//

#include "instruction_decoder.h"

void decode_arm(uint32_t opcode, decoded_instruction& i){
    i.raw_opcode = opcode;
    i.cond = (condition)((opcode >> 28) & 0xf);
}

void decode_thumb(uint16_t opcode, decoded_instruction& i){
    i.raw_opcode = opcode;
    assert(false);
}

std::ostream &operator<<(std::ostream &os, decoded_instruction& i){
    switch (i.cond) {
        case EQ: os << "eq"; break;
        case NE: os << "ne"; break;
        case CS: os << "cs"; break;
        case CC: os << "cc"; break;
        case MI: os << "mi"; break;
        case PL: os << "pl"; break;
        case VS: os << "vs"; break;
        case VC: os << "vc"; break;
        case HI: os << "hi"; break;
        case LS: os << "ls"; break;
        case GE: os << "ge"; break;
        case LT: os << "lt"; break;
        case GT: os << "gt"; break;
        case LE: os << "le"; break;
        case UNCONDITIONAL: os << ""; break;
        case UNDEF: os << "undef"; break;
    }
    return os;
}
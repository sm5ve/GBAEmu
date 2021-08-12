//
// Created by Spencer Martin on 8/11/21.
//

#include "instruction_decoder.h"
#include <iostream>
#include "../util.h"

void decode_arm(uint32_t opcode, decoded_instruction& i, uint32_t pc){
    std::cout << "decoding instruction " << std::hex << opcode << std::endl;
    i.raw_opcode = opcode;
    i.pc = pc;
    i.cond = (condition)((opcode >> 28) & 0xf);
    i.undef = false;
    if(i.cond == SPECIAL){
        [[unlikely]]
        assert(false);
    }
    std::cout << "op1 " << std::hex << ((opcode >> 25) & 0x7) << std::endl;
    switch((opcode >> 25) & 0x7){
        case 0b000: assert(false); //ALU things
        case 0b001: {
            assert(false);
        } break; //data processing
        case 0b010: i.undef = true; return;
        case 0b011: if(opcode & (1 << 4)){i.undef = true; return;}
        {
            assert(false);
        } //Single data transfer
        case 0b100: assert(false); //Block data transfer
        case 0b101: {
            i.type = BRANCH_IMMEDIATE;
            i.branchData.link_offset = -4;
            i.branchData.link = (opcode >> 24) & 1;
            i.branchData.offset = sign_extend<24>(opcode & 0xffffff) << 2;
            std::cout << "computed branch data offset " << i.branchData.offset << std::endl;
        } break; //Branch
        case 0b110: case 0b111: if((opcode >> 24) & 0xf == 0xf){
            assert(false); //SWI
        }
        else{
            assert(false); //Coprocessor operation - there is no coprocessor
        }
    }
}

void decode_thumb(uint16_t opcode, decoded_instruction& i, uint32_t pc){
    i.raw_opcode = opcode;
    i.pc = pc;
    assert(false);
}

std::ostream &operator<<(std::ostream &os, condition& cond){
    switch (cond) {
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
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, decoded_instruction& i){
    if(i.cond == SPECIAL){
        os << "unknown";
        return os;
    }
    switch (i.type) {
        case BRANCH_IMMEDIATE:
            os << "b";
            if(i.branchData.link) os << "l";
            if(i.pc == -1)
                os << i.cond << " " << "[PC " << "+-"[i.branchData.offset < 0] << " " << std::hex << abs(i.branchData.offset) << "]";
            else
                os << i.cond << " " << std::hex << (i.pc + i.branchData.offset);
    }
    return os;
}
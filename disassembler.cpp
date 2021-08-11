//
// Created by Spencer Martin on 8/11/21.
//

#include "disassembler.h"

std::string decodeCondition(uint8_t cond){
    switch (cond) {
        case 0b0000: return "eq";
        case 0b0001: return "ne";
        case 0b0010: return "cs";
        case 0b0011: return "cc";
        case 0b0100: return "mi";
        case 0b0101: return "pl";
        case 0b0110: return "vs";
        case 0b0111: return "vc";
        case 0b1000: return "hi";
        case 0b1001: return "ls";
        case 0b1010: return "ge";
        case 0b1011: return "lt";
        case 0b1100: return "gt";
        case 0b1101: return "le";
        case 0b1110: return "";
        case 0b1111: return "Error"; //TODO figure out what to do here
    }
}

std::string disassemble(uint32_t opcode, instruction_set isa){
    uint8_t op = (opcode >> 25) & 0x7;
    uint8_t cond = (opcode >> 28) & 0xf;
    switch(op){
    case 0b100: case 0b101: {
        uint8_t op1 = (opcode >> 19) & 0x3f;
        uint8_t rn = (opcode >> 15) & 0xf;
        bool r = (opcode >> 14) & 0x1;
    } break;
    }

    return "";
}
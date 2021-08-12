//
// Created by Spencer Martin on 8/12/21.
//

#include "instruction_decoder.h"

//There are only 2^16 possible opcodes, so we can cache them all
void decode_thumb(uint16_t opcode, decoded_instruction& i, uint32_t pc){
    i.raw_opcode = opcode;
    i.pc = pc;
    assert(false);
}
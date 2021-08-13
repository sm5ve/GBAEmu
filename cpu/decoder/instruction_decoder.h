//
// Created by Spencer Martin on 8/11/21.
//

#ifndef GBAEMU_INSTRUCTION_DECODER_H
#define GBAEMU_INSTRUCTION_DECODER_H

#include "decoded_instruction.h"

void decode_arm(uint32_t opcode, decoded_instruction&, uint32_t pc = (uint32_t)-1);
void decode_thumb(uint16_t opcode, decoded_instruction&, uint32_t pc = (uint32_t)-1);
std::ostream &operator<<(std::ostream &os, decoded_instruction&);

extern uint32_t decoder_cache_hits;

#endif //GBAEMU_INSTRUCTION_DECODER_H

//
// Created by Spencer Martin on 8/11/21.
//

#ifndef GBAEMU_DISASSEMBLER_H
#define GBAEMU_DISASSEMBLER_H

#include <string>
#include <stdint.h>
#include "forward_decls.h"

std::string disassemble(uint32_t opcode, instruction_set isa);

#endif //GBAEMU_DISASSEMBLER_H

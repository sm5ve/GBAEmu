//
// Created by Spencer Martin on 8/11/21.
//

#include "instruction_decoder.h"
#include <iostream>
#include <utility>
#include "../../util.h"

//#define CACHE_ARM_DECODE

//Referenced Eggvance emulator https://github.com/jsmolka/eggvance/blob/master/eggvance/src/arm/decode.h
#define ARM_SWI_MASK 0b0000'1111'0000'0000'0000'0000'0000'0000
#define ARM_SWI_SIG  0b0000'1111'0000'0000'0000'0000'0000'0000
#define ARM_CDT_MASK 0b0000'1110'0000'0000'0000'0000'0000'0000
#define ARM_CDT_SIG  0b0000'1100'0000'0000'0000'0000'0000'0000
#define ARM_CDO_MASK 0b0000'1111'0000'0000'0000'0000'0001'0000
#define ARM_CDO_SIG  0b0000'1110'0000'0000'0000'0000'0000'0000
#define ARM_CRT_MASK 0b0000'1111'0000'0000'0000'0000'0001'0000
#define ARM_CRT_SIG  0b0000'1110'0000'0000'0000'0000'0001'0000
#define ARM_BL_MASK  0b0000'1110'0000'0000'0000'0000'0000'0000
#define ARM_BL_SIG   0b0000'1010'0000'0000'0000'0000'0000'0000
#define ARM_BDT_MASK 0b0000'1110'0000'0000'0000'0000'0000'0000
#define ARM_BDT_SIG  0b0000'1000'0000'0000'0000'0000'0000'0000
#define ARM_UD1_MASK 0b0000'1110'0000'0000'0000'0000'0001'0000
#define ARM_UD1_SIG  0b0000'0110'0000'0000'0000'0000'0001'0000
#define ARM_SDT_MASK 0b0000'1100'0000'0000'0000'0000'0000'0000
#define ARM_SDT_SIG  0b0000'0100'0000'0000'0000'0000'0000'0000
#define ARM_BX_MASK  0b0000'1111'1111'0000'0000'0000'1111'0000
#define ARM_BX_SIG   0b0000'0001'0010'0000'0000'0000'0001'0000
#define ARM_MUL_MASK 0b0000'1111'1100'0000'0000'0000'1111'0000
#define ARM_MUL_SIG  0b0000'0000'0000'0000'0000'0000'1001'0000
#define ARM_MLL_MASK 0b0000'1111'1000'0000'0000'0000'1111'0000
#define ARM_MLL_SIG  0b0000'0000'1000'0000'0000'0000'1001'0000
#define ARM_SDS_MASK 0b0000'1111'1011'0000'0000'0000'1111'0000
#define ARM_SDS_SIG  0b0000'0001'0000'0000'0000'0000'1001'0000
#define ARM_HDT_MASK 0b0000'1110'0000'0000'0000'0000'1001'0000
#define ARM_HDT_SIG  0b0000'0000'0000'0000'0000'0000'1001'0000
#define ARM_STR_MASK 0b0000'1101'1001'0000'0000'0000'0000'0000
#define ARM_STR_SIG  0b0000'0001'0000'0000'0000'0000'0000'0000
#define ARM_DP_MASK  0b0000'1100'0000'0000'0000'0000'0000'0000
#define ARM_DP_SIG   0b0000'0000'0000'0000'0000'0000'0000'0000

void decode_arm_swi(uint32_t opcode, decoded_instruction& i){

}

void decode_arm_cdt(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_cdo(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_crt(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_bl(uint32_t opcode, decoded_instruction& i){
    i.type = BRANCH_IMMEDIATE;
    i.flush = true;
    i.branchData.link_offset = -4;
    i.branchData.link = (opcode >> 24) & 1;
    i.branchData.offset = (sign_extend<24>(opcode & 0xffffff) << 2);
}

void decode_arm_bdt(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_ud1(uint32_t opcode, decoded_instruction& i){
    i.type = UNDEFINED;
}

void decode_arm_sdt(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_bx(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_mul(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_mll(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_sds(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_hdt(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_str(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

void decode_arm_dp(uint32_t opcode, decoded_instruction& i){
    assert(false); //There should be no coprocessor instructions
}

//Just an idea: if this method ends up being too slow, perhaps we could cache every opcode we decode
//We could even mask out the last 4 bits since they're really easy to parse!

std::pair<uint32_t, decoded_instruction> decode_cache[0x10000];
uint32_t decoder_cache_hits = 0;

inline uint16_t hash_opcode(uint32_t op){
    return (op & 0xffff) ^ (((op >> 16) & 0x0fff) * 23);
}

void decode_arm(uint32_t opcode, decoded_instruction& i, uint32_t pc){
    //std::cout << "decoding instruction " << std::hex << opcode << std::endl;
#ifdef CACHE_ARM_DECODE
    auto& cache_entry = decode_cache[hash_opcode(opcode)];
    if (cache_entry.first == (opcode & 0x0fffffff)){
        decoder_cache_hits++;
        i = cache_entry.second;
        i.cond = (instruction_condition)((opcode >> 28) & 0xf);
        i.pc = pc;
        i.raw_opcode = opcode;
        return;
    }
#endif
    i.cond = (instruction_condition)((opcode >> 28) & 0xf);
    i.pc = pc;
    i.raw_opcode = opcode;
    i.icycles = 0;
    i.flush = false;
    i.normal_condition = true;
    //Perhaps this could be optimized further by switching on some initial bits?
    if((opcode & ARM_SWI_MASK) == ARM_SWI_SIG) decode_arm_swi(opcode, i);
    else if((opcode & ARM_CDT_MASK) == ARM_CDT_SIG) decode_arm_cdt(opcode, i);
    else if((opcode & ARM_CDO_MASK) == ARM_CDO_SIG) decode_arm_cdo(opcode, i);
    else if((opcode & ARM_CRT_MASK) == ARM_CRT_SIG) decode_arm_crt(opcode, i);
    else if((opcode & ARM_BL_MASK ) == ARM_BL_SIG ) decode_arm_bl(opcode, i);
    else if((opcode & ARM_BDT_MASK) == ARM_BDT_SIG) decode_arm_bdt(opcode, i);
    else if((opcode & ARM_UD1_MASK) == ARM_UD1_SIG) decode_arm_ud1(opcode, i);
    else if((opcode & ARM_SDT_MASK) == ARM_SDT_SIG) decode_arm_sdt(opcode, i);
    else if((opcode & ARM_BX_MASK ) == ARM_BX_SIG ) decode_arm_bx(opcode, i);
    else if((opcode & ARM_MUL_MASK) == ARM_MUL_SIG) decode_arm_mul(opcode, i);
    else if((opcode & ARM_MLL_MASK) == ARM_MLL_SIG) decode_arm_mll(opcode, i);
    else if((opcode & ARM_SDS_MASK) == ARM_SDS_SIG) decode_arm_sds(opcode, i);
    else if((opcode & ARM_HDT_MASK) == ARM_HDT_SIG) decode_arm_hdt(opcode, i);
    else if((opcode & ARM_STR_MASK) == ARM_STR_SIG) decode_arm_str(opcode, i);
    else if((opcode & ARM_DP_MASK ) == ARM_DP_SIG ) decode_arm_dp(opcode, i);
    else assert(false);

#ifdef CACHE_ARM_DECODE
    cache_entry.first = opcode & 0x0fffffff;
    cache_entry.second = i;
#endif
}
//
// Created by Spencer Martin on 8/12/21.
//

#include "decoded_instruction.h"

std::ostream &operator<<(std::ostream &os, instruction_condition& cond){
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
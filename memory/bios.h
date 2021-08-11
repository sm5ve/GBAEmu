//
// Created by Spencer Martin on 8/9/21.
//

#ifndef GBAEMU_BIOS_H
#define GBAEMU_BIOS_H

#define BIOS_MAX_SIZE 0x4000

#include "../forward_decls.h"
#include <string>

class bios {
public:
    bios(const std::string filename);
    ~bios();
private:
    friend bus;
    uint8_t* buffer;
};


#endif //GBAEMU_BIOS_H

//
// Created by Spencer Martin on 8/9/21.
//

#ifndef GBAEMU_CARTRIDGE_H
#define GBAEMU_CARTRIDGE_H

#define CART_MAX_SIZE 0x2000000

#include "forward_decls.h"
#include <string>

class cartridge {
public:
    cartridge(const std::string filename);
    ~cartridge();
private:
    friend bus;
    uint8_t* buffer;
};

#endif //GBAEMU_CARTRIDGE_H

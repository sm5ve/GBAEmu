//
// Created by Spencer Martin on 8/9/21.
//

#ifndef GBAEMU_CARTRIDGE_H
#define GBAEMU_CARTRIDGE_H

#include <string>

class cartridge {
public:
    cartridge(const std::string filename);
    ~cartridge();

    

private:
    uint32_t length;
    void* buffer;
};


#endif //GBAEMU_CARTRIDGE_H

//
// Created by Spencer Martin on 8/9/21.
//

#include "bios.h"
#include <fstream>
#include <iostream>

bios::bios(const std::string filename) {
    buffer = (uint8_t*)calloc(BIOS_MAX_SIZE, sizeof(uint8_t));
    std::ifstream fin(filename, std::ios::in | std::ios::binary );
    assert(fin);
    fin.read((char*)buffer, BIOS_MAX_SIZE);
}

bios::~bios(){
    free(buffer);
}
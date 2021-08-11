//
// Created by Spencer Martin on 8/9/21.
//

#include "cartridge.h"
#include <fstream>
#include <iostream>

cartridge::cartridge(const std::string filename) {
    buffer = (uint8_t*)calloc(CART_MAX_SIZE, sizeof(uint8_t));
    std::ifstream fin(filename, std::ios::in | std::ios::binary );
    assert(fin);
    fin.read((char*)buffer, CART_MAX_SIZE);
}

cartridge::~cartridge(){
    free(buffer);
}
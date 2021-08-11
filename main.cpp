#include <iostream>
#include "bios.h"
#include "cartridge.h"
#include "bus.h"
#include "cpu.h"

void main_loop(bus& b, cpu& c){
    for(uint32_t i = 0; i < 100; i++){
        b.execute_cycle();
        c.execute_cycle(b);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    bios b("../gba_bios.bin");
    cartridge c("../rom.gba");
    bus bs(b, c);
    cpu cpu;
    std::cout << std::hex << *((uint32_t*)bs[8]) << std::endl;
    main_loop(bs, cpu);
    return 0;
}
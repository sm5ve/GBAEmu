#include <iostream>
#include "bios.h"
#include "cartridge.h"
#include "bus.h"
#include "cpu.h"

#include <sys/time.h>
#include <ctime>

void main_loop(bus& b, cpu& c){
    auto init_time = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    uint32_t cycle_count = 0;
    for(uint32_t i = 0; i < 100000000; i++){
        cycle_count++;
        b.execute_cycle();
        c.execute_cycle(b);
    }
    auto post_time = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto delta_time = post_time - init_time;
    float mips = c.instructions_executed/((float)delta_time * 1000.0);
    float freq = cycle_count/((float)delta_time * 1000.0);
    std::cout << "MIPS " << mips << std::endl;
    std::cout << "GBA Frequency: " << freq << " MHz" << std::endl;
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
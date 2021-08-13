#include <iostream>
#include "memory/bios.h"
#include "memory/cartridge.h"
#include "memory/bus.h"
#include "cpu/cpu.h"
#include "cpu/decoder/instruction_decoder.h"

#define BOOT_STRAIGHT_TO_CART true

void main_loop(bus& b, cpu& c){
    auto init_time = duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    uint32_t cycle_count = 0;
    for(uint32_t i = 0; i < 10000000; i++){
        cycle_count++;
        b.execute_cycle();
        c.execute_cycle(b);
    }
    auto post_time = duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto delta_time = post_time - init_time;
    float mips = 1000.0 * c.instructions_executed/((float)delta_time);
    float freq = 1000.0 * cycle_count/((float)delta_time);
    float decode_cache_hit_rate = 100.0 * decoder_cache_hits / (float)c.instructions_executed;
    std::cout << "MIPS " << mips << std::endl;
    std::cout << "GBA Frequency: " << freq << " MHz" << std::endl;
    std::cout << "Decode cache hit rate: " << decode_cache_hit_rate << "%" << std::endl;
}

int main() {
    bios b("../gba_bios.bin");
    cartridge c("../rom.gba");
    bus bs(b, c);
    cpu cpu(BOOT_STRAIGHT_TO_CART);
    main_loop(bs, cpu);
    return 0;
}

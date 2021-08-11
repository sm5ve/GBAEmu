cmake_minimum_required(VERSION 3.17)
set(CMAKE_OSX_ARCHITECTURES "arm64")
set (CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Werror -O0 -g -gdwarf")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Ofast -g -gdwarf")
project(GBAEmu)

set(CMAKE_CXX_STANDARD 20)

add_executable(GBAEmu main.cpp memory/cartridge.cpp memory/cartridge.h cpu/cpu.cpp cpu/cpu.h memory/bios.cpp memory/bios.h memory/bus.cpp memory/bus.h forward_decls.h memory/memory_transaction.h flags.h cpu/instruction_decoder.cpp cpu/instruction_decoder.h)
add_custom_command(TARGET GBAEmu
        POST_BUILD
        COMMAND /opt/homebrew/opt/llvm/bin/dsymutil GBAEmu -o GBAEmu.dSYM
        )
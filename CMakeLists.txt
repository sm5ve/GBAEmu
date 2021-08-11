cmake_minimum_required(VERSION 3.17)
project(GBAEmu)

set(CMAKE_CXX_STANDARD 20)

add_executable(GBAEmu main.cpp cartridge.cpp cartridge.h cpu.cpp cpu.h bios.cpp bios.h bus.cpp bus.h forward_decls.h memory_transaction.h)

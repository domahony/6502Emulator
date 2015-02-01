/*
 ============================================================================
 Name        : 6502Emulator.cpp
 Author      : David O'Mahony
 Version     :
 Copyright   : MIT
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include <memory>
#include "ROM.h"
#include "CPU.h"

using namespace std;
using domahony::emu::ROM;
using domahony::emu::CPU;

int main(void) {
	CPU cpu(std::shared_ptr<ROM>(new ROM("/home/domahony/Projects/atariROMs/REVA.ROM")));

	cpu.run();
}

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
#include "AddressSpace.h"
#include "CPU.h"

using namespace std;
using domahony::emu::CPU;
using domahony::emu::AddressSpace;

int main(void) {

	AddressSpace address_space;
	CPU cpu(address_space);

	cpu.run();
}

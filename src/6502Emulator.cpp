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
#include "Emulator.h"

using namespace std;
using domahony::emu::ROM;
using domahony::emu::Emulator;

int main(void) {

	Emulator emulator(std::shared_ptr<ROM>(new ROM("/home/domahony/atari600xl.rom")));
	emulator.run();
}

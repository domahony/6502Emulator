/*
 * BIT.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */

#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Accumulator;
using domahony::emu::Address;

void
initBIT(std::function<int (domahony::emu::CPU&)> *fn)
{

	// zero page
	fn[0x24] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.BIT<Address>(addr);
		return 3;
	};

	// absolute
	fn[0x2C] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.BIT<Address>(addr);
		return 4;

	};

}


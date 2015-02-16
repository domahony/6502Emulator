/*
 * ASL.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */

#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Accumulator;
using domahony::emu::Address;

void
initASL(std::function<int (domahony::emu::CPU&)> *fn)
{
	// accumulator
	fn[0x0A] = [](CPU& cpu) {

		Accumulator acc;
		//cpu.acc = cpu.ASL(cpu.acc);
		cpu.ASL<Accumulator>(acc);
		return 2;
	};

	// zero page
	fn[0x06] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.ASL<Address>(addr);
		return 5;

	};

	// zero page, x
	fn[0x16] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.ASL<Address>(addr);
		return 6;
	};

	// absolute
	fn[0x0E] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.ASL<Address>(addr);
		return 6;

	};

	// absolute X
	fn[0x1E] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.ASL<Address>(addr);
		return 7;
	};
}


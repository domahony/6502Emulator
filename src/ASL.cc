/*
 * ASL.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */

#include "CPU.h"

using domahony::emu::CPU;

void
initAND(std::function<int (domahony::emu::CPU&)> *fn)
{
	// accumulator
	fn[0x0A] = [](CPU& cpu) {
		cpu.acc = cpu.ASL(cpu.acc);
		return 2;
	};

	// zero page
	fn[0x06] = [](CPU& cpu) {

		unsigned short addr;
		unsigned char val = cpu.readZp(addr);
		val = cpu.ASL(val);

		cpu.write(addr, val);
		return 5;
	};

	// zero page, x
	fn[0x16] = [](CPU& cpu) {

		return 6;
	};

	// absolute
	fn[0x0E] = [](CPU& cpu) {

		return 6;
	};

	// absolute X
	fn[0x1E] = [](CPU& cpu) {

		return 7;
	};

}


/*
 * ROL.cc
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */


#include "ROL.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Accumulator;

void
initROL(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * ROL
	 */

	// accumulator
	fn[0x2a] = [](CPU& cpu) {

		Accumulator accumulator;
		cpu.ROL<Accumulator>(accumulator);

		return 2;
	};

	// zero page
	fn[0x26] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.ROL<Address>(addr);
		return 5;
	};

	// zero page, x
	fn[0x36] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.ROL<Address>(addr);

		return 6;
	};

	// absolute
	fn[0x2E] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.ROL<Address>(addr);

		return 6;
	};

	// absolute X
	fn[0x3e] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.ROL<Address>(addr);

		return 7;
	};
}

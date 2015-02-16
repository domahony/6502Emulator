/*
 * LSR.cc
 *
 *  Created on: Feb 16, 2015
 *      Author: domahony
 */


#include "LSR.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Accumulator;

void
initLSR(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * LSR
	 */

	// accumulator
	fn[0x4a] = [](CPU& cpu) {

		Accumulator accumulator;
		cpu.LSR<Accumulator>(accumulator);

		return 2;
	};

	// zero page
	fn[0x46] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.LSR<Address>(addr);
		return 5;
	};

	// zero page, x
	fn[0x56] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.LSR<Address>(addr);

		return 6;
	};

	// absolute
	fn[0x4e] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.LSR<Address>(addr);

		return 6;
	};

	// absolute X
	fn[0x5e] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.LSR<Address>(addr);

		return 7;
	};

}

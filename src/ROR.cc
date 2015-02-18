/*
 * ROR.cc
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */


#include "ROR.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Accumulator;

void
initROR(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * ROR
	 */

	// accumulator
	fn[0x6a] = [](CPU& cpu) {

		Accumulator accumulator;
		cpu.ROR<Accumulator>(accumulator);

		return 2;
	};

	// zero page
	fn[0x66] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.ROR<Address>(addr);
		return 5;
	};

	// zero page, x
	fn[0x76] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.ROR<Address>(addr);

		return 6;
	};

	// absolute
	fn[0x6E] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.ROR<Address>(addr);

		return 6;
	};

	// absolute X
	fn[0x7e] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.ROR<Address>(addr);

		return 7;
	};
}

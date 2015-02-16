/*
 * DEC.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "DEC.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;

void
initDEC(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * DEC
	 */

	// zero page
	fn[0xc6] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.DEC<Address>(addr);

		return 5;
	};

	// zero page, x
	fn[0xd6] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.DEC<Address>(addr);

		return 6;
	};

	// zero page, x
	fn[0xce] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.DEC<Address>(addr);

		return 6;
	};

	// zero page, x
	fn[0xde] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.DEC<Address>(addr);

		return 6;
	};
}

/*
 * INC.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "INC.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;

void
initINC(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * INC
	 */

	// zero page
	fn[0xe6] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.INC<Address>(addr);

		return 5;
	};

	// zero page, x
	fn[0xf6] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.INC<Address>(addr);

		return 6;
	};

	// absolute
	fn[0xee] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.INC<Address>(addr);

		return 6;
	};

	// absolute, x
	fn[0xfe] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.INC<Address>(addr);

		return 7;
	};
}

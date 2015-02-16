/*
 * JMP.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "JMP.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;

void
initJMP(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * JMP
	 */

	// absolute
	fn[0x4c] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.JMP<Address>(addr);

		return 3;
	};

	// absolute indirect
	fn[0x6c] = [](CPU& cpu) {

		Address addr = cpu.getIndirect();
		cpu.JMP<Address>(addr);

		return 5;
	};

}

/*
 * CMP.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "CPX_Y.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initCPX(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * CPX
	 */

	// immediate
	fn[0xe0] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.CPX<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0xe4] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.CPX<Address>(addr);

		return 3;
	};

	// zero page, x
	fn[0xec] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.CPX<Address>(addr);

		return 4;
	};
}

void
initCPY(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * CPY
	 */

	// immediate
	fn[0xc0] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.CPY<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0xc4] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.CPY<Address>(addr);

		return 3;
	};

	// zero page, x
	fn[0xcc] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.CPY<Address>(addr);

		return 4;
	};
}

/*
 * SBC.cc
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */


#include "SBC.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initSBC(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * SBC
	 */

	// immediate
	fn[0xe9] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.SBC<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0xe5] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.SBC<Address>(addr);
		return 3;
	};

	// zero page, x
	fn[0xf5] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.SBC<Address>(addr);

		return 4;
	};

	// absolute
	fn[0xed] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.SBC<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0xfD] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.SBC<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
	};

	// absolute Y
	fn[0xf9] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.SBC<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
		};

	// (indirect, X)
	fn[0xe1] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.SBC<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0xf1] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.SBC<Address>(addr);

		return 5 + addr.boundary_cross() ? 1 : 0;

	};

}

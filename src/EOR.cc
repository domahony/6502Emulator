/*
 * EOR.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "EOR.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initEOR(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * EOR
	 */

	// immediate
	fn[0x49] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.EOR<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0x45] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.EOR<Address>(addr);
		return 3;
	};

	// zero page, x
	fn[0x55] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.EOR<Address>(addr);

		return 4;
	};

	// absolute
	fn[0x4d] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.EOR<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0x5D] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.EOR<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
	};

	// absolute Y
	fn[0x59] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.EOR<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
		};

	// (indirect, X)
	fn[0x41] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.EOR<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0x51] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.EOR<Address>(addr);

		return 5 + addr.boundary_cross() ? 1 : 0;

	};

}

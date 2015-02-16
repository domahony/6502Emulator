/*
 * CMP.cc
 *
 *  Created on: Feb 14, 2015
 *      Author: domahony
 */


#include "CMP.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initCMP(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * CMP
	 */

	// immediate
	fn[0xc9] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.CMP<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0xc5] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.CMP<Address>(addr);
		return 3;
	};

	// zero page, x
	fn[0xd5] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.CMP<Address>(addr);

		return 4;
	};

	// absolute
	fn[0xcd] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.CMP<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0xdd] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.CMP<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
	};

	// absolute Y
	fn[0xd9] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.CMP<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
		};

	// (indirect, X)
	fn[0xc1] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.CMP<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0xd1] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.CMP<Address>(addr);

		return 5 + addr.boundary_cross() ? 1 : 0;

	};

}

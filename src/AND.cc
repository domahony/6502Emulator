/*
 * ADC.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */


#include "AND.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initAND(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * AND
	 */

	// immediate
	fn[0x29] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.AND<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0x25] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.AND<Address>(addr);
		return 3;
	};

	// zero page, x
	fn[0x35] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.AND<Address>(addr);

		return 4;
	};

	// absolute
	fn[0x2D] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.AND<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0x3D] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.AND<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
	};

	// absolute Y
	fn[0x39] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.AND<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
		};

	// (indirect, X)
	fn[0x21] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.AND<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0x31] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.AND<Address>(addr);

		return 5 + addr.boundary_cross() ? 1 : 0;

	};



}

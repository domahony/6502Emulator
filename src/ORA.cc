/*
 * ORA.cc
 *
 *  Created on: Feb 16, 2015
 *      Author: domahony
 */


#include "ORA.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initORA(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * ORA
	 */

	// immediate
	fn[0x09] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.ORA<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0x05] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.ORA<Address>(addr);
		return 2;
	};

	// zero page, x
	fn[0x15] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.ORA<Address>(addr);

		return 3;
	};

	// absolute
	fn[0x0D] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.ORA<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0x1D] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.ORA<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
	};

	// absolute Y
	fn[0x19] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.ORA<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
		};

	// (indirect, X)
	fn[0x01] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.ORA<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0x11] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.ORA<Address>(addr);

		return 5 + addr.boundary_cross() ? 1 : 0;

	};

}

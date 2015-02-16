/*
 * LDA.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "LDA.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initLDA(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * LDA
	 */

	// immediate
	fn[0xa9] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.LDA<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0xa5] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.LDA<Address>(addr);
		return 3;
	};

	// zero page, x
	fn[0xb5] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.LDA<Address>(addr);

		return 4;
	};

	// absolute
	fn[0xad] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.LDA<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0xbD] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.LDA<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
	};

	// absolute Y
	fn[0xb9] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.LDA<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
		};

	// (indirect, X)
	fn[0xa1] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.LDA<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0xb1] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.LDA<Address>(addr);

		return 5 + addr.boundary_cross() ? 1 : 0;

	};

}

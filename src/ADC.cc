/*
 * ADC.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */


#include "ADC.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initADC(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * ADC
	 */

	// immediate
	fn[0x69] = [](CPU& cpu) {

		Immediate immediate = cpu.getImmediate();
		cpu.ADC<Immediate>(immediate);

		return 2;
	};

	// zero page
	fn[0x65] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.ADC<Address>(addr);
		return 3;
	};

	// zero page, x
	fn[0x75] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.ADC<Address>(addr);

		return 4;
	};

	// absolute
	fn[0x62] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.ADC<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0x7D] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.ADC<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
	};

	// absolute Y
	fn[0x79] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.ADC<Address>(addr);

		return 4 + addr.boundary_cross() ? 1 : 0;
		};

	// (indirect, X)
	fn[0x61] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.ADC<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0x71] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.ADC<Address>(addr);

		return 5 + addr.boundary_cross() ? 1 : 0;

	};

}

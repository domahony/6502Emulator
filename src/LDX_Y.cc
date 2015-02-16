/*
 * LDX_Y.cc
 *
 *  Created on: Feb 16, 2015
 *      Author: domahony
 */


#include "LDX_Y.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Immediate;
using domahony::emu::Address;

void
initLDX(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * LDX
	 */

	// immediate
	fn[0xa2] = [](CPU& cpu) {


		Immediate immediate = cpu.getImmediate();
		cpu.LDX<Immediate>(immediate);

		return 2;
	};

	fn[0xa6] = [](CPU& cpu) {


		Address address = cpu.getZp();
		cpu.LDX<Address>(address);

		return 3;
	};

	fn[0xb6] = [](CPU& cpu) {


		Address address = cpu.getZpIdxWithY();
		cpu.LDX<Address>(address);

		return 4;
	};

	fn[0xae] = [](CPU& cpu) {


		Address address = cpu.getAbsolute();
		cpu.LDX<Address>(address);

		return 4;
	};

	fn[0xbe] = [](CPU& cpu) {

		Address address = cpu.getAbsoluteIdxWithY();
		cpu.LDX<Address>(address);

		int tick = 4;
		tick += address.boundary_cross() ? 1 : 0;

		return tick;
	};

}

void
initLDY(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * LDY
	 */

	// immediate
	fn[0xa0] = [](CPU& cpu) {


		Immediate immediate = cpu.getImmediate();
		cpu.LDY<Immediate>(immediate);

		return 2;
	};

	fn[0xa4] = [](CPU& cpu) {


		Address address = cpu.getZp();
		cpu.LDY<Address>(address);

		return 3;
	};

	fn[0xb4] = [](CPU& cpu) {


		Address address = cpu.getZpIdxWithX();
		cpu.LDY<Address>(address);

		return 4;
	};

	fn[0xac] = [](CPU& cpu) {


		Address address = cpu.getAbsolute();
		cpu.LDY<Address>(address);

		return 4;
	};

	fn[0xbc] = [](CPU& cpu) {

		Address address = cpu.getAbsoluteIdxWithX();
		cpu.LDY<Address>(address);

		int tick = 4;
		tick += address.boundary_cross() ? 1 : 0;

		return tick;
	};

}

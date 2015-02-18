/*
 * STX_Y.cc
 *
 *  Created on: Feb 16, 2015
 *      Author: domahony
 */


#include "STX_Y.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;

void
initSTX(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * SDX
	 */

	fn[0x86] = [](CPU& cpu) {


		Address address = cpu.getZp();
		cpu.STX<Address>(address);

		return 3;
	};

	fn[0x96] = [](CPU& cpu) {


		Address address = cpu.getZpIdxWithY();
		cpu.STX<Address>(address);

		return 4;
	};

	fn[0x8e] = [](CPU& cpu) {


		Address address = cpu.getAbsolute();
		cpu.STX<Address>(address);

		return 4;
	};

}

void
initSTY(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * STY
	 */

	fn[0x84] = [](CPU& cpu) {


		Address address = cpu.getZp();
		cpu.STY<Address>(address);

		return 3;
	};

	fn[0x94] = [](CPU& cpu) {


		Address address = cpu.getZpIdxWithX();
		cpu.STY<Address>(address);

		return 4;
	};

	fn[0x8c] = [](CPU& cpu) {


		Address address = cpu.getAbsolute();
		cpu.STY<Address>(address);

		return 4;
	};

}

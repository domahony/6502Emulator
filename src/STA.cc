/*
 * STA.cc
 *
 *  Created on: Feb 18, 2015
 *      Author: domahony
 */


#include "STA.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;
using domahony::emu::Immediate;

void
initSTA(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * STA
	 */

	// zero page
	fn[0x85] = [](CPU& cpu) {

		Address addr = cpu.getZp();
		cpu.STA<Address>(addr);
		return 3;
	};

	// zero page, x
	fn[0x95] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxWithX();
		cpu.STA<Address>(addr);

		return 4;
	};

	// absolute
	fn[0x8d] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.STA<Address>(addr);

		return 4;
	};

	// absolute X
	fn[0x9D] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithX();
		cpu.STA<Address>(addr);

		return 5;
	};

	// absolute Y
	fn[0x99] = [](CPU& cpu) {

		Address addr = cpu.getAbsoluteIdxWithY();
		cpu.STA<Address>(addr);

		return 5;
		};

	// (indirect, X)
	fn[0x81] = [](CPU& cpu) {

		Address addr = cpu.getZpIdxIndirect();
		cpu.STA<Address>(addr);

		return 6;
	};

	// (indirect), Y
	fn[0x91] = [](CPU& cpu) {

		Address addr = cpu.getZpIndirectIdxWithY();
		cpu.STA<Address>(addr);

		return 6;

	};

}

/*
 * DEC.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "DEX_Y.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initDEX(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * DEX
	 */

	// zero page
	fn[0xca] = [](CPU& cpu) {

		cpu.DEX();

		return 2;
	};
}

void
initDEY(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * DEY
	 */

	// zero page
	fn[0x88] = [](CPU& cpu) {

		cpu.DEY();

		return 2;
	};
}

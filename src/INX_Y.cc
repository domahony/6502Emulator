/*
 * INX_Y.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "INX_Y.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initINX(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * DEX
	 */

	// zero page
	fn[0xe8] = [](CPU& cpu) {

		cpu.INX();

		return 2;
	};
}

void
initINY(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * DEY
	 */

	// zero page
	fn[0xc8] = [](CPU& cpu) {

		cpu.INY();

		return 2;
	};
}

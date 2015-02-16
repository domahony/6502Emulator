/*
 * NOP.cc
 *
 *  Created on: Feb 16, 2015
 *      Author: domahony
 */


#include "NOP.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initNOP(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * NOP
	 */

	// implied
	fn[0xea] = [](CPU& cpu) {

		cpu.NOP();

		return 2;
	};

}

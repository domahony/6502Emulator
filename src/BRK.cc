/*
 * BCC.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */


#include "BRK.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initBRK(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BCC
	 */

	// immediate
	fn[0x00] = [](CPU& cpu) {

		cpu.BRK();

		return 7;
	};

}

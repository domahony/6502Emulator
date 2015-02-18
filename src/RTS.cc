/*
 * RTS.cc
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */


#include "RTS.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initRTS(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * RTS
	 */

	// absolute
	fn[0x60] = [](CPU& cpu) {

		cpu.RTS();

		return 6;
	};
}

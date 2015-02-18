/*
 * RTI.cc
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */


#include "RTI.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initRTI(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * RTI
	 */

	// absolute
	fn[0x40] = [](CPU& cpu) {

		cpu.RTI();

		return 6;
	};
}

/*
 * JSR.cc
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */


#include "JSR.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Address;

void
initJSR(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * JSR
	 */

	// absolute
	fn[0x20] = [](CPU& cpu) {

		Address addr = cpu.getAbsolute();
		cpu.JSR<Address>(addr);

		return 6;
	};
}

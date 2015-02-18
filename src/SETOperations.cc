/*
 * SETOperations.cc
 *
 *  Created on: Feb 18, 2015
 *      Author: domahony
 */


#include "SETOperations.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initSET(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * SEC
	 */
	fn[0x38] = [](CPU& cpu) {

		cpu.SEC();
		return 2;
	};

	/*
	 * SED
	 */
	fn[0xf8] = [](CPU& cpu) {

		cpu.SED();
		return 2;
	};

	/*
	 * SEI
	 */
	fn[0x78] = [](CPU& cpu) {

		cpu.SEI();
		return 2;
	};

}

/*
 * CLEAROperations.cc
 *
 *  Created on: Feb 14, 2015
 *      Author: domahony
 */


#include "CLEAROperations.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initCLEAR(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * CLC
	 */
	fn[0x18] = [](CPU& cpu) {

		cpu.CLC();
		return 2;
	};

	/*
	 * CLD
	 */
	fn[0xD8] = [](CPU& cpu) {

		cpu.CLD();
		return 2;
	};

	/*
	 * CLI
	 */
	fn[0x58] = [](CPU& cpu) {

		cpu.CLI();
		return 2;
	};

	/*
	 * CLI
	 */
	fn[0xB8] = [](CPU& cpu) {

		cpu.CLV();
		return 2;
	};

}

/*
 * TRANSFEROperations.cc
 *
 *  Created on: Feb 18, 2015
 *      Author: domahony
 */


#include "TRANSFEROperations.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initTRANSFER(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * TAX
	 */
	fn[0xaa] = [](CPU& cpu) {

		cpu.TAX();
		return 2;
	};

	/*
	 * TAY
	 */
	fn[0xa8] = [](CPU& cpu) {

		cpu.TAY();
		return 2;
	};

	/*
	 * TSX
	 */
	fn[0xba] = [](CPU& cpu) {

		cpu.TSX();
		return 2;
	};

	/*
	 * TXA
	 */
	fn[0x8a] = [](CPU& cpu) {

		cpu.TXA();
		return 2;
	};

	/*
	 * TXS
	 */
	fn[0x9a] = [](CPU& cpu) {

		cpu.TXS();
		return 2;
	};

	/*
	 * TYA
	 */
	fn[0x98] = [](CPU& cpu) {

		cpu.TYA();
		return 2;
	};

}

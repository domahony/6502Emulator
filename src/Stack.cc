/*
 * Stack.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */


#include "CPU.h"
#include "Stack.h"

using domahony::emu::CPU;

void initStack(std::function<int (domahony::emu::CPU&)> *fn)
{
	// immediate
	fn[0x48] = [](CPU& cpu) {

		cpu.PHA();

		return 3;
	};

	fn[0x08] = [](CPU& cpu) {

		cpu.PHP();

		return 3;
	};

	fn[0x68] = [](CPU& cpu) {

		cpu.PLA();

		return 4;
	};

	fn[0x28] = [](CPU& cpu) {

		cpu.PLP();

		return 4;
	};

}



/*
 * BCC.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */


#include "BCC.h"
#include "CPU.h"

using domahony::emu::CPU;
using domahony::emu::Relative;

void
initBCC(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BCC
	 */

	// immediate
	fn[0x90] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BCC<Relative>(addr);

		int tick = 2;
		if (addr.branch_taken()) {
			tick++;

			if (addr.page_boundary()) {
				tick++;
			}
		}


		return tick;
	};

}

void
initBCS(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BCS
	 */

	// immediate
	fn[0xB0] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BCS<Relative>(addr);

		int tick = 2;
		if (addr.branch_taken()) {
			tick++;

			if (addr.page_boundary()) {
				tick++;
			}
		}

		return tick;
	};

}

void
initBEQ(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BEQ
	 */

	// immediate
	fn[0xF0] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BEQ<Relative>(addr);

		int tick = 2;
		if (addr.branch_taken()) {
			tick++;

			if (addr.page_boundary()) {
				tick++;
			}
		}

		return tick;
	};

}

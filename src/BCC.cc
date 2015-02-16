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

void
initBMI(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BMI
	 */

	// immediate
	fn[0x30] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BMI<Relative>(addr);

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
initBNE(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BMI
	 */

	// immediate
	fn[0xD0] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BNE<Relative>(addr);

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
initBPL(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BMI
	 */

	// immediate
	fn[0x10] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BPL<Relative>(addr);

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
initBVC(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BVC
	 */

	// immediate
	fn[0x50] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BVC<Relative>(addr);

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
initBVS(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * BVS
	 */

	// immediate
	fn[0x70] = [](CPU& cpu) {

		Relative addr= cpu.getRelative();
		cpu.BVS<Relative>(addr);

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

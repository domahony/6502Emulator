/*
 * ADC.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */


#include "AND.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initAND(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * AND
	 */

	// immediate
	fn[0x29] = [](CPU& cpu) {
		unsigned char val = cpu.readImmediate8();
		cpu.AND(val);
		return 2;
	};

	// zero page
	fn[0x25] = [](CPU& cpu) {
		unsigned char val = cpu.readZp();
		cpu.AND(val);
		return 3;
	};

	// zero page, x
	fn[0x35] = [](CPU& cpu) {

		unsigned char val = cpu.readZpX();

		cpu.AND(val);
		return 4;
	};

	// absolute
	fn[0x2D] = [](CPU& cpu) {

		unsigned char val = cpu.readMem16();
		cpu.AND(val);

		return 4;
	};

	// absolute X
	fn[0x3D] = [](CPU& cpu) {

		bool pageBoundary = false;
		unsigned char val = cpu.readMem16X(&pageBoundary);

		cpu.AND(val);

		return 4 + pageBoundary ? 1 : 0;
	};

	// absolute Y
	fn[0x39] = [](CPU& cpu) {
		bool pageBoundary = false;
		unsigned char val = cpu.readMem16Y(&pageBoundary);

		cpu.AND(val);

		return 4 + pageBoundary ? 1 : 0;
	};

	// (indirect, X)
	fn[0x21] = [](CPU& cpu) {

		unsigned short val = cpu.readZpIndirectX();
		cpu.AND(val);

		return 6;
	};

	// (indirect), Y
	fn[0x31] = [](CPU& cpu) {

		bool page = false;
		unsigned short val = cpu.readZpIndirectY(&page);

		cpu.AND(val);
		return 5 + page ? 1 : 0;

	};



}

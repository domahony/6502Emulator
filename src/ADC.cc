/*
 * ADC.cc
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */


#include "ADC.h"
#include "CPU.h"

using domahony::emu::CPU;

void
initADC(std::function<int (domahony::emu::CPU&)> *fn)
{
	/*
	 * ADC
	 */
	fn[0x69] = [](CPU& cpu) {
		unsigned char val = cpu.readImmediate8();
		cpu.ADC(val);
		return 2;
	};

	fn[0x6D] = [](CPU& cpu) {

		unsigned char val = cpu.readMem16();
		cpu.ADC(val);

		return 4;
	};

	fn[0x7D] = [](CPU& cpu) {

		bool pageBoundary = false;
		unsigned char val = cpu.readMem16X(&pageBoundary);

		cpu.ADC(val);

		return 4 + pageBoundary ? 1 : 0;
	};

	fn[0x79] = [](CPU& cpu) {
		bool pageBoundary = false;
		unsigned char val = cpu.readMem16Y(&pageBoundary);

		cpu.ADC(val);

		return 4 + pageBoundary ? 1 : 0;
	};

	fn[0x61] = [](CPU& cpu) {

		unsigned short val = cpu.readZpIndirectX();
		cpu.ADC(val);

		return 6;
	};

	fn[0x71] = [](CPU& cpu) {

		bool page = false;
		unsigned short val = cpu.readZpIndirectY(&page);

		cpu.ADC(val);
		return 5 + page ? 1 : 0;

	};

	fn[0x65] = [](CPU& cpu) {
		unsigned char val = cpu.readZp();
		cpu.ADC(val);
		return 3;
	};

	fn[0x75] = [](CPU& cpu) {

		unsigned char val = cpu.readZpX();

		cpu.ADC(val);
		return 4;
	};

}

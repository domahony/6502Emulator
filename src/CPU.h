/*
 * CPU.h
 *
 *  Created on: Feb 1, 2015
 *      Author: domahony
 */

#ifndef CPU_H_
#define CPU_H_

#include "ROM.h"
#include <memory>
#include <vector>
#include <functional>

namespace domahony {
namespace emu {

class CPU {
public:
	CPU(std::shared_ptr<domahony::emu::ROM> rom);

	virtual ~CPU() {

	}

	void run();

	std::shared_ptr<domahony::emu::ROM> rom;
	std::vector<unsigned char> ram;

	unsigned char read(unsigned short);

	bool N,V,B,D,I,Z,C;

	unsigned short pc; //program counter;
	unsigned char sp; // stack pointer;
	unsigned char acc; //accumulator
	unsigned char x; // X register
	unsigned char y; // Y register

	std::function<int (CPU&)> fn[255];

private:
	void init();

	unsigned char readImmediate8() {
		return read(pc++);
	}

	unsigned char readMem16() {
		unsigned short low = read(pc++);
		unsigned short high = read(pc++);

		high <<= 8;
		high += low;
		return read(high);
	}

	unsigned char readZp() {

		unsigned short zp = read(pc++);
		return read(zp);
	}

	unsigned char readZpIndirectX() {
		unsigned char zp = read(pc++);
		zp += static_cast<char>(x);

		unsigned char addr_low = read(zp);
		unsigned short addr = read(zp + 1);
		addr <<= 8;
		addr += addr_low;

		unsigned char val = read(addr);

		return val;
	}

	unsigned char readZpIndirectY() {

		unsigned char addr_low = read(pc++);
		unsigned short addr_high = read(pc++);

		addr_high <<= 8;
		addr_high += addr_low;

		unsigned char val = read(addr_high);
		val += static_cast<char>(y);

		return val;
	}

	void ADC(unsigned short value);
	void AND(unsigned short value);
	void LDA(unsigned short addr);
};

} /* namespace emu */
} /* namespace domahony */

#endif /* CPU_H_ */

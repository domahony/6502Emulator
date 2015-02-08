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

class Address;

class CPU {

friend class Accumulator;

public:
	CPU(std::shared_ptr<domahony::emu::ROM> rom);

	virtual ~CPU() {

	}

	void run();

	std::shared_ptr<domahony::emu::ROM> rom;
	std::vector<unsigned char> ram;

	unsigned char read(unsigned short);
	void write(unsigned short, unsigned char);

	bool N,V,B,D,I,Z,C;
	std::function<int (CPU&)> fn[255];

	Address getImmediate();
	Address getAbsolute();
	Address getZp();
	Address getRelative();
	Address getAbsoluteIdxWithX();
	Address getAbsoluteIdxWithY();
	Address getZpIdxWithX();
	Address getZpIdxWithY();
	Address getZpIdxIndirect();
	Address getZpIndirectIdxWithY();


	void ADC(unsigned char value);
	void AND(unsigned char value);
	unsigned char ASL(unsigned char value);
	template <typename T> void ASL(T addr);
	void LDA(unsigned short addr);

private:
	unsigned short pc; //program counter;
	unsigned char sp; // stack pointer;
	unsigned char acc; //accumulator
	unsigned char x; // X register
	unsigned char y; // Y register


	void init();

};

class Accumulator {
	Accumulator() {};
	~Accumulator() {};

	unsigned char read(const CPU& c) const {
		return c.acc;
	}

	void write(CPU& c, unsigned char val) const {
		c.acc = val;
	}
};

class Address {
public:
	Address(unsigned char low, unsigned char high)
	{
		addr = high;
		addr <<= 8;
		addr &= low;
	}

	unsigned char read(domahony::emu::CPU& c) const {
		return c.read(addr);
	}

	void write(domahony::emu::CPU& c, unsigned char val) {
		c.write(addr, val);
	}


	virtual ~Address() {

	}

private:
	unsigned short addr;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* CPU_H_ */

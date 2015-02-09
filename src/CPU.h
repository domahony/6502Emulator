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

unsigned char BCD(unsigned char v);

class Address;
class Immediate;
class Relative;

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

	Immediate getImmediate();
	Address getAbsolute();
	Address getZp();
	Relative getRelative();
	Address getAbsoluteIdxWithX();
	Address getAbsoluteIdxWithY();
	Address getZpIdxWithX();
	Address getZpIdxWithY();
	Address getZpIdxIndirect();
	Address getZpIndirectIdxWithY();

	template <typename T> void ADC(T addr);
	template <typename T> void AND(T addr);
	template <typename T> void ASL(T addr);
	template <typename T> void BCC(T addr);
	template <typename T> void BCS(T addr);
	template <typename T> void BEQ(T addr);
	template <typename T> void BIT(T addr);
	template <typename T> void LDA(T addr);

private:
	unsigned short pc; //program counter;
	unsigned char sp; // stack pointer;
	unsigned char acc; //accumulator
	unsigned char x; // X register
	unsigned char y; // Y register


	void init();

};

class Accumulator {
public:
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

	Address(unsigned char low, unsigned char high) : boundary(false)
	{
		addr <<= 8;
		addr &= low;
	}

	Address(unsigned char low, unsigned char high, char offset) : Address(low, high)
	{
		unsigned short ah1 = addr >> 8;
		addr += offset;
		unsigned short ah2 = addr >> 8;

		boundary = ah1 != ah2;
	}

	bool boundary_cross() const {
		return boundary;
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
	bool boundary;
};

class Immediate {
public:
	Immediate(unsigned char val) : val(val) {

	}

	unsigned char read(domahony::emu::CPU& c) const {
		return val;
	}

private:
	const unsigned char val;
};

class Relative {
public:
	Relative(unsigned short pc, char offset) : pc(pc), offset(offset), addr(pc + offset), branch(false) {

	}

	unsigned char read(domahony::emu::CPU& c) const {
		return addr;
	}

	void set_branch() {
		branch = true;
	}

	bool branch_taken() const {
		return branch;
	}

	bool page_boundary() const {

		unsigned char ah1 = pc >> 8;;
		unsigned char ah2 = addr >> 8;

		return ah1 != ah2;
	}

private:
	const unsigned short pc;
	const char offset;
	const unsigned char addr;
	bool branch;
};

} /* namespace emu */
} /* namespace domahony */



#endif /* CPU_H_ */

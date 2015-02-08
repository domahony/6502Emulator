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
	Address getRelative();
	Address getAbsoluteIdxWithX();
	Address getAbsoluteIdxWithY();
	Address getZpIdxWithX();
	Address getZpIdxWithY();
	Address getZpIdxIndirect();
	Address getZpIndirectIdxWithY();


	template <typename T> void ADC(T addr)
	{
		unsigned char arg = addr.read(*this);

		unsigned short val = acc + arg + (C ? 1 : 0);

		V = ((val >> 7) != (acc >> 7));
		N = (acc >> 7) & 0x1;
		Z = (val == 0);

		if (D) {
			val = BCD(acc) + BCD(arg) + (C ? 1 : 0);
			C = val > 99;
		} else {
			C = val > 255;
		}

		acc = val & 0xFF;
	}

	template <typename T> void AND(T addr)
	{
		unsigned char value = addr.read(*this);

		acc = acc & (value & 0xFF);
		N = acc >> 7;
		Z = acc == 0;
		/*
		A = A & M
		P.N = A.7
		P.Z = (A==0) ? 1:0
		 */
	}

	template <typename T> void ASL(T addr)
	{
		unsigned char value = addr.read(*this);

		C = (value >> 7) & 0x1;
		unsigned char ret = (value << 1) & 0xFE;
		N = (ret >> 7) & 0x1;
		Z = ret == 0;

		addr.write(*this, ret);

		/*
		Logic:
		  P.C = B.7
		  B = (B << 1) & $FE
		  P.N = B.7
		  P.Z = (B==0) ? 1:0
		 */

	}

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

} /* namespace emu */
} /* namespace domahony */



#endif /* CPU_H_ */

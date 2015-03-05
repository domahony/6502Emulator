/*
 * CPU.h
 *
 *  Created on: Feb 1, 2015
 *      Author: domahony
 */

#ifndef CPU_H_
#define CPU_H_

#include "AddressSpace.h"
#include <memory>
#include <vector>
#include <functional>
#include <iostream>

namespace domahony {
namespace emu {

unsigned char BCD(unsigned char v);

class Address;
class Immediate;
class Relative;

class CPU {

friend class Accumulator;

public:
	CPU(const AddressSpace&);

	virtual ~CPU() {

	}

	void run();

	unsigned char read(unsigned short);
	void write(unsigned short, unsigned char);

	bool N,V,B,D,I,Z,C;
	std::function<int (CPU&)> fn[255];

	Immediate getImmediate();
	Address getAbsolute();
	Address getIndirect();
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
	template <typename T> void BMI(T addr);
	template <typename T> void BNE(T& addr);
	template <typename T> void BPL(T addr);
	void BRK();
	template <typename T> void BVC(T addr);
	template <typename T> void BVS(T addr);
	void CLC();
	void CLD();
	void CLI();
	void CLV();
	template <typename T> void CMP(T addr);
	template <typename T> void CPX(T addr);
	template <typename T> void CPY(T addr);
	template <typename T> void DEC(T addr);
	void DEX();
	void DEY();
	template <typename T> void EOR(T addr);
	template <typename T> void INC(T addr);
	void INX();
	void INY();
	template <typename T> void JMP(T addr);
	template <typename T> void JSR(T addr);
	template <typename T> void LDA(T addr);
	template <typename T> void LDX(T addr);
	template <typename T> void LDY(T addr);
	template <typename T> void LSR(T addr);
	void NOP();
	template <typename T> void ORA(T addr);
	void PHA();
	void PHP();
	void PLA();
	void PLP();
	template <typename T> void ROL(T addr);
	template <typename T> void ROR(T addr);
	void RTI();
	void RTS();
	template <typename T> void SBC(T addr);
	void SEC();
	void SED();
	void SEI();
	template <typename T> void STA(T addr);
	template <typename T> void STX(T addr);
	template <typename T> void STY(T addr);
	void TAX();
	void TAY();
	void TSX();
	void TXA();
	void TXS();
	void TYA();

private:
	unsigned short pc; //program counter;
	unsigned char sp; // stack pointer;
	unsigned char acc; //accumulator
	unsigned char x; // X register
	unsigned char y; // Y register

	void push(unsigned char b);
	unsigned char pop();
	unsigned char get_flags() const;

	AddressSpace address_space;
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
		addr = high;
		addr <<= 8;
		addr |= low;
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

	unsigned short get_address() const {
		return addr;
	}

	virtual ~Address() {

	}


private:
	unsigned short addr;
	bool boundary;
};

class Immediate {
public:
	Immediate(unsigned char val) : val(val){
	}

	unsigned char read(domahony::emu::CPU& c) const {
		return val;
	}

	unsigned char read() const {
		return val;
	}

private:
	const unsigned char val;
};

class Relative {
public:
	Relative(signed short pc, char offset) : pc(pc), offset(offset), addr(pc + offset), branch(false) {

	}

	unsigned char read(domahony::emu::CPU& c) const {
		return read();
	}

	unsigned char read() const {
		return offset;
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

std::ostream & operator<<(std::ostream& output, const Address& addr);
std::ostream & operator<<(std::ostream& output, const Immediate& addr);
std::ostream & operator<<(std::ostream& output, const Accumulator& addr);
std::ostream & operator<<(std::ostream& output, const Relative& addr);

} /* namespace emu */
} /* namespace domahony */



#endif /* CPU_H_ */

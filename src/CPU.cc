/*
 * CPU.cc
 *
 *  Created on: Feb 1, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ADC.h"
#include "AND.h"
#include "ASL.h"
#include "BCC.h"
#include "BIT.h"
#include "CLEAROperations.h"
#include "CMP.h"
#include "CPX_Y.h"
#include "DEC.h"
#include "DEX_Y.h"
#include <vector>
#include <functional>

namespace domahony {
namespace emu {

using std::vector;
using std::function;

CPU::
CPU(std::shared_ptr<domahony::emu::ROM> rom) : rom(rom) {

	unsigned char low = read(0xFFFa);
	unsigned char high = read(0xFFFa + 1);

	pc = (high << 8) + low;

	std::cout << "Initial PC: " << std::hex << pc << std::endl;

	ram.resize(0xFFFF);

	initADC(fn);
	initAND(fn);
	initASL(fn);
	initBCC(fn);
	initBCS(fn);
	initBEQ(fn);
	initBIT(fn);
	initBMI(fn);
	initBNE(fn);
	initBPL(fn);
	initCLEAR(fn);
	initCMP(fn);
	initCPX(fn);
	initCPY(fn);
	initDEC(fn);
	initDEX(fn);
	initDEY(fn);

	fn[0xa5] = [] (CPU& cpu) {

		std::cout << "Executing" << std::endl;
		unsigned char addr = cpu.read(cpu.pc++);
		cpu.acc = cpu.read(addr);

		std::cout << "Acc Value: " << cpu.acc << std::endl;
		return 1;
	};

}

unsigned char CPU::
get_flags() const {

	unsigned char ret = 0;

	if (N) ret |= 1;
	ret <<=1;
	if (V) ret |= 1;
	ret <<=2;
	if (B) ret |= 1;
	ret <<=1;
	if (D) ret |= 1;
	ret <<=1;
	if (I) ret |= 1;
	ret <<=1;
	if (Z) ret |= 1;
	ret <<=1;
	if (C) ret |= 1;

	return ret;
}

void CPU::
push(unsigned char b) {

	write(0x100 | sp, b);
	sp -= 1;

}

void CPU::
run() {

	unsigned char op = read(pc++);
	int tick = 0;
	fn[op](*this);
}

unsigned char CPU::
read(unsigned short addr)
{
	if (addr < 0xA000) {
		return ram[addr];
	} else {
		return rom->fetch(addr - 0xA000);
	}
}


void CPU::
write(unsigned short addr, unsigned char val)
{
	if (addr < 0xA000) {
		ram[addr] == val;
	}
}

unsigned char
BCD(unsigned char v)
{
	unsigned char tens = (v >> 4) * 10;
	unsigned char ones = v & 0x0F;

	return tens + ones;
}


Immediate CPU::
getImmediate()
{
	Immediate ret(read(pc++));
	return ret;
}

Address CPU::
getAbsolute()
{
	unsigned char low = read(pc++);
	unsigned char high = read(pc++);

	return Address(low, high);
}

Address CPU::
getZp()
{
	unsigned char low = read(pc++);
	unsigned char high = 0;
	Address addr(low, high);

	return addr;
}

Relative CPU::
getRelative()
{
	unsigned char offset = read(pc++);
	return Relative(pc, static_cast<char>(offset));
}

Address CPU::
getAbsoluteIdxWithX()
{
	unsigned char low = read(pc++);
	unsigned char high = read(pc++);

	return Address(low, high, x);
}

Address CPU::
getAbsoluteIdxWithY()
{
	unsigned char low = read(pc++);
	unsigned char high = read(pc++);

	return Address(low, high, y);
}

Address CPU::
getZpIdxWithX()
{
	unsigned char zp = read(pc++);
	zp += x;

	Address addr(zp, 0);
	return addr;
}

Address CPU::
getZpIdxWithY()
{
	unsigned char zp = read(pc++);
	zp += y;

	Address addr(zp, 0);
	return addr;
}

Address CPU::
getZpIdxIndirect()
{
	unsigned char zp = read(pc++);
	zp += static_cast<char>(x);

	unsigned char low = read(zp);
	unsigned char high = read(zp + 1);

	return Address(low, high);
}

Address CPU::
getZpIndirectIdxWithY()
{
	unsigned char zp = read(pc++);

	unsigned char low = read(zp);
	unsigned char high = read(zp + 1);

	return Address(low, high, static_cast<char>(y));
}

template <typename T> void CPU::
AND(T addr)
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

template void CPU::AND<Immediate>(Immediate);
template void CPU::AND<Address>(Address);

template <typename T> void CPU::
ASL(T addr)
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

template void CPU::ASL<Accumulator>(Accumulator);
template void CPU::ASL<Address>(Address);

template <typename T> void CPU::
ADC(T addr)
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

template void CPU::ADC<Immediate>(Immediate);
template void CPU::ADC<Address>(Address);

template <typename T> void CPU::
BCC(T addr)
{
	if (!C) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BCC<Relative>(Relative);

template <typename T> void CPU::
BCS(T addr)
{
	if (C) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BCS<Relative>(Relative);

template <typename T> void CPU::
BEQ(T addr)
{
	if (Z) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BEQ<Relative>(Relative);

template <typename T> void CPU::
BIT(T addr)
{
	unsigned char t  = acc & addr.read(*this) ;

	N = (t >> 7) && 0x1;
	V = (t >> 6) && 0x1;
	Z = (t == 0);
	/*
	  t = A & M
	  P.N = t.7
	  P.V = t.6
	  P.Z = (t==0) ? 1:0
	*/
}

template void CPU::BIT<Address>(Address);

template <typename T> void CPU::
BMI(T addr)
{
	if (N) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BMI<Relative>(Relative);

template <typename T> void CPU::
BNE(T addr)
{
	if (!Z) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BNE<Relative>(Relative);

template <typename T> void CPU::
BPL(T addr)
{
	if (!N) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BPL<Relative>(Relative);

void CPU::
BRK()
{
	pc++;

	unsigned char h = pc >> 8;
	unsigned char l = pc & 0xFF;
	push(h);
	push(l);

	unsigned char flags = get_flags();

	push(flags |= 0x10);

	l = read(0xFFFE);
	h = read(0xFFFF);

	pc = h << 8;
	pc |= l;
}

template <typename T> void CPU::
BVC(T addr)
{
	if (!V) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BVC<Relative>(Relative);

template <typename T> void CPU::
BVS(T addr)
{
	if (V) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BVS<Relative>(Relative);

void CPU::
CLC()
{
	C = 0;
}
void CPU::
CLD()
{
	D = 0;
}
void CPU::
CLI()
{
	I = 0;
}
void CPU::
CLV()
{
	V = 0;
}

template <typename T> void CPU::
CMP(T addr)
{
	unsigned char arg = addr.read(*this);
	unsigned char t = acc - arg;

	N = (t >> 7) & 0x1;
	C = (acc >= arg);
	Z = (t == 0);
}

template void CPU::CMP<Immediate>(Immediate);
template void CPU::CMP<Address>(Address);

template <typename T> void CPU::
CPX(T addr)
{
	unsigned char arg = addr.read(*this);
	unsigned char t = x - arg;

	N = (t >> 7) & 0x1;
	C = (x >= arg);
	Z = (t == 0);
}

template void CPU::CPX<Immediate>(Immediate);
template void CPU::CPX<Address>(Address);

template <typename T> void CPU::
CPY(T addr)
{
	unsigned char arg = addr.read(*this);
	unsigned char t = y - arg;

	N = (t >> 7) & 0x1;
	C = (y >= arg);
	Z = (t == 0);
}

template void CPU::CPY<Immediate>(Immediate);
template void CPU::CPY<Address>(Address);

template <typename T> void CPU::
DEC(T addr)
{
	unsigned char arg = addr.read(*this);
	arg--;
	arg &= 0xFF;

	N = (arg >> 7) & 0x1;
	Z = (arg == 0);

	addr.write(*this, arg);
}

template void CPU::DEC<Address>(Address);

void CPU::
DEX()
{
	x--;

	Z = (x == 0);
	N = (x >> 7) & 0x1;
}

void CPU::
DEY()
{
	y--;

	Z = (y == 0);
	N = (y >> 7) & 0x1;
}

} /* namespace emu */
} /* namespace domahony */

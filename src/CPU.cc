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
#include <vector>
#include <functional>

namespace domahony {
namespace emu {

using std::vector;
using std::function;

static unsigned char BCD(unsigned char);

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

	fn[0xa5] = [] (CPU& cpu) {

		std::cout << "Executing" << std::endl;
		unsigned char addr = cpu.read(cpu.pc++);
		cpu.acc = cpu.read(addr);

		std::cout << "Acc Value: " << cpu.acc << std::endl;
		return 1;
	};

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
ADC(unsigned char arg)
{
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

void CPU::
AND(unsigned char value)
{
	acc = acc & (value & 0xFF);
	N = acc >> 7;
	Z = acc == 0;
	/*
	A = A & M
	P.N = A.7
	P.Z = (A==0) ? 1:0
	*/
}

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

static unsigned char
BCD(unsigned char v)
{
	unsigned char tens = (v >> 4) * 10;
	unsigned char ones = v & 0x0F;

	return tens + ones;
}


Address CPU::
getImmediate()
{

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

}

Address CPU::
getRelative()
{

}

Address CPU::
getAbsoluteIdxWithX()
{

}

Address CPU::
getAbsoluteIdxWithY()
{

}

Address CPU::
getZpIdxWithX()
{

}

Address CPU::
getZpIdxWithY()
{

}

Address CPU::
getZpIdxIndirect()
{

}

Address CPU::
getZpIndirectIdxWithY()
{

}


} /* namespace emu */
} /* namespace domahony */


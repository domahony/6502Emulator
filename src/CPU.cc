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

Address CPU::
getRelative()
{

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


} /* namespace emu */
} /* namespace domahony */


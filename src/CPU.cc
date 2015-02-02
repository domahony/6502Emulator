/*
 * CPU.cc
 *
 *  Created on: Feb 1, 2015
 *      Author: domahony
 */

#include "CPU.h"
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

	fn[0x69] = [](CPU& cpu) {
		unsigned char val = cpu.read(cpu.pc++);
		cpu.ADC(val);
		return 2;
	};

	fn[0x6D] = [](CPU& cpu) {
		unsigned short low = cpu.read(cpu.pc++);
		unsigned short val = cpu.read(cpu.pc++);

		val << 8;
		val += low;

		cpu.ADC(val);
		return 4;
	};

	fn[0x7D] = [](CPU& cpu) {
		unsigned short low = cpu.read(cpu.pc++);
		unsigned short val = cpu.read(cpu.pc++);

		val << 8;
		val += low;

		cpu.ADC(val + static_cast<char>(cpu.x));
		return 4;
	};

	fn[0x79] = [](CPU& cpu) {
		unsigned short low = cpu.read(cpu.pc++);
		unsigned short val = cpu.read(cpu.pc++);

		val << 8;
		val += low;

		cpu.ADC(val + static_cast<char>(cpu.y));
		return 4;
	};

	fn[0x61] = [](CPU& cpu) {
		unsigned short addr = cpu.read(cpu.pc++);
		addr += static_cast<char>(cpu.x);

		unsigned short low = cpu.read(addr);
		unsigned short val = cpu.read(addr+1);

		val << 8;
		val += low;

		val = cpu.read(val);

		cpu.ADC(val);
		return 6;
	};

	fn[0x71] = [](CPU& cpu) {
		unsigned short addr = cpu.read(cpu.pc++);

		unsigned short low_addr = cpu.read(addr);
		unsigned short high_addr = cpu.read(addr+1);

		high_addr << 8;
		high_addr += low_addr;

		high_addr += static_cast<char>(cpu.y);

		unsigned short val = cpu.read(high_addr);

		cpu.ADC(val);
		return 5;
	};

	fn[0x65] = [](CPU& cpu) {
		unsigned char addr = cpu.read(cpu.pc++);
		unsigned char val = cpu.read(addr);

		cpu.ADC(val);
		return 3;
	};

	fn[0x75] = [](CPU& cpu) {
		unsigned char addr = cpu.read(cpu.pc++);
		unsigned char val = cpu.read(addr + static_cast<char>(cpu.x));

		cpu.ADC(val);
		return 4;
	};

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

int CPU::
ADC(unsigned short value)
{
	unsigned short val = acc + value + (C ? 1 : 0);

	V = ((val >> 7) != (acc >> 7));
	N = (acc >> 7) & 0x1;
	Z = (val == 0);

	if (D) {
		val = BCD(acc) + BCD(value) + (C ? 1 : 0);
		C = val > 99;
	} else {
		C = val > 255;
	}

	acc = val & 0xFF;

}

static unsigned char
BCD(unsigned char v)
{
	unsigned char tens = (v >> 4) * 10;
	unsigned char ones = v & 0x0F;

	return tens + ones;
}

} /* namespace emu */
} /* namespace domahony */


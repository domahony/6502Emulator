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

CPU::
CPU(std::shared_ptr<domahony::emu::ROM> rom) : rom(rom) {

	unsigned char low = read(0xFFFa);
	unsigned char high = read(0xFFFa + 1);

	pc = (high << 8) + low;

	std::cout << "Initial PC: " << std::hex << pc << std::endl;

	ram.resize(0xFFFF);

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

} /* namespace emu */
} /* namespace domahony */


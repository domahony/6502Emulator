/*
 * Emulator.cc
 *
 *  Created on: Jan 30, 2015
 *      Author: domahony
 */

#include <iostream>
#include "Emulator.h"
#include "ROM.h"

namespace domahony {
namespace emu {

using std::cout;
using std::endl;

Emulator::Emulator(std::shared_ptr<domahony::emu::ROM> rom): rom(rom), pc(0xFFFC)   {
	// TODO Auto-generated constructor stub

}

void Emulator::
run() {
	auto op = fetch();

	cout << "Executing " << std::hex << "'" << 78 << "'" << endl;
	cout << "Executing " << std::hex << "'" << op << "'" << endl;
}

unsigned char Emulator::
fetch() {
	return read(pc++);
}

void Emulator::
execute(unsigned char op)
{

}

unsigned char Emulator::
read(unsigned short addr)
{

	if (addr < 0x8000) {
		return ram[addr];
	} else {
		return rom->fetch(addr - 0x8000);
	}

}
/*
std::function<void ()> Emulator::
decode(unsigned char op) {

	return [pc](){

		auto hb = rom->fetch(pc++);
		auto lb = rom->fetch(pc++);

		A = read_memory(hb, lb, A);
		X = A;

	};

}
*/

Emulator::~Emulator() {
	// TODO Auto-generated destructor stub
}

} /* namespace emu */
} /* namespace domahony */

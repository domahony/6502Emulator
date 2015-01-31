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

Emulator::Emulator(std::shared_ptr<domahony::emu::ROM> rom): rom(rom)   {

	unsigned char low = read(0xFFFC);
	unsigned char high = read(0xFFFC + 1);

	pc = (high << 8) + low;

	std::cout << "Initial PC: " << std::hex << pc << std::endl;

}

void Emulator::
run() {
	unsigned int op = fetch();
	cout << "Executing " << std::hex << "'" << std::hex << op << "'" << endl;

	unsigned int l;
	unsigned int h;
	unsigned short value;

	bool done = false;

	while (!done) {

		switch (op) {
			case 0x78:
				cout << "Executing SEI" << endl;
				break;
			case 0x8c:
				cout << "STY $A5B6" << endl;
				l = read(pc++);
				h = read(pc++);

				value = (h << 8) + l;
				cout << "STY " << std::hex << value << endl;

				break;

			case 0x88:
				cout << "DEY" << endl;
				y -= 1;
				N = (y >> 7) & 0x1;
				Z = (y == 0);
				break;

			case 0xa2:
				cout << "LDX #$A5" << endl;
				l = read(pc++);
				cout << "Loading X with Value " << std::hex << l << endl;
				x = l;
				N = (x >> 7) & 0x1;
				Z = (x == 0);
				break;

			case 0xd0:
				cout << "BNE $A5" << endl;
				l = read(pc++);

				if (!Z) {
					pc = pc + l;
					cout << "Setting PC to " << std::hex << pc << endl;
				}

				break;

			default:
				done = true;
				break;
		}

		if (!done) {
			op = fetch();
			cout << "Executing " << std::hex << "'" << std::hex << op << "'" << endl;
		}
	}

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

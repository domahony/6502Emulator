/*
 * ROM.cc
 *
 *  Created on: Jan 30, 2015
 *      Author: domahony
 */

#include "ROM.h"

#include <iostream>
#include <fstream>
#include <cmath>

namespace domahony {
namespace emu {

ROM::ROM(const string& fname) : rom() {

	std::ifstream testFile(fname.c_str(), std::ios::binary);

	rom.assign((std::istreambuf_iterator<char>(testFile)), std::istreambuf_iterator<char>());

	int bits = floor( log2(rom.size() -1) + 1 );

	std::cout << "N bits " << bits << std::endl;
	std::cout << "Size " << std::hex << rom.size() -1 << std::endl;

	mask = (1 << bits) -1;

	bits = floor( log2(65533) + 1 );
	std::cout << "N bits " << std::dec << bits << std::endl;
	std::cout << "Addr " << std::dec << 0xfffd << std::endl;
	std::cout << "Addr (masked) " << std::hex << (0xfffd & mask) << std::endl;
	std::cout << "Max " << std::hex << mask << std::endl;

}

ROM::~ROM() {
	// TODO Auto-generated destructor stub
}

} /* namespace emu */
} /* namespace domahony */

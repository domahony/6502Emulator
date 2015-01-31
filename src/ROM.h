/*
 * ROM.h
 *
 *  Created on: Jan 30, 2015
 *      Author: domahony
 */

#ifndef ROM_H_
#define ROM_H_

#include <iostream>
#include <vector>
#include <string>

namespace domahony {
namespace emu {

using std::string;
using std::vector;

class ROM {
public:
	ROM(const string&);
	virtual ~ROM();

	unsigned char fetch(unsigned short addr) {

		int x = rom.at(addr & mask);

		std::cout << "Request for addr: " << std::hex << addr << std::endl;
		std::cout << "Request for addr (masked): " << std::hex << (addr & mask) << std::endl;
		std::cout << "Request for addr (masked): " << std::dec << (addr & mask) << std::endl;
		std::cout << "Request for addr (value): " << std::hex << static_cast<unsigned char>(rom.at(addr & mask)) << std::endl;
		std::cout << "Request for addr (value): " << std::dec << x << std::endl;
		std::cout << "Request for addr (value): " << std::hex << x << std::endl;

		return rom.at(addr & mask);
	}

private:
	vector<unsigned char> rom;
	unsigned int mask;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* ROM_H_ */

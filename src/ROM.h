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
		return rom.at(addr & mask);
	}

private:
	vector<unsigned char> rom;
	unsigned int mask;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* ROM_H_ */

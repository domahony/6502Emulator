/*
 * ROM.h
 *
 *  Created on: Jan 30, 2015
 *      Author: domahony
 */

#ifndef ROM_H_
#define ROM_H_

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

	unsigned char fetch(short addr) {
		return rom[addr];
	}

private:
	vector<unsigned char> rom;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* ROM_H_ */

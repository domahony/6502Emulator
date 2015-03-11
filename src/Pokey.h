/*
 * Pokey.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef POKEY_H_
#define POKEY_H_

namespace domahony {
namespace emu {

class Pokey {
public:
	Pokey();
	virtual ~Pokey();

	unsigned char read(unsigned short addr) const {

	}
	void write(unsigned short addr, unsigned char val) {

	}

};
} /* namespace emu */
} /* namespace domahony */

#endif /* POKEY_H_ */

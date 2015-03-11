/*
 * PIA.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef PIA_H_
#define PIA_H_

namespace domahony {
namespace emu {

class PIA {
public:
	PIA();
	virtual ~PIA();

	unsigned char read(unsigned short addr) const {

	}

	void write(unsigned short addr, unsigned char val) {

	}

};

} /* namespace emu */
} /* namespace domahony */

#endif /* PIA_H_ */

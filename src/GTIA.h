/*
 * GTIA.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef GTIA_H_
#define GTIA_H_

namespace domahony {
namespace emu {

class GTIA {
public:
	GTIA();
	virtual ~GTIA();

	unsigned char read(unsigned short addr) const {

	}

	void write(unsigned short addr, unsigned char val) {

	}

};

} /* namespace emu */
} /* namespace domahony */

#endif /* GTIA_H_ */

/*
 * AddressSelector.h
 *
 *  Created on: Mar 11, 2015
 *      Author: domahony
 */

#ifndef ADDRESSSELECTOR_H_
#define ADDRESSSELECTOR_H_

#include "AddressSpace.h"

namespace domahony {
namespace emu {
namespace v2 {

template <unsigned char N>
class AddressSelector {
public:
	AddressSelector() {

	}

	virtual ~AddressSelector() {

	}
};

template <>
class AddressSelector<0> {

public:
	AddressSelector(domahony::emu::AddressSpace& as, unsigned short offset) : offset(offset), address_space(as) {

	}

	virtual ~AddressSelector() {

	}

	unsigned char read(unsigned short addr) const {
		return address_space.ram->read(addr - offset);
	}

private:
	unsigned short offset;
	AddressSpace address_space;
};

} /* namespace v2 */
} /* namespace emu */
} /* namespace domahony */

#endif /* ADDRESSSELECTOR_H_ */

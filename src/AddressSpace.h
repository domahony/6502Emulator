/*
 * AddressSpace.h
 *
 *  Created on: Mar 4, 2015
 *      Author: domahony
 */

#ifndef ADDRESSSPACE_H_
#define ADDRESSSPACE_H_

#include <memory>
#include <vector>
#include "Bus.h"

namespace domahony {
namespace emu {

class AddressSpace {

public:
	AddressSpace();

	unsigned char read(unsigned short) const;
	void write(unsigned short, unsigned char);

	virtual ~AddressSpace();

private:
	Bus<RAM> ram;
	Bus<ROM> cartridgeB;
	Bus<ROM> cartridgeA;
	Bus<GTIA> gtia;
	Bus<Pokey> pokey;
	Bus<PIA> pia;
	Bus<ANTIC> antic;
	Bus<ROM> os;

	template<class T> Bus<T> get_bus(unsigned short);
	template<class T> Bus<T> get_bus(unsigned short) const;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* ADDRESSSPACE_H_ */


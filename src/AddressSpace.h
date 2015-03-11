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
#include "RAM.h"
#include "ROM.h"
#include "GTIA.h"
#include "Pokey.h"
#include "PIA.h"
#include "ANTIC.h"

namespace domahony {
namespace emu {


class AddressSpace {

public:
	AddressSpace();

	unsigned char read(unsigned short) const;
	void write(unsigned short, unsigned char);

	unsigned char read2(unsigned short addr) const {

		if (addr > 0xD800) {
			return readX<ROM>(addr - 0xD800, os);
		}

		return 0;
	}

	virtual ~AddressSpace();

private:

	template<typename T> unsigned char readX(unsigned short addr, std::shared_ptr<T> t) const {
		return t->read(addr);
	}

	std::shared_ptr<RAM> ram;
	std::shared_ptr<ROM> cartridgeB;
	std::shared_ptr<ROM> cartridgeA;
	std::shared_ptr<GTIA> gtia;
	std::shared_ptr<Pokey> pokey;
	std::shared_ptr<PIA> pia;
	std::shared_ptr<ANTIC> antic;
	std::shared_ptr<ROM> os;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* ADDRESSSPACE_H_ */


/*
 * AddressSpace.h
 *
 *  Created on: Mar 4, 2015
 *      Author: domahony
 */

#ifndef ADDRESSSPACE_H_
#define ADDRESSSPACE_H_

#include <memory>
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
	std::shared_ptr<Bus> ram;
	std::shared_ptr<Bus> cartridgeB;
	std::shared_ptr<Bus> cartridgeA;
	std::shared_ptr<Bus> gtia;
	std::shared_ptr<Bus> pokey;
	std::shared_ptr<Bus> pia;
	std::shared_ptr<Bus> antic;
	std::shared_ptr<Bus> os;

	std::shared_ptr<Bus> get_bus(unsigned short);
	std::shared_ptr<Bus> get_bus(unsigned short) const;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* ADDRESSSPACE_H_ */

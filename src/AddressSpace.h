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

struct BusHolder {

	BusHolder(std::shared_ptr<Bus> bus, int offset) : bus(bus), offset(offset)
	{

	}

	BusHolder() : bus(0), offset(0) {

	}

	std::shared_ptr<Bus> bus;
	int offset;
};

public:
	AddressSpace();

	unsigned char read(unsigned short) const;
	void write(unsigned short, unsigned char);

	virtual ~AddressSpace();

private:
	BusHolder ram;
	BusHolder cartridgeB;
	BusHolder cartridgeA;
	BusHolder gtia;
	BusHolder pokey;
	BusHolder pia;
	BusHolder antic;
	BusHolder os;
	/*
	std::shared_ptr<Bus> ram;
	std::shared_ptr<Bus> cartridgeB;
	std::shared_ptr<Bus> cartridgeA;
	std::shared_ptr<Bus> gtia;
	std::shared_ptr<Bus> pokey;
	std::shared_ptr<Bus> pia;
	std::shared_ptr<Bus> antic;
	std::shared_ptr<Bus> os;
	*/

	BusHolder get_bus(unsigned short);
	BusHolder get_bus(unsigned short) const;
};

} /* namespace emu */
} /* namespace domahony */

#endif /* ADDRESSSPACE_H_ */

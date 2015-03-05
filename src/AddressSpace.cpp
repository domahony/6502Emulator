/*
 * AddressSpace.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: domahony
 */

#include "AddressSpace.h"

namespace domahony {
namespace emu {

using std::shared_ptr;

AddressSpace::AddressSpace() {

}

AddressSpace::~AddressSpace() {

}

shared_ptr<Bus> AddressSpace::
get_bus(unsigned short addr) const {

	if (addr < 0x8000) {
		return ram;
	} else if (addr < 0xA000) {
		return cartridgeB;
	} else if (addr < 0xD000) {
		return cartridgeA;
	} else if (addr < 0xD200) {
		return gtia;
	} else if (addr < 0xD300) {
		return pokey;
	} else if (addr < 0xD400) {
		return pia;
	} else if (addr < 0xD800) {
		return antic;
	} else {
		return os;
	}

}

shared_ptr<Bus> AddressSpace::
get_bus(unsigned short addr) {

	if (addr < 0x8000) {
		return ram;
	} else if (addr < 0xA000) {
		return cartridgeB;
	} else if (addr < 0xD000) {
		return cartridgeA;
	} else if (addr < 0xD200) {
		return gtia;
	} else if (addr < 0xD300) {
		return pokey;
	} else if (addr < 0xD400) {
		return pia;
	} else if (addr < 0xD800) {
		return antic;
	} else {
		return os;
	}

}

unsigned char AddressSpace::
read(unsigned short addr) const
{
	shared_ptr<Bus> bus = get_bus(addr);
	return bus->read(addr);
}

void AddressSpace::
write(unsigned short addr, unsigned char val)
{
	shared_ptr<Bus> bus = get_bus(addr);
	bus->write(addr, val);
}

} /* namespace emu */
} /* namespace domahony */

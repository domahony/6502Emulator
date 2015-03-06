/*
 * AddressSpace.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: domahony
 */

#include <iostream>
#include "AddressSpace.h"
#include "ROM.h"
#include "RAM.h"

namespace domahony {
namespace emu {

using std::shared_ptr;

AddressSpace::AddressSpace() :
os(BusHolder(
		shared_ptr<ROM>(new ROM("/home/domahony/Projects/atariROMs/ATARIOSB.ROM")),
		0xD800)),
cartridgeA(BusHolder(
		shared_ptr<ROM>(new ROM("/home/domahony/Projects/atariROMs/REVA.ROM")),
		0xA000)),
ram(BusHolder(
		shared_ptr<RAM>(new RAM(0x8000)),
		0x0
		)),
cartridgeB(BusHolder(
		shared_ptr<RAM>(new RAM(0xA000 - 0x8000)),
		0x8000))
{

}

AddressSpace::~AddressSpace() {

}

AddressSpace::BusHolder AddressSpace::
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

AddressSpace::BusHolder AddressSpace::
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
	BusHolder bh = get_bus(addr);

	if (!bh.bus) {
		std::cout << "Attempt to read unknown!! " << addr << std::endl;
	}

	return bh.bus->read(addr - bh.offset);
}

void AddressSpace::
write(unsigned short addr, unsigned char val)
{
	BusHolder bh = get_bus(addr);

	if (!bh.bus) {
		std::cout << "Attempt to write unknown!! " << addr << std::endl;
	}
	bh.bus->write(addr - bh.offset, val);
}

} /* namespace emu */
} /* namespace domahony */

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
#include <AddressSpace.h>

namespace domahony {
namespace emu {

using std::shared_ptr;

AddressSpace::AddressSpace() :
		os(
				BusHolder(
						shared_ptr<ROM>(
								new ROM(
										"/home/domahony/Projects/atariROMs/ATARIOSB.ROM")),
						0xD800)), cartridgeA(
				BusHolder(
						shared_ptr<ROM>(
								new ROM(
										"/home/domahony/Projects/atariROMs/REVA.ROM")),
						0xA000)), ram(
				BusHolder(shared_ptr<RAM>(new RAM(0x8000)), 0x0)), cartridgeB(
				BusHolder(shared_ptr<RAM>(new RAM(0xA000 - 0x8000)), 0x8000)) {

}

AddressSpace::~AddressSpace() {

}

template<class T>
Bus<T> AddressSpace::get_bus(unsigned short addr) const {

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

template<class T>
Bus<T> AddressSpace::get_bus(unsigned short addr) {

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

template<class T>
unsigned char AddressSpace::read(unsigned short addr) const {
	Bus<T> bus = get_bus(addr);

	return bus.read(addr - bus.offset);
}

template<class T>
void AddressSpace::write(unsigned short addr, unsigned char val) {
	Bus<T> bus = get_bus(addr);

	bus.write(addr - bus.offset, val);
}

} /* namespace emu */
} /* namespace domahony */

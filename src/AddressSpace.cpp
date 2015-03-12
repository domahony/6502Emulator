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

template<unsigned char N> struct AddrTraits {
    enum{D =
    		(N > 0xD800 ? 7 :
    		(N > 0xD700 ? 6 :
    		(N > 0xD600 ? 5 :
    		(N > 0xD500 ? 4 :
    		0))))
    };

     enum{OFFSET =
    		(N > 0xD800 ? 0xD800 :
    		(N > 0xD700 ? 0xD700 :
    		(N > 0xD600 ? 0xD600 :
    		(N > 0xD500 ? 0xD500 :
    		0))))
    };
};

AddressSpace::AddressSpace() :
		os(new ROM("/home/domahony/Projects/atariROMs/ATARIOSB.ROM")),
		cartridgeA(new ROM("/home/domahony/Projects/atariROMs/REVA.ROM")),
		ram(new RAM(0xA000))
{

	const unsigned short addr = 50;
	auto val = read_address<AddrTraits<addr>::D>(addr - AddrTraits<addr>::OFFSET);
}

AddressSpace::~AddressSpace() {

}

unsigned char AddressSpace::read(const unsigned short addr) const {

	if (addr > 0xD800) {
		return os->read(addr - 0xD800);
	} else if (addr > 0xD400) {
		return antic->read(addr - 0xD400);
	} else if (addr > 0xD300) {
		return pia->read(addr - 0xD300);
	} else if (addr > 0xD200) {
		return pokey->read(addr - 0xD200);
	} else if (addr > 0xD000) {
		return gtia->read(addr - 0xD000);
	} else if (addr > 0xA000) {
		return cartridgeA->read(addr - 0xA000);
	} else if (addr > 0x8000) {
		return cartridgeB->read(addr - 0x8000);
	} else {
		return ram->read(addr);
	}
}

void AddressSpace::write(unsigned short addr, unsigned char val) {

	if (addr > 0xD800) {
		os->write(addr - 0xD800, val);
	} else if (addr > 0xD400) {
		antic->write(addr - 0xD400, val);
	} else if (addr > 0xD300) {
		pia->write(addr - 0xD300, val);
	} else if (addr > 0xD200) {
		pokey->write(addr - 0xD200, val);
	} else if (addr > 0xD000) {
		gtia->write(addr - 0xD000, val);
	} else if (addr > 0xA000) {
		cartridgeA->write(addr - 0xA000, val);
	} else if (addr > 0x8000) {
		cartridgeB->write(addr - 0x8000, val);
	} else {
		ram->write(addr, val);
	}
}

template<>
unsigned char AddressSpace::
read_address<0>(unsigned char addr)
{
	return ram->read(addr);
}

template<>
unsigned char AddressSpace::
read_address<1>(unsigned char addr)
{
	return cartridgeB->read(addr);
}

} /* namespace emu */
} /* namespace domahony */

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

AddressSpace::AddressSpace() :
		os(new ROM("/home/domahony/Projects/atariROMs/new/REVBNTSC.ROM")),
		cartridgeA(new ROM("/home/domahony/Projects/atariROMs/REVA.ROM")),
		ram(new RAM(0xA000)),
		ramB(new RAM(0x8000))
{


}

AddressSpace::~AddressSpace() {

}

unsigned char AddressSpace::read(const unsigned short addr) const {

	if (addr >= 0xD800) {
		return os->read(addr - 0xD800);
	} else if (addr >= 0xD400) {
		return antic->read(addr - 0xD400);
	} else if (addr >= 0xD300) {
		return pia->read(addr - 0xD300);
	} else if (addr >= 0xD200) {
		return pokey->read(addr - 0xD200);
	} else if (addr >= 0xD000) {
		return gtia->read(addr - 0xD000);
	} else if (addr >= 0xA000) {
		return cartridgeA->read(addr - 0xA000);
	} else if (addr >= 0x8000) {

		if (cartridgeB) {
			return cartridgeB->read(addr - 0x8000);
		} else {
			return ramB->read(addr - 0x8000);
		}


	} else {
		return ram->read(addr);
	}
}

void AddressSpace::write(unsigned short addr, unsigned char val) {

	if (addr >= 0xD800) {
		os->write(addr - 0xD800, val);
	} else if (addr >= 0xD400) {
		antic->write(addr - 0xD400, val);
	} else if (addr >= 0xD300) {
		pia->write(addr - 0xD300, val);
	} else if (addr >= 0xD200) {
		pokey->write(addr - 0xD200, val);
	} else if (addr >= 0xD000) {
		gtia->write(addr - 0xD000, val);
	} else if (addr >= 0xA000) {
		cartridgeA->write(addr - 0xA000, val);
	} else if (addr >= 0x8000) {

		if (cartridgeB) {
			cartridgeB->write(addr - 0x8000, val);
		} else {
			ramB->write(addr - 0x8000, val);
		}


	} else {
		ram->write(addr, val);
	}
}

} /* namespace emu */
} /* namespace domahony */

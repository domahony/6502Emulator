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

template<unsigned short N> struct select {typedef domahony::emu::RAM result; };
template<> struct select<7> {typedef domahony::emu::ROM result; };
template<> struct select<6> {typedef domahony::emu::ANTIC result; };
template<> struct select<5> {typedef domahony::emu::PIA result; };
template<> struct select<4> {typedef domahony::emu::Pokey result; };
template<> struct select<3> {typedef domahony::emu::GTIA result; };
template<> struct select<2> {typedef domahony::emu::ROM result; };
template<> struct select<1> {typedef domahony::emu::ROM result; };
template<> struct select<0> {typedef domahony::emu::RAM result; };

template<unsigned short N>
struct BusX
{
	unsigned short offsets[] = {
	0xD800,
	0xD400,
	0xD300,
	0xD200,
	0xD000,
	0xA000,
	0x8000,
	0 };

	enum{D = (N > offsets[7] ? 7 :
			(N > offsets[6] ? 6 :
			(N > offsets[5] ? 5 :
			(N > offsets[4] ? 4 :
			(N > offsets[3] ? 3 :
			(N > offsets[2] ? 2 :
			(N > offsets[1] ? 1 :
			0)))))))
	};

	enum {OFFSET = offsets[D]};
	typedef typename select<D>::result value_type;

};

template<class T>
class Bus
{
public:
	unsigned char read(unsigned short addr) const {
		return value.read(addr - offset);
	}

	void write(unsigned short addr, unsigned char val) {
			value.write(addr - offset, val);
	}

private:
	unsigned short offset = T::OFFSET;
	typename T::value_type value;
};

AddressSpace::AddressSpace()

		/*
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
		*/
{
	auto x = 255;

	Bus<BusX<x>> bus;
	auto zz = bus.read(x);
	bus.write(x, zz);

	Bus<BusX<0>> ram;

	ram.value = domahony::emu::ROM("");
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

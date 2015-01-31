/*
 * Emulator.h
 *
 *  Created on: Jan 30, 2015
 *      Author: domahony
 */

#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <memory>
#include <vector>

namespace domahony {
namespace emu {

class ROM;

class Emulator {
public:
	Emulator(std::shared_ptr<domahony::emu::ROM>);
	void run();

	virtual ~Emulator();

private:
	unsigned char fetch();
	unsigned char read(unsigned short addr);
	void write(short addr, unsigned char val);

	void execute(unsigned char);

	std::shared_ptr<domahony::emu::ROM> rom;
	std::vector<unsigned char> ram;
	bool N,V,B,D,I,Z,C;

	unsigned short pc; //program counter;
	unsigned char sp; // stack pointer;
	unsigned char acc; //accumulator
	unsigned char x; // X register
	unsigned char y; // Y register

};

} /* namespace emu */
} /* namespace domahony */

#endif /* EMULATOR_H_ */

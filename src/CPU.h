/*
 * CPU.h
 *
 *  Created on: Feb 1, 2015
 *      Author: domahony
 */

#ifndef CPU_H_
#define CPU_H_

#include "ROM.h"
#include <memory>
#include <vector>
#include <functional>

namespace domahony {
namespace emu {

class CPU {
public:
	CPU(std::shared_ptr<domahony::emu::ROM> rom);

	virtual ~CPU() {

	}

	void run();

	std::shared_ptr<domahony::emu::ROM> rom;
	std::vector<unsigned char> ram;

	unsigned char read(unsigned short);

	bool N,V,B,D,I,Z,C;

	unsigned short pc; //program counter;
	unsigned char sp; // stack pointer;
	unsigned char acc; //accumulator
	unsigned char x; // X register
	unsigned char y; // Y register

	std::function<int (CPU&)> fn[255];

private:
	void init();

	void ADC(unsigned short value);
	void AND(unsigned short value);
	void LDA(unsigned short addr);
};

} /* namespace emu */
} /* namespace domahony */

#endif /* CPU_H_ */

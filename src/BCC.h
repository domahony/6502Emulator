/*
 * BCC.h
 *
 *  Created on: Feb 8, 2015
 *      Author: domahony
 */

#ifndef BCC_H_
#define BCC_H_

#include "CPU.h"

void initBCC(std::function<int (domahony::emu::CPU&)> *fn);
void initBCS(std::function<int (domahony::emu::CPU&)> *fn);
void initBEQ(std::function<int (domahony::emu::CPU&)> *fn);


#endif /* ADC_H_ */

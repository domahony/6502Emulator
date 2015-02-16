/*
 * LDX_Y.h
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */

#ifndef LDX_Y_H_
#define LDX_Y_H_

#include "CPU.h"

void initLDX(std::function<int (domahony::emu::CPU&)> *fn);
void initLDY(std::function<int (domahony::emu::CPU&)> *fn);


#endif

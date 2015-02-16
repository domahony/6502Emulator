/*
 * INX_Y.h
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */

#ifndef INX_Y_H_
#define INX_Y_H_

#include "CPU.h"

void initINX(std::function<int (domahony::emu::CPU&)> *fn);
void initINY(std::function<int (domahony::emu::CPU&)> *fn);


#endif

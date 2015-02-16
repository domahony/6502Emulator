/*
 * DEX_Y.h
 *
 *  Created on: Feb 15, 2015
 *      Author: domahony
 */

#ifndef DEX_Y_H_
#define DEX_Y_H_

#include "CPU.h"

void initDEX(std::function<int (domahony::emu::CPU&)> *fn);
void initDEY(std::function<int (domahony::emu::CPU&)> *fn);


#endif

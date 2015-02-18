/*
 * STX_Y.h
 *
 *  Created on: Feb 18, 2015
 *      Author: domahony
 */

#ifndef STX_Y_H_
#define STX_Y_H_

#include "CPU.h"

void initSTX(std::function<int (domahony::emu::CPU&)> *fn);
void initSTY(std::function<int (domahony::emu::CPU&)> *fn);


#endif

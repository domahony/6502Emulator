/*
 * Stack.h
 *
 *  Created on: Feb 17, 2015
 *      Author: domahony
 */

#ifndef STACK_H_
#define STACK_H_


#include "CPU.h"

void initStack(std::function<int (domahony::emu::CPU&)> *fn);

#endif /* STACK_H_ */

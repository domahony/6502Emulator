/*
 * ADC.h
 *
 *  Created on: Feb 3, 2015
 *      Author: domahony
 */

#ifndef ADC_H_
#define ADC_H_

#include "CPU.h"

void initADC(std::function<int (domahony::emu::CPU&)> *fn);


#endif /* ADC_H_ */

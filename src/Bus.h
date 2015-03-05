/*
 * Bus.h
 *
 *  Created on: Mar 4, 2015
 *      Author: domahony
 */

#ifndef BUS_H_
#define BUS_H_

namespace domahony {
namespace emu {

class Bus {
public:
	Bus();

	virtual unsigned char read(unsigned short addr) const = 0;
	virtual void write(unsigned short, unsigned char) = 0;

	virtual ~Bus();
};

} /* namespace emu */
} /* namespace domahony */

#endif /* BUS_H_ */

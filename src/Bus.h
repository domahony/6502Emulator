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

template<class T>
class Bus : public T {
public:
	Bus();

	unsigned char read(unsigned short addr) const;
	void write(unsigned short, unsigned char);

	virtual ~Bus();
};

} /* namespace emu */
} /* namespace domahony */

#endif /* BUS_H_ */

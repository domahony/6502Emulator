/*
 * ROM.cc
 *
 *  Created on: Jan 30, 2015
 *      Author: domahony
 */

#include "ROM.h"
#include <fstream>
#include <iterator>
#include <algorithm>

namespace domahony {
namespace emu {

using std::fstream;

ROM::ROM(const string& fname) {
	// TODO Auto-generated constructor stub

	fstream f(fname.c_str(), std::ios_base::in);

	std::istream_iterator<unsigned char> eos;              // end-of-stream iterator
	std::istream_iterator<unsigned char> fiter(f);   // stdin iterator

	std::back_insert_iterator< std::vector<unsigned char> > back_it (rom);

	std::copy(fiter, eos, back_it);
}

ROM::~ROM() {
	// TODO Auto-generated destructor stub
}

} /* namespace emu */
} /* namespace domahony */

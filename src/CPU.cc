/*
 * CPU.cc
 *
 *  Created on: Feb 1, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ADC.h"
#include "AND.h"
#include "ASL.h"
#include "BCC.h"
#include "BIT.h"
#include "BRK.h"
#include "CLEAROperations.h"
#include "CMP.h"
#include "CPX_Y.h"
#include "DEC.h"
#include "DEX_Y.h"
#include "EOR.h"
#include "INC.h"
#include "INX_Y.h"
#include "JMP.h"
#include "JSR.h"
#include "LDA.h"
#include "LDX_Y.h"
#include "LSR.h"
#include "NOP.h"
#include "ORA.h"
#include "Stack.h"
#include "ROL.h"
#include "ROR.h"
#include "RTI.h"
#include "RTS.h"
#include "SBC.h"
#include "STA.h"
#include "STX_Y.h"
#include "SETOperations.h"
#include "TRANSFEROperations.h"
#include <vector>
#include <functional>
#include <iostream>

namespace domahony {
namespace emu {

using std::vector;
using std::function;
using std::cout;
using std::endl;
using std::hex;


CPU::
CPU(std::shared_ptr<domahony::emu::ROM> rom) : rom(rom) {

	unsigned char low = read(0xFFFa);
	unsigned char high = read(0xFFFa + 1);

	pc = (high << 8) + low;

	std::cout << "Initial PC: " << std::hex << pc << std::endl;

	ram.resize(0xFFFF);

	initADC(fn);
	initAND(fn);
	initASL(fn);
	initBCC(fn);
	initBCS(fn);
	initBEQ(fn);
	initBIT(fn);
	initBMI(fn);
	initBNE(fn);
	initBPL(fn);
	initBRK(fn);
	initCLEAR(fn);
	initCMP(fn);
	initCPX(fn);
	initCPY(fn);
	initDEC(fn);
	initDEX(fn);
	initDEY(fn);
	initEOR(fn);
	initINC(fn);
	initINX(fn);
	initINY(fn);
	initJMP(fn);
	initJSR(fn);
	initLDA(fn);
	initLDX(fn);
	initLDY(fn);
	initLSR(fn);
	initNOP(fn);
	initORA(fn);
	initStack(fn);
	initROL(fn);
	initROR(fn);
	initRTI(fn);
	initRTS(fn);
	initSBC(fn);
	initSET(fn);
	initSTA(fn);
	initSTX(fn);
	initSTY(fn);
	initTRANSFER(fn);
}

unsigned char CPU::
get_flags() const {

	unsigned char ret = 0;

	if (N) ret |= 1;
	ret <<=1;
	if (V) ret |= 1;
	ret <<=2;
	if (B) ret |= 1;
	ret <<=1;
	if (D) ret |= 1;
	ret <<=1;
	if (I) ret |= 1;
	ret <<=1;
	if (Z) ret |= 1;
	ret <<=1;
	if (C) ret |= 1;

	return ret;
}

void CPU::
push(unsigned char b) {

	write(0x100 | sp, b);
	sp -= 1;

}

unsigned char CPU::
pop() {
	++sp;
	return read(0x100 | sp);
}

void CPU::
run() {

	while (true) {
		unsigned char op = read(pc++);
		int tick = 0;
		fn[op](*this);
	}
}

unsigned char CPU::
read(unsigned short addr)
{
	if (addr < 0xA000) {
		return ram[addr];
	} else {
		return rom->fetch(addr - 0xA000);
	}
}


void CPU::
write(unsigned short addr, unsigned char val)
{
	if (addr < 0xA000) {
		ram[addr] == val;
	}
}

unsigned char
BCD(unsigned char v)
{
	unsigned char tens = (v >> 4) * 10;
	unsigned char ones = v & 0x0F;

	return tens + ones;
}


Immediate CPU::
getImmediate()
{
	Immediate ret(read(pc++));
	return ret;
}

Address CPU::
getAbsolute()
{
	unsigned char low = read(pc++);
	unsigned char high = read(pc++);

	return Address(low, high);
}

Address CPU::
getIndirect()
{
	unsigned char low = read(pc++);
	unsigned char high = read(pc++);

	unsigned short addr = high << 8;
	addr |= low;

	unsigned char low2 = read(addr);
	unsigned char high2 = read(addr + 1);

	return Address(low2, high2);

}

Address CPU::
getZp()
{
	unsigned char low = read(pc++);
	unsigned char high = 0;
	Address addr(low, high);

	return addr;
}

Relative CPU::
getRelative()
{
	unsigned char offset = read(pc++);
	return Relative(pc, static_cast<char>(offset));
}

Address CPU::
getAbsoluteIdxWithX()
{
	unsigned char low = read(pc++);
	unsigned char high = read(pc++);

	return Address(low, high, x);
}

Address CPU::
getAbsoluteIdxWithY()
{
	unsigned char low = read(pc++);
	unsigned char high = read(pc++);

	return Address(low, high, y);
}

Address CPU::
getZpIdxWithX()
{
	unsigned char zp = read(pc++);
	zp += x;

	Address addr(zp, 0);
	return addr;
}

Address CPU::
getZpIdxWithY()
{
	unsigned char zp = read(pc++);
	zp += y;

	Address addr(zp, 0);
	return addr;
}

Address CPU::
getZpIdxIndirect()
{
	unsigned char zp = read(pc++);
	zp += static_cast<char>(x);

	unsigned char low = read(zp);
	unsigned char high = read(zp + 1);

	return Address(low, high);
}

Address CPU::
getZpIndirectIdxWithY()
{
	unsigned char zp = read(pc++);

	unsigned char low = read(zp);
	unsigned char high = read(zp + 1);

	return Address(low, high, static_cast<char>(y));
}

template <typename T> void CPU::
AND(T addr)
{
	cout << hex << pc << " AND " << addr << endl;
	unsigned char value = addr.read(*this);

	acc = acc & (value & 0xFF);
	N = acc >> 7;
	Z = acc == 0;
	/*
	A = A & M
	P.N = A.7
	P.Z = (A==0) ? 1:0
	 */
}

template void CPU::AND<Immediate>(Immediate);
template void CPU::AND<Address>(Address);

template <typename T> void CPU::
ASL(T addr)
{
	cout << hex << pc << " ASL " << addr << endl;
	unsigned char value = addr.read(*this);

	C = (value >> 7) & 0x1;
	unsigned char ret = (value << 1) & 0xFE;
	N = (ret >> 7) & 0x1;
	Z = ret == 0;

	addr.write(*this, ret);

	/*
	Logic:
	  P.C = B.7
	  B = (B << 1) & $FE
	  P.N = B.7
	  P.Z = (B==0) ? 1:0
	 */

}

template void CPU::ASL<Accumulator>(Accumulator);
template void CPU::ASL<Address>(Address);

template <typename T> void CPU::
ADC(T addr)
{
	unsigned char arg = addr.read(*this);

	cout << hex << pc << " ADC " << addr << endl;

	unsigned short val = acc + arg + (C ? 1 : 0);

	V = ((val >> 7) != (acc >> 7));
	N = (acc >> 7) & 0x1;
	Z = (val == 0);

	if (D) {
		val = BCD(acc) + BCD(arg) + (C ? 1 : 0);
		C = val > 99;
	} else {
		C = val > 255;
	}

	acc = val & 0xFF;
}

template void CPU::ADC<Immediate>(Immediate);
template void CPU::ADC<Address>(Address);

template <typename T> void CPU::
BCC(T addr)
{
	cout << hex << pc << " BCC " << addr << endl;
	if (!C) {
		pc += static_cast<char>(addr.read(*this));
		addr.set_branch();
	}
}

template void CPU::BCC<Relative>(Relative);

template <typename T> void CPU::
BCS(T addr)
{
	cout << hex << pc << " BCS " << addr << endl;
	if (C) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BCS<Relative>(Relative);

template <typename T> void CPU::
BEQ(T addr)
{
	cout << hex << pc << " BEQ " << addr << endl;
	if (Z) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BEQ<Relative>(Relative);

template <typename T> void CPU::
BIT(T addr)
{
	cout << hex << pc << " BIT " << addr << endl;
	unsigned char t  = acc & addr.read(*this) ;

	N = (t >> 7) && 0x1;
	V = (t >> 6) && 0x1;
	Z = (t == 0);
	/*
	  t = A & M
	  P.N = t.7
	  P.V = t.6
	  P.Z = (t==0) ? 1:0
	*/
}

template void CPU::BIT<Address>(Address);

template <typename T> void CPU::
BMI(T addr)
{
	cout << hex << pc << " BMI " << addr << endl;
	if (N) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BMI<Relative>(Relative);

template <typename T> void CPU::
BNE(T addr)
{
	cout << hex << pc << " BNE " << addr << endl;
	if (!Z) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BNE<Relative>(Relative);

template <typename T> void CPU::
BPL(T addr)
{
	cout << hex << pc << " BPL " << addr << endl;
	if (!N) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BPL<Relative>(Relative);

void CPU::
BRK()
{
	cout << hex << pc << " BRK" << endl;
	pc++;

	unsigned char h = pc >> 8;
	unsigned char l = pc & 0xFF;
	push(h);
	push(l);

	unsigned char flags = get_flags();

	push(flags |= 0x10);

	l = read(0xFFFE);
	h = read(0xFFFF);

	pc = h << 8;
	pc |= l;
	std::exit(0);
}

template <typename T> void CPU::
BVC(T addr)
{
	cout << hex << pc << " BVC " << addr << endl;
	if (!V) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BVC<Relative>(Relative);

template <typename T> void CPU::
BVS(T addr)
{
	cout << hex << pc << " BVS " << addr << endl;
	if (V) {
		pc = addr.read(*this);
		addr.set_branch();
	}
}

template void CPU::BVS<Relative>(Relative);

void CPU::
CLC()
{
	cout << hex << pc << " CLC" << endl;
	C = 0;
}
void CPU::
CLD()
{
	cout << hex << pc << " CLD" << endl;
	D = 0;
}
void CPU::
CLI()
{
	cout << hex << pc << " CLI" << endl;
	I = 0;
}
void CPU::
CLV()
{
	cout << hex << pc << " CLV" << endl;
	V = 0;
}

template <typename T> void CPU::
CMP(T addr)
{
	cout << hex << pc << " CMP " << addr << endl;
	unsigned char arg = addr.read(*this);
	unsigned char t = acc - arg;

	N = (t >> 7) & 0x1;
	C = (acc >= arg);
	Z = (t == 0);
}

template void CPU::CMP<Immediate>(Immediate);
template void CPU::CMP<Address>(Address);

template <typename T> void CPU::
CPX(T addr)
{
	cout << hex << pc << " CMP " << addr << endl;
	unsigned char arg = addr.read(*this);
	unsigned char t = x - arg;

	N = (t >> 7) & 0x1;
	C = (x >= arg);
	Z = (t == 0);
}

template void CPU::CPX<Immediate>(Immediate);
template void CPU::CPX<Address>(Address);

template <typename T> void CPU::
CPY(T addr)
{
	cout << hex << pc << " CPY " << addr << endl;
	unsigned char arg = addr.read(*this);
	unsigned char t = y - arg;

	N = (t >> 7) & 0x1;
	C = (y >= arg);
	Z = (t == 0);
}

template void CPU::CPY<Immediate>(Immediate);
template void CPU::CPY<Address>(Address);

template <typename T> void CPU::
DEC(T addr)
{
	cout << hex << pc << " DEC " << addr << endl;
	unsigned char arg = addr.read(*this);
	arg--;
	arg &= 0xFF;

	N = (arg >> 7) & 0x1;
	Z = (arg == 0);

	addr.write(*this, arg);
}

template void CPU::DEC<Address>(Address);

void CPU::
DEX()
{
	cout << hex << pc << " DEX " << endl;
	x--;

	Z = (x == 0);
	N = (x >> 7) & 0x1;
}

void CPU::
DEY()
{
	cout << hex << pc << " DEY " << endl;
	y--;

	Z = (y == 0);
	N = (y >> 7) & 0x1;
}

template <typename T> void CPU::
EOR(T addr)
{
	cout << hex << pc << " EOR " << addr << endl;
	unsigned char arg = addr.read(*this);

	acc ^= arg;
	N = (acc >> 7) & 0x1;
	Z = (acc == 0);

	/*
	  A = A ^ M
	  P.N = A.7
	  P.Z = (A==0) ? 1:0
	*/
}

template void CPU::EOR<Immediate>(Immediate);
template void CPU::EOR<Address>(Address);

template <typename T> void CPU::
INC(T addr)
{
	cout << hex << pc << " INC " << addr << endl;
	unsigned char arg = addr.read(*this);
	arg++;
	arg &= 0xFF;

	N = (arg >> 7) & 0x1;
	Z = (arg == 0);

	addr.write(*this, arg);
}

template void CPU::INC<Address>(Address);

void CPU::
INX()
{
	cout << hex << pc << " INX " << endl;
	x++;

	Z = (x == 0);
	N = (x >> 7) & 0x1;
}

void CPU::
INY()
{
	cout << hex << pc << " INY " << endl;
	y++;

	Z = (y == 0);
	N = (y >> 7) & 0x1;
}

template <typename T> void CPU::
JMP(T addr)
{
	cout << hex << pc << " JMP " << addr << endl;
	pc = addr.get_address();
}
template void CPU::JMP<Address>(Address);

template <typename T> void CPU::
JSR(T addr)
{
	cout << hex << pc << " JSR " << addr << endl;
	unsigned short a = addr.get_address();

	unsigned char pc_h = (pc - 1) >> 8 && 0xFF;
	unsigned char pc_l = (pc - 1) && 0xFF;

	push(pc_h);
	push(pc_l);

	pc = a;
}

template void CPU::JSR<Address>(Address);

template <typename T> void CPU::
LDA(T addr)
{
	acc = addr.read(*this);

	cout << hex << pc << " LDA " << addr << endl;

	N = acc >> 7;
	Z = (acc == 0);

	/*
	 A = M
	  P.N = A.7
	  P.Z = (A==0) ? 1:0
	*/
}

template void CPU::LDA<Immediate>(Immediate);
template void CPU::LDA<Address>(Address);

template <typename T> void CPU::
LDX(T addr)
{
	cout << hex << pc << " LDX " << addr << endl;
	x = addr.read(*this);

	N = x >> 7;
	Z = (x == 0);

	/*
	  X = M
	  P.N = X.7
	  P.Z = (X==0) ? 1:0
	*/

}

template void CPU::LDX<Immediate>(Immediate);
template void CPU::LDX<Address>(Address);

template <typename T> void CPU::
LDY(T addr)
{
	y = addr.read(*this);
	cout << hex << pc << " LDY " << addr << endl;

	N = y >> 7;
	Z = (y == 0);

	/*
 Y = M
  P.N = Y.7
  P.Z = (Y==0) ? 1:0
	*/
}

template void CPU::LDY<Immediate>(Immediate);
template void CPU::LDY<Address>(Address);

template <typename T> void CPU::
LSR(T addr)
{
	unsigned char val = addr.read(*this);
	cout << hex << pc << " LSR " << addr << endl;

	N = 0;
	C = val & 0x1;
	val = (val >> 1) & 0x7F;
	Z = (val == 0);

	addr.write(*this, val);

	/*
  P.N = 0
  P.C = B.0
  B = (B >> 1) & $7F
  P.Z = (B==0) ? 1:0
	*/
}

template void CPU::LSR<Address>(Address);
template void CPU::LSR<Accumulator>(Accumulator);

void CPU::
NOP()
{
	cout << hex << pc << " NOP" << endl;
	// do nothing
}

template <typename T> void CPU::
ORA(T addr)
{
	unsigned char value = addr.read(*this);
	cout << hex << pc << " ORA " << addr << endl;

	acc = acc | (value & 0xFF);
	N = acc >> 7;
	Z = acc == 0;
	/*
	A = A | M
	P.N = A.7
	P.Z = (A==0) ? 1:0
	 */
}

template void CPU::ORA<Immediate>(Immediate);
template void CPU::ORA<Address>(Address);

void CPU::
PHA()
{
	cout << hex << pc << " PHA " << endl;
	push(acc);
}
void CPU::
PHP()
{
	cout << hex << pc << " PHP " << endl;
	push(get_flags());
}
void CPU::
PLA()
{
	cout << hex << pc << " PLA " << endl;
	acc = pop();
	N = (acc >> 7) & 0x1;
	Z = (acc == 0);
}

void CPU::
PLP()
{
	cout << hex << pc << " PLP " << endl;
	unsigned char flags = pop();

	N = (flags >> 7) & 0x1;
	V = (flags >> 6) & 0x1;
	B = (flags >> 4) & 0x1;
	D = (flags >> 3) & 0x1;
	I = (flags >> 2) & 0x1;
	Z = (flags >> 1) & 0x1;
	C = (flags >> 0) & 0x1;
}

template <typename T> void CPU::
ROL(T addr)
{
	cout << hex << pc << " ROL " << addr << endl;
	unsigned char value = addr.read(*this);

	bool t = (value >> 7) & 0x1;
	value = (value << 1) & 0xFE;
	value = value | C;

	C = t;
	Z = (value == 0);
	N = (value >> 7) & 0x1;

	addr.write(*this, value);
}

template void CPU::ROL<Accumulator>(Accumulator);
template void CPU::ROL<Address>(Address);

template <typename T> void CPU::
ROR(T addr)
{
	cout << hex << pc << " ROR " << addr << endl;
	unsigned char value = addr.read(*this);

	bool t = value & 0x1;
	value = (value >> 1) & 0x7F;

	value = value | (C ? 0x80 : 0x00);
	C = t;
	Z = (value == 0);
	N = (value >> 7) & 0x1;

	addr.write(*this, value);
}

template void CPU::ROR<Accumulator>(Accumulator);
template void CPU::ROR<Address>(Address);

void CPU::
RTI()
{
	cout << hex << pc << " RTI " << endl;
	unsigned char flags = pop();
	N = (flags >> 7) & 0x1;
	V = (flags >> 6) & 0x1;
	B = (flags >> 4) & 0x1;
	D = (flags >> 3) & 0x1;
	I = (flags >> 2) & 0x1;
	Z = (flags >> 1) & 0x1;
	C = (flags >> 0) & 0x1;

	unsigned char l = pop();
	unsigned char h = pop();

	pc = h << 8;
	pc |= l;
}

void CPU::
RTS()
{

	cout << hex << pc << " RTS " << endl;
	unsigned char l = pop();
	unsigned char h = pop();

	pc = h << 8;
	pc |= l;
	++pc;
}

template <typename T> void CPU::
SBC(T addr)
{
	cout << hex << pc << " SBC " << addr << endl;
	unsigned char arg = addr.read(*this);

	short t;
	if (D) {
		t = BCD(acc) - BCD(arg) - (C ? 0 : 1);
		V = (t > 99 || t < 0) ? 1 : 0;
	} else {
		t = acc - arg - (C ? 0 : 1);
		V = (t > 127 || t < -128) ? 1 : 0;
	}

	C = (t >= 0);
	N = (t >> 7) & 0x1;
	Z = (t == 0);

	acc = t & 0xFF;
}

template void CPU::SBC<Immediate>(Immediate);
template void CPU::SBC<Address>(Address);

void CPU::
SEC()
{
	cout << hex << pc << " SEC " << endl;
	C = true;
}

void CPU::
SED()
{
	cout << hex << pc << " SED " << endl;
	D = true;
}

void CPU::
SEI()
{
	cout << hex << pc << " SEI " << endl;
	I = true;
}

template <typename T> void CPU::
STA(T addr)
{
	cout << hex << pc << " STA " << addr << endl;
	addr.write(*this, acc);
}

template void CPU::STA<Address>(Address);

template <typename T> void CPU::
STX(T addr)
{
	cout << hex << pc << " STX " << addr << endl;
	addr.write(*this, x);
}

template void CPU::STX<Address>(Address);

template <typename T> void CPU::
STY(T addr)
{
	cout << hex << pc << " STY " << addr << endl;
	addr.write(*this, y);
}

template void CPU::STY<Address>(Address);

void CPU::TAX()
{
	cout << hex << pc << " TAX " << endl;
	x = acc;
	N = (x >> 7) & 0x1;
	Z = (x == 0);
	/*
  X = A
  P.N = X.7
  P.Z = (X==0) ? 1:0
	 */
}

void CPU::TAY()
{
	cout << hex << pc << " TAY " << endl;
	y = acc;
	N = (y >> 7) & 0x1;
	Z = (y == 0);

}

void CPU::TSX()
{
	cout << hex << pc << " TSX " << endl;
	x = sp;
	N = (x >> 7) & 0x1;
	Z = (x == 0);

}

void CPU::TXA()
{
	cout << hex << pc << " TXA " << endl;
	acc = x;
	N = (acc >> 7) & 0x1;
	Z = (acc == 0);
}

void CPU::TXS()
{
	cout << hex << pc << " TXS " << endl;
	sp = x;
}

void CPU::TYA()
{
	cout << hex << pc << " TYA " << endl;
	acc = y;
	N = (acc >> 7) & 0x1;
	Z = (acc == 0);
}

std::ostream & operator<<(std::ostream& output, const Address& addr) {
		output << std::hex << addr.get_address() << std::dec;
		return output;
}

std::ostream & operator<<(std::ostream& output, const Immediate& addr) {
		output << std::hex << static_cast<int>(addr.read()) << std::dec;
		return output;
}

std::ostream & operator<<(std::ostream& output, const Accumulator& addr) {
		output << "ACC";
		return output;
}

std::ostream & operator<<(std::ostream& output, const Relative& addr) {
		output << std::hex << static_cast<int>(addr.read());
		return output;
}

} /* namespace emu */
} /* namespace domahony */

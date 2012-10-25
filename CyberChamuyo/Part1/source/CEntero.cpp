/*
 * CEntero.cpp
 *
 *  Created on: 06/05/2012
 *      Author: Shazgath
 */

#include "CEntero.h"
#include "common.h"
#include <cstring>

C_Entero::C_Entero() {
}

C_Entero::C_Entero(long i) {
	clave = i;
}

C_Entero C_Entero::operator+(const Clave& c) {
	C_Entero cAux;
	cAux = dynamic_cast<const C_Entero&>(c).clave + clave;
	return cAux;
}

C_Entero C_Entero::operator+(unsigned long i) {
	C_Entero cAux;
	cAux = i + clave;
	return cAux;
}

C_Entero& C_Entero::operator=(unsigned long i) {
	clave = i;
	return *this;
}

C_Entero::~C_Entero() {
}

long C_Entero::size() {
	return sizeof(long);
}

bool C_Entero::operator<(const Clave& c) const {
	return (clave < dynamic_cast<const C_Entero&>(c).clave);
}

bool C_Entero::operator<(const long& i) const {
	return clave < i;
}

bool C_Entero::operator>(const long& i) const {
	return clave > i;
}

bool C_Entero::operator!=(const C_Entero& c) const {
	return clave != c.clave;
}

bool C_Entero::operator==(const Clave& c) const {
	return (clave == dynamic_cast<const C_Entero&>(c).clave);
}

bool C_Entero::operator!=(const Clave& c) const {
	return !(clave == dynamic_cast<const C_Entero&>(c).clave);
}

bool C_Entero::operator>(const Clave& c) const {
	return (clave > dynamic_cast<const C_Entero&>(c).clave);
}

bool C_Entero::operator>=(const Clave& c) const {
	return (clave >= dynamic_cast<const C_Entero&>(c).clave);
}

std::ostream& operator<<(std::ostream& os, const C_Entero& c) {
	return(os << c.clave);
}

C_Entero& operator>>(std::istream& is, C_Entero& c) {
	is >> c.clave;
	return c;
}

void C_Entero::set(const long num) {
	clave = num;
}

long C_Entero::get() const {
	return clave;
}

void C_Entero::setSize(int size) {

}

std::string C_Entero::print() {
	std::string s(Auxiliar::int_to_dec(clave));
	return s;
}

char* int2bin(unsigned int a, char* buffer, int buf_size) {
	buffer += (buf_size - 1);
	for(int i = 31; i >= 0; i--) {
		*buffer-- = (a & 1) + '0';
		a >>= 1;
	}
	return buffer;
}
/*
std::string C_Entero::serializar() const {
	//char* buffer = new char[sizeof(int) + 1];
	char buffer[5];
	buffer[sizeof(int)] = 0;
	memcpy(buffer, reinterpret_cast<const char*>(&clave), sizeof(int));
	std::string ret(buffer);

	int a = 0;
	char buffer2[5];
	for(int i = 0; i < ret.size(); ++i) {
		buffer2[i] = ret[i];
	}
	memcpy(&a, buffer2, sizeof(int));

	return ret;
}
*/
std::vector<char>*& C_Entero::serializar(std::vector<char>*& ret) const{
	char buffer[5];
	buffer[sizeof(int)] = 0;
	memcpy(buffer, reinterpret_cast<const char*>(&clave), sizeof(int));
	for(int i = sizeof(int) - 1; i >= 0; --i) {
		ret->push_back(buffer[i]);
	}
	return ret;
/*
	unsigned int a = 0;
	unsigned char buffer2[5];
	buffer2[sizeof(int)] = 0;
	for(int i = sizeof(int) - 1; i >= 0; --i) {
		buffer2[i] = pData[3-i];
	}
	memcpy(&a, buffer2, sizeof(int));
*/

//	buffer2[sizeof(int)] = 0;
}

std::string C_Entero::serializarDecimal() const {
	std::string ret = Auxiliar::int_to_dec(clave);
	return ret;
}

Clave& C_Entero::operator=(const Clave& c) {
	clave = dynamic_cast<const C_Entero&>(c).clave;
	return *this;
}

int C_Entero::byte_size() {
	return this->size();
}

void C_Entero::hidratar(const std::vector<char>* s, int& pos) {
	clave = Auxiliar::leerEntero(s, pos);
}

int C_Entero::getTipo() const {
	return 0;
}

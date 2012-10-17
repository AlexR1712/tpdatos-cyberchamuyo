/*
 * Auxiliar.cpp
 *
 *  Created on: 04/05/2012
 *      Author: Shazgath
 */

#include "common.h"
#include <iomanip>

namespace Auxiliar {

int stoi(char* s) {
	std::stringstream ss(s);
	int res;
	ss >> res;
	return res;
}

int stoi(const std::string s) {
	std::stringstream ss(s.c_str());
	ss << std::hex;
	long res;
	ss >> res;
	return res;
}

std::string cambiarSeparadores(std::string& s, char sep1, char sep2) {
	std::string::iterator it;
	int size = s.size();
	for(int i = 0; i < size; ++i) {
		if(s[i] == sep1)
			s[i] = sep2;
	}
	return std::string(s);
}



std::string itos(int i) {
	std::string s;
	std::stringstream ss;
	ss << i;
	ss >> std::dec >> s;
	return s;
}


std::string int_to_hex( int i )
{
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(int))
         << std::hex << i;
  return stream.str();
}

std::string int_to_dec( int i )
{
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(int))
         << std::dec << i;
  return stream.str();
}


bool validarHecho(std::string s) {
	if(s.find('-') != std::string::npos)
		return false;						//  DESHARDCODEAR LUEGO
	std::stringstream ss(s);
	unsigned int i;
	ss >> i;
	if(ss.fail()) {
		return false;
	} else {
		return true;
	}
}

std::string float_to_dec(float f) {
	std::stringstream stream;
	stream << std::dec << f;
	return stream.str();
}

long leerEntero(long& p, const std::string dat) {
	std::string sn = dat.substr(p, sizeof(long));
	p += sizeof(long);
	return Auxiliar::stoi(sn);
}

}

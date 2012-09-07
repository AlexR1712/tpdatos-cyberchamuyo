/*
 * Auxiliar.h
 *
 *  Created on: 04/05/2012
 *      Author: Shazgath
 */

#ifndef AUXILIAR_H_
#define AUXILIAR_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

namespace Auxiliar {
int stoi(char* s);
int stoi(const std::string s);
std::string itos(int i);
std::string cambiarSeparadores(std::string& s, char sep1, char sep2);
std::string int_to_hex( int i );
std::string int_to_dec( int i );
std::string float_to_dec(float f);
long leerEntero(long& p, const std::string dat);
}

#endif /* AUXILIAR_H_ */

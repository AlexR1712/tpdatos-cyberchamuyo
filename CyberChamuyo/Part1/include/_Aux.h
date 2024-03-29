/*
 * Auxiliar.h
 *
 *  Created on: 04/05/2012
 *      Author: Shazgath
 */

#ifndef AUXILIAR_H_
#define AUXILIAR_H_

#include <string>
#include <sstream>

unsigned int stoi(std::string& s);
void obtenerSiguientePosicion(int &posAnterior, int &posActual, const std::string &linea);
unsigned long int generateHash(const char * string, size_t len);

#endif /* AUXILIAR_H_ */

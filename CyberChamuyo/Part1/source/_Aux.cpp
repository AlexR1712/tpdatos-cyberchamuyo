/*
 * Auxiliar.cpp
 *
 *  Created on: 04/05/2012
 *      Author: Shazgath
 */

#include "../include/_Aux.h"

unsigned int stoi(std::string& s) {
	std::stringstream ss(s.c_str());
	unsigned int res = 0;
	ss >> res;
	return res;
}

void obtenerSiguientePosicion(int
					    &posAnterior, int &posActual, const std::string &linea) {
  posAnterior = posActual;
  posActual = (linea.find("\t", posAnterior + 1));
}


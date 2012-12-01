/*
 * RegistroT.cpp
 *
 *  Created on: 27/11/2012
 *      Author: sebastian
 */

#include "../include/RegistroT.h"

RegistroT::RegistroT() {
	// TODO Auto-generated constructor stub

}

std::vector<char> RegistroT::seriallize() {
	std::vector<char> data;
	Auxiliar::insertarEntero(&data, termId);
	Auxiliar::insertarEntero(&data, term.size());
	Auxiliar::insertarString(&data, term);
	return data;
}

void RegistroT::deseriallize(std::vector<char>& data) {
	int pos = 0;
	termId = Auxiliar::leerEntero(&data, pos);
	int size = Auxiliar::leerEntero(&data, pos);
	for(int i = 0; i < size; ++i) {
		term.push_back(data[pos + i]);
	}
}

RegistroT::~RegistroT() {
	// TODO Auto-generated destructor stub
}

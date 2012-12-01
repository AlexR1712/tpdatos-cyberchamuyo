/*
 * RegistroTerminosEnDoc.cpp
 *
 *  Created on: 27/11/2012
 *      Author: sebastian
 */

#include "../include/RegistroTerminosEnDoc.h"
#include "../include/common.h"

RegistroTerminosEnDoc::RegistroTerminosEnDoc() {
	// TODO Auto-generated constructor stub

}

std::vector<char> RegistroTerminosEnDoc::seriallize() {
	std::vector<char> data;
	Auxiliar::insertarEntero(&data, this->termId);
	Auxiliar::insertarEntero(&data, this->docId);
	return data;
}

void RegistroTerminosEnDoc::deseriallize(std::vector<char>& data) {
	int pos = 0;
	this->termId = Auxiliar::leerEntero(&data, pos);
	this->docId = Auxiliar::leerEntero(&data, pos);
}

RegistroTerminosEnDoc::~RegistroTerminosEnDoc() {
	// TODO Auto-generated destructor stub
}

/*
 * IndiceArbol.cpp
 *
 *  Created on: 11/10/2012
 *      Author: sebastian
 */

#include "IndiceArbol.h"
#include <fstream>
#include "CAlfa.h"
#include <cstring>

IndiceArbol::IndiceArbol(TextInputSequentialFile<TextDictionaryRecord<false> >& arch_sec, const char* n_arch_arbol, int b_size) : arbol(n_arch_arbol, b_size) {
	TextDictionaryRecord<false> record;
	char buffer[255];
	record = arch_sec.getRecord();
	record = arch_sec.getRecord();
	unsigned int n = 0;
	while(!arch_sec.endOfFile()) {
		std::string s = record.getWord();
		s.erase(s.size() - 1);
		CAlfa* c = new CAlfa(s);
		Registro* reg = new Registro(c);
		arbol.insertarRegistro(reg);
		record = arch_sec.getRecord();
	}
	arbol.imprimirNodos();
}

IndiceArbol::~IndiceArbol() {
	// TODO Auto-generated destructor stub
}



/*
 * IndiceArbol.cpp
 *
 *  Created on: 11/10/2012
 *      Author: sebastian
 */

#include "../include/IndiceArbol.h"
#include <fstream>
#include "../include/CAlfa.h"
#include <cstring>
#include "../include/RegistroArbol.h"

IndiceArbol::IndiceArbol() : arbol("arch_arbol.bin", 512) {

}
/*
IndiceArbol::IndiceArbol(TextInputSequentialFile<TextDictionaryRecord<false> >& arch_sec, const char* n_arch_arbol, int b_size) : arbol(n_arch_arbol, b_size) {
	TextDictionaryRecord<false> record;
	record = arch_sec.getRecord();
	record = arch_sec.getRecord();
	while(!arch_sec.endOfFile()) {
		std::string s = record.getWord();
		s.erase(s.size() - 1);
		CAlfa* c = new CAlfa(s);
		Registro* reg = new Registro(c);
		arbol.insertarRegistro(reg);
		record = arch_sec.getRecord();
		delete reg;
	}
	arbol.imprimirNodos();
}
*/
bool IndiceArbol::find(const std::string& word) {
	CAlfa* clave = new CAlfa(word);
	Registro* ret_reg = new RegistroArbol();
	bool resultado = arbol.buscar(clave, ret_reg);
	//delete ret_reg;
	return resultado;
}

void IndiceArbol::clear() {
	arbol.clear();
}

BinaryDictionaryRecord<true> IndiceArbol::next() {
	BinaryDictionaryRecord<true> record;
	Registro* reg = arbol.siguiente();
	Clave* clave = reg->getClave();
	record.setWord(clave->serializarDecimal());	//  cambiar por un getter de string polimorfico
	return record;
}

bool IndiceArbol::hasNext() {
	return arbol.hasNext();
}

void IndiceArbol::insert(std::string& word) {
	CAlfa* clave = new CAlfa(word);
	Registro* reg = new Registro(clave);
	arbol.insertarRegistro(reg);
	delete reg;
}

void IndiceArbol::exportar(const char* path) {
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > file(path);
	arbol.exportar(file);
}

void IndiceArbol::createIndex(std::string in_path) {
	BinaryDictionaryRecord<true> record;
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > arch_sec(in_path);
	record = arch_sec.getRecord();
	record = arch_sec.getRecord();
	while(!arch_sec.endOfFile()) {
		std::string s = record.getWord();
		CAlfa* c = new CAlfa(s);
		Registro* reg = new Registro(c);
		arbol.insertarRegistro(reg);
		record = arch_sec.getRecord();
		delete reg;
	}
}

IndiceArbol::~IndiceArbol() {
}



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
#include "../include/stringUtilities.h"
#include "../include/wordNormalizer.h"

IndiceArbol::IndiceArbol(std::string file_name) : arbol(file_name.c_str(), N_SIZE) {
}

bool IndiceArbol::find(std::string word) {
	if(isEmpty())
		return false;
	WordNormalizer normalizer;
	normalizer.normalizeWord(word);
	CAlfa* clave = new CAlfa(word);
	Registro* ret_reg = new RegistroArbol();
	bool resultado = arbol.buscar(clave, ret_reg);
	return resultado;
}

void IndiceArbol::clear() {
	arbol.clear();
}

RegistroArbol& IndiceArbol::textSearch(std::string term) {
	//	TODO
}

BinaryDictionaryRecord<true> IndiceArbol::next() {
	BinaryDictionaryRecord<true> record;
	Registro* reg = arbol.siguiente();
	Clave* clave = reg->getClave();
	record.setWord(clave->serializarDecimal());	//  cambiar por un getter de string polimorfico
	delete reg;
	return record;
}

bool IndiceArbol::hasNext() {
	return arbol.hasNext();
}

void IndiceArbol::insert(std::string& word) {
	CAlfa* clave = new CAlfa(word);
	Registro* reg = new RegistroArbol(clave);
	arbol.insertarRegistro(reg);
	//delete reg;
}

void IndiceArbol::exportar(const char* path) {
	BinaryOutputSequentialFile<BinaryDictionaryRecord<true> > file(path);
	arbol.exportar(file);
}

void IndiceArbol::createIndex(std::string in_path) {
	BinaryDictionaryRecord<true> record;
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > arch_sec(in_path);
	record = arch_sec.getRecord();
	while(!arch_sec.endOfFile()) {
		std::string s = record.getWord();
		if(s.size() > 1 && s != "\n") {
		StringUtilities::sacarR(s);
		StringUtilities::sacarN(s);
		CAlfa* c = new CAlfa(s);
		Registro* reg = new RegistroArbol(c);
		arbol.insertarRegistro(reg);
		delete reg;
		record = arch_sec.getRecord();
		} else {
			record = arch_sec.getRecord();
		}
	}
}

void IndiceArbol::rewind() {
	arbol.rewind();
}

bool IndiceArbol::isEmpty() {
	return arbol.isEmpty();
}

void IndiceArbol::insert(unsigned int termId, std::string term, unsigned int invListId) {
	//	TODO
}

void IndiceArbol::modify(unsigned int termId, std::string term, unsigned int invListId) {
	//	TODO
}

void IndiceArbol::mostrar() {
	arbol.imprimirNodos();
}

IndiceArbol::~IndiceArbol() {
}



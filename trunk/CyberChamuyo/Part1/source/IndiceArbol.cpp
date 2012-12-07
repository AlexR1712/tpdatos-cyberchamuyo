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
#include "../include/wordRankingRecord.h"

#ifndef T_RECORD_SIZE
#define T_RECORD_SIZE 50
#endif

IndiceArbol::IndiceArbol(std::string file_name) : arbol(file_name.c_str(), N_SIZE) {
	totalTerms = 1;
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
	if(isEmpty())
		throw(1);
	CAlfa* clave = new CAlfa(term);
	RegistroArbol* ret_reg = new RegistroArbol();
	bool resultado = arbol.buscar(clave, ret_reg);
	if(!resultado) {
		ret_reg->setListId(0);
		ret_reg->setTermId(1000000);
	}
	return *ret_reg;
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
	if(arbol.insertarRegistro(reg) == OK)
		totalTerms++;
	//delete reg;
}

void IndiceArbol::exportar(const char* path) {
	VariableLengthRecordSequentialFile<WordRankingRecord> file;
	file.open(path,true);
	arbol.exportar(file);
}

void IndiceArbol::createIndex(std::string in_path, FixedLengthRecordSequentialFile<FixedLengthTRecord>* T) {
	VariableLengthRecordSequentialFile<BinaryDictionaryRecord<true> > arch_sec;
	BinaryDictionaryRecord<true> record;
	arch_sec.open(in_path);
	//record = arch_sec.getNextRecord();
	if(arch_sec.endOfFile()) {
		std::cout << "Archivo inexistente" << std::endl;
		return;
	}
	do {
		record = arch_sec.getNextRecord();
		std::string s = record.getWord();
		if(s.size() > 1 && s != "\n") {
			StringUtilities::sacarR(s);
			StringUtilities::sacarN(s);
			CAlfa* c = new CAlfa(s);
			RegistroArbol* reg = new RegistroArbol(c, 0, 0);
			reg->setTermId(T->getLastRecordPosition() + 1);
			if(arbol.insertarRegistro(reg) == OK)
				totalTerms++;
			delete reg;
			FixedLengthTRecord tRecord(T_RECORD_SIZE);
			tRecord.setTerm(s);
			tRecord.setId(T->getLastRecordPosition() + 1);
			T->putRecord(tRecord);
		}
	else {
			record = arch_sec.getNextRecord();
		}
	} while(!arch_sec.endOfFile());
}

void IndiceArbol::rewind() {
	arbol.rewind();
}

bool IndiceArbol::isEmpty() {
	return arbol.isEmpty();
}

void IndiceArbol::insert(unsigned int termId, std::string term, unsigned int invListId) {
	CAlfa* clave = new CAlfa(term);
	RegistroArbol* reg = new RegistroArbol(clave, termId, invListId);
	if(arbol.insertarRegistro(reg) == OK)
		totalTerms++;
}

unsigned int IndiceArbol::getTotalTerms() {
	return totalTerms;
}

void IndiceArbol::modify(unsigned int termId, std::string word, unsigned int invListId) {
	if(isEmpty())
		return;	//  CAMBIAR POR EXCEPCION DESPUES
	WordNormalizer normalizer;
	normalizer.normalizeWord(word);
	CAlfa* clave = new CAlfa(word);
	RegistroArbol* ret_reg = new RegistroArbol(clave, termId, invListId);
	arbol.modify(ret_reg);
}

void IndiceArbol::clearLists() {
	(this->arbol).clearListReferences();
}

void IndiceArbol::mostrar() {
	arbol.imprimirNodos();
}

IndiceArbol::~IndiceArbol() {
}



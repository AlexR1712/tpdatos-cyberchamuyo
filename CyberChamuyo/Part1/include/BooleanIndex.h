/*
 * BooleanIndex.h
 *
 *  Created on: 01/12/2012
 *      Author: sebastian
 */

#ifndef BOOLEANINDEX_H_
#define BOOLEANINDEX_H_

#include <list>
#include <string>
#include "Frase.h"
#include "IndiceArbol.h"
#include "fixedLengthRecordSequentialFile.h"
#include "binaryInputSequentialFile.h"
#include "OcurrenceFileRecord.h"
#include "FixedLengthTRecord.h"
#include "RegistroArbol.h"
#include "Phrase.h"
#include "externalSorter.h"
#include "InvertedListFile.h"
#include "ListaInvertida.h"

class BooleanIndex {
private:
	invertedList::InvertedListFile invertedListsFile;
	IndiceArbol* vocabulary;
public:
	BooleanIndex();
	void insertPhrase(Phrase frase, IndiceArbol* vocabulary, FixedLengthRecordSequentialFile<FixedLengthTRecord>* T);
	void load(FixedLengthRecordSequentialFile<FixedLengthTRecord>& T, std::string ocurrenceFilePath, IndiceArbol* vocabulary);
	std::list<unsigned int> search(std::string term, IndiceArbol* vocabulary);
	void erasePhrase(unsigned int phraseId);
	void insertTerm(std::string term);
	virtual ~BooleanIndex();
};

#endif /* BOOLEANINDEX_H_ */

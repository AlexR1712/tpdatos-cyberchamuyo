/*
 * BooleanIndex.h
 *
 *  Created on: 01/12/2012
 *      Author: sebastian
 */

#ifndef BOOLEANINDEX_H_
#define BOOLEANINDEX_H_

#include "ArchivoBloquesFijos.h"
#include <list>
#include <string>
#include "Frase.h"
#include "IndiceArbol.h"
#include "fixedLengthRecordSequentialFile.h"
#include "variableLengthRecordSequentialFile.h"
#include "OcurrenceFileRecord.h"
#include "FixedLengthTRecord.h"
#include "InvertedList.h"
#include "RegistroArbol.h"
#include "Phrase.h"
#include "externalSorter.h"
#include "InvertedListFile.h"
#include "ListaInvertida.h"

#ifndef	INVERTED_LISTS_FILE_NAME
#define INVERTED_LISTS_FILE_NAME "bin/invertedLists.bin"
#endif

#ifndef MSG_FILE_SIZE_INFO
#define MSG_FILE_SIZE_INFO "size : "
#endif

#ifndef MSG_FILE_NAME_INFO
#define MSG_FILE_NAME_INFO "Inverted Lists File name: "
#endif

class BooleanIndex {
private:
	invertedList::InvertedListFile invertedListsFile;
	bool valid;
public:
	BooleanIndex();
	void eraseTermInDoc(std::string term, unsigned int docId, IndiceArbol* vocabulary);
	void addDocToTerm(std::string term, unsigned int docIds, IndiceArbol* vocabulary);
	void insertPhrase(Phrase frase, IndiceArbol* vocabulary, FixedLengthRecordSequentialFile<FixedLengthTRecord>* T, unsigned int totalTerms );
	void load(FixedLengthRecordSequentialFile<FixedLengthTRecord>* T, std::string ocurrenceFilePath, IndiceArbol* vocabulary);
	std::list<unsigned int> search(std::string term, IndiceArbol* vocabulary);
	unsigned int addTerm(std::string term, unsigned int docId);
	void erasePhrase(unsigned int phraseId);
	bool isLoaded();
	void printFileInfo(std::ostream& os);
	virtual ~BooleanIndex();
	friend std::ostream& operator<<(std::ostream& oss, BooleanIndex &boooleanIndex);
};

std::ostream& operator<<(std::ostream& oss, BooleanIndex &booleanIndex);

#endif /* BOOLEANINDEX_H_ */

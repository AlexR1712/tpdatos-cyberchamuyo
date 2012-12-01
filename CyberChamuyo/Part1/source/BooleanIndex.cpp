/*
 * BooleanIndex.cpp
 *
 *  Created on: 01/12/2012
 *      Author: sebastian
 */

#include "../include/BooleanIndex.h"

BooleanIndex::BooleanIndex() : invertedListsFile("invertedLists.bin") {
}

void BooleanIndex::load(FixedLengthRecordSequentialFile<FixedLengthTRecord>& T, std::string ocurrenceFilePath, IndiceArbol* vocabulary) {
	ExternalSorter sorter(100, false);	//	NI IDEA
	std::string orderedOcurrenceFilePath = "orderedOcurrenceFile.bin";
	sorter.sort(ocurrenceFilePath, orderedOcurrenceFilePath, false);
	BinaryInputSequentialFile<OcurrenceFileRecord> ocurrenceFile;
	ocurrenceFile.open(orderedOcurrenceFilePath);
	unsigned int inv_list_cont = 0;
	while(!ocurrenceFile.endOfFile()) {
		OcurrenceFileRecord ocurrenceRecord = ocurrenceFile.getRecord();
		FixedLengthTRecord termRecord = T.getRecord(ocurrenceRecord.getTermId());
		std::string term = termRecord.getTerm();
		unsigned int previousTerm = ocurrenceRecord.getTermId();
		invertedList::ListaInvertida* inv_list = new invertedList::ListaInvertida;
		inv_list->setId(inv_list_cont++);
		if(!vocabulary->find(term))
			vocabulary->insert(ocurrenceRecord.getTermId(), term, inv_list_cont);
		else
			vocabulary->modify(ocurrenceRecord.getTermId(), term, inv_list_cont);
		while(ocurrenceRecord.getTermId() == previousTerm) {
			unsigned int docId = ocurrenceRecord.getDocId();
			inv_list->insertar(docId);
			ocurrenceRecord = ocurrenceFile.getRecord();
		}
		this->invertedListsFile.insertarLista(inv_list);
	}
}

std::list<unsigned int> BooleanIndex::search(std::string term, IndiceArbol* vocabulary) {
	RegistroArbol* reg(vocabulary->textSearch(term));
	unsigned int listId = reg->getListId();
	invertedList::ListaInvertida* inv_list = new invertedList::ListaInvertida;
	inv_list = this->invertedListsFile.getLista(listId);
	std::list<unsigned int> res = inv_list->getParticion();
	return res;
}

void erasePhrase(Phrase frase) {
	//	TODO
}

void BooleanIndex::insertPhrase(Phrase frase, IndiceArbol* vocabulary, FixedLengthRecordSequentialFile<FixedLengthTRecord>* T) {
	std::vector<std::string> phraseTerms = frase.getTerms();
	for(unsigned int i = 0; i < phraseTerms.size(); ++i) {
		if(!vocabulary->find(phraseTerms[i])) {
			invertedList::ListaInvertida* inv_list = new invertedList::ListaInvertida;
			//unsigned int newTermId = T->putRecord(phraseTerms[i]);
			inv_list->insertar(frase.getId());
			//unsigned int newListId = invertedListsFile.getNewId();
			//inv_list.setId(newListId);
			//vocabulary.insert(newTermId, phraseTerms[i], newListId);
		} else {
			invertedList::ListaInvertida* inv_list = new invertedList::ListaInvertida;
			inv_list = this->invertedListsFile.getLista(frase.getId());
			//inv_list->insertar(T.insert(phraseTerms[i]));
			this->invertedListsFile.actualizarLista(inv_list, frase.getId());
		}
	}
}

void insertTerm(std::string term) {
	//  Hace falta esto realmente??
}

BooleanIndex::~BooleanIndex() {
	// TODO Auto-generated destructor stub
}

/*
 * FixedLengthTRecord.cpp
 *
 *  Created on: 30/11/2012
 *      Author: sebastian
 */

#include "../include/FixedLengthTRecord.h"

FixedLengthTRecord::FixedLengthTRecord(unsigned int size) {
	this->setRecordSize(size);
	termId = 0;
}

void FixedLengthTRecord::setId(unsigned int id) {
	termId = id;
}

void FixedLengthTRecord::setTerm(std::string t) {
	term = t;
}

unsigned int FixedLengthTRecord::getId() {
	return this->termId;
}

std::string FixedLengthTRecord::getTerm() {
	return term;
}

void FixedLengthTRecord::deserialize(std::vector<unsigned char>& data) {
	int pos = 0;
	unsigned int termSize = 0;
	termId = Auxiliar::leerEnteroU(data, pos);
	termSize = Auxiliar::leerEnteroU(data, pos);
	term = Auxiliar::leerStringU(data, term, pos, termSize);
}

void FixedLengthTRecord::serialize(std::vector<unsigned char>& data) {
	Auxiliar::insertarEnteroU(data, this->termId);
	Auxiliar::insertarEnteroU(data, term.size());
	Auxiliar::insertarStringU(data, this->term);
}

FixedLengthTRecord::~FixedLengthTRecord() {
	// TODO Auto-generated destructor stub
}

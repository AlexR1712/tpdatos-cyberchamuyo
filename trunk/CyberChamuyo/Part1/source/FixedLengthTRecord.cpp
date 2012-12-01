/*
 * FixedLengthTRecord.cpp
 *
 *  Created on: 30/11/2012
 *      Author: sebastian
 */

#include "../include/FixedLengthTRecord.h"

FixedLengthTRecord::FixedLengthTRecord(unsigned int size) : FixedLengthRecord(size) {
	// TODO Auto-generated constructor stub

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

}

void FixedLengthTRecord::serialize(std::vector<unsigned char>& data) {

}

FixedLengthTRecord::~FixedLengthTRecord() {
	// TODO Auto-generated destructor stub
}

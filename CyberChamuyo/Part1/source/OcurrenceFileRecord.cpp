/*
 * OcurrenceFileRecord.cpp
 *
 *  Created on: 22/11/2012
 *      Author: sebastian
 */

#include "../include/OcurrenceFileRecord.h"
#include "../include/common.h"

OcurrenceFileRecord::OcurrenceFileRecord() {
	// TODO Auto-generated constructor stub

}

std::string OcurrenceFileRecord::serialize() {
	std::vector<unsigned char> data;
	Auxiliar::insertarEnteroU(data, this->docId);
	Auxiliar::insertarEnteroU(data, this->termId);
	std::string ret;
	std::vector<unsigned char>::iterator it;
	for(it = data.begin(); it != data.end(); ++it) {
		ret.push_back(*it);
	}
	return ret;
}

void OcurrenceFileRecord::deserialize(std::string data) {
	int pos = 0;
	std::vector<unsigned char> dataVector;
	for(unsigned int i = 0; i < data.size(); ++i) {
		dataVector.push_back(data[i]);
	}
	this->docId = Auxiliar::leerEnteroU(dataVector, pos);
	this->termId = Auxiliar::leerEnteroU(dataVector, pos);
}

int OcurrenceFileRecord::getDocId() {
	return docId;
}

int OcurrenceFileRecord::getTermId() {
	return termId;
}

void OcurrenceFileRecord::setDocId(int id) {
	this->docId = id;
}

void OcurrenceFileRecord::setTermId(int id) {
	this->termId = id;
}

OcurrenceFileRecord::~OcurrenceFileRecord() {
	// TODO Auto-generated destructor stub
}

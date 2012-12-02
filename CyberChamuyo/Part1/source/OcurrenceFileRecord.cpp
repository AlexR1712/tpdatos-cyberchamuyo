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

void OcurrenceFileRecord::serialize(std::vector<unsigned char>& recordAsCharVector) {
	recordAsCharVector.clear();
//	std::vector<unsigned char> data;
//	Auxiliar::insertarEnteroU(data, this->docId);
//	Auxiliar::insertarEnteroU(data, this->termId);
	Auxiliar::insertarEnteroU(recordAsCharVector, this->docId);
	Auxiliar::insertarEnteroU(recordAsCharVector, this->termId);
//	std::string ret;

//	std::vector<unsigned char>::iterator it;
//	for(it = data.begin(); it != data.end(); ++it) {
//		ret.push_back(*it);
//	}
//	return ret;
}

void OcurrenceFileRecord::deserialize(std::vector<unsigned char>& recordAsCharVector) {
	int pos = 0;
//	std::vector<unsigned char> dataVector;
//	for(unsigned int i = 0; i < data.size(); ++i) {
//		dataVector.push_back(data[i]);
//	}
//	this->docId = Auxiliar::leerEnteroU(dataVector, pos);
//	this->termId = Auxiliar::leerEnteroU(dataVector, pos);
	this->docId = Auxiliar::leerEnteroU(recordAsCharVector, pos);
	this->termId = Auxiliar::leerEnteroU(recordAsCharVector, pos);
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

/*
 * InvertedList.cpp
 *
 *  Created on: 24/11/2012
 *      Author: sebastian
 */

#include "../include/InvertedList.h"

InvertedList::InvertedList() {
	// TODO Auto-generated constructor stub
}

unsigned int InvertedList::size() {
	return this->vec.size();
}

unsigned int& InvertedList::operator [](unsigned int pos) {
	return this->vec[pos];
}

void InvertedList::setId(unsigned int docId) {
	id = docId;
}

std::vector<unsigned char> InvertedList::serialize() {
	int last_pos = 0;
	std::vector<unsigned char> vec_aux;
	Auxiliar::insertarEnteroU(vec_aux, vec.size());
	BinaryArray2 res(0);
	for(int i = 0; i < vec.size(); ++i) {
		BinaryArray2 ba = TextRecoveryUtilities::gammaEncode(vec[i]);
		int gammaSize = TextRecoveryUtilities::gammaSize(vec[i]);
		res.append(ba, last_pos, gammaSize);
		last_pos += gammaSize;
	}
	res.push_array_front(vec_aux);
	std::vector<unsigned char> ret;
	for(int i = 0; i < res.size(); ++i)
		ret.push_back(res[i]);
	return ret;
}

void InvertedList::deserialize(std::vector<unsigned char> data) {
	int pos = 0;
	unsigned int cant = Auxiliar::leerEnteroU(data, pos);
	std::vector<unsigned char> vec_aux;
	for(int i = 4; i < data.size(); ++i)
		vec_aux.push_back(data[i]);
	BinaryArray2 ba(vec_aux);
	unsigned int offset = 0;
	for(int i = 0; i < cant; ++i) {
		unsigned int n = TextRecoveryUtilities::gammaDecode(ba, offset);
		offset += TextRecoveryUtilities::gammaSize(n);
		vec.push_back(n);
	}
}

void InvertedList::push_back(unsigned int n) {
	vec.push_back(n);
}

InvertedList::~InvertedList() {
	// TODO Auto-generated destructor stub
}

/*
 * Phrase.cpp
 *
 *  Created on: 02/12/2012
 *      Author: sebastian
 */

#include "../include/Phrase.h"

Phrase::Phrase() {
	// TODO Auto-generated constructor stub

}

std::vector<std::string> Phrase::getTerms() {
	return terms;
}

unsigned int Phrase::getId() {
	return this->phraseId;
}

Phrase::~Phrase() {
	// TODO Auto-generated destructor stub
}

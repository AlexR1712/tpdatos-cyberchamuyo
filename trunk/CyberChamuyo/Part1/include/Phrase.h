/*
 * Phrase.h
 *
 *  Created on: 02/12/2012
 *      Author: sebastian
 */

#ifndef PHRASE_H_
#define PHRASE_H_

#include <vector>
#include <string>

class Phrase {
private:
	std::vector<std::string> terms;
	unsigned int phraseId;
public:
	unsigned int getId();
	std::vector<std::string> getTerms();
	Phrase();
	Phrase(std::vector<std::string> frases, unsigned int phraseId);
	virtual ~Phrase();
};

#endif /* PHRASE_H_ */

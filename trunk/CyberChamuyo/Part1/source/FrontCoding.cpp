/*
 * FrontCoding.cpp
 *
 *  Created on: 06/10/2012
 *      Author: sebastian
 */

#include "FrontCoding.h"
#include <sstream>

FrontCoding::FrontCoding() {
}

FrontCoding::~FrontCoding() {
}

int FrontCoding::encode(const std::vector<char>* word, std::vector<char>* res) {
	if(previous.size() == 0) {
		res->push_back(0);
		for(int i = 0; i < word->size(); ++i) {
			previous.push_back((*word)[i]);
			res->push_back((*word)[i]);
		}
	} else {
		unsigned char i = 0;
		while((*word)[i] == previous[i])
			++i;
		res->push_back(i);
		previous.erase(previous.begin(), previous.end());
		for(int j = 0; j < word->size(); ++j) {
			previous.push_back((*word)[j]);
		}
		for(;i < word->size(); ++i)
			res->push_back((*word)[i]);
	}
	return 0;
}

int FrontCoding::encode(const std::string& word, std::string& res) {
	if(previous.size() == 0) {
		previous = word;
		res.append(word, 0, word.size());
	}
	else {
		unsigned char i = 0;
		while(word[i] == previous[i])
			++i;
		previous = word;
		res.push_back(i);
		for(;i < word.size(); ++i)
			res.push_back(word[i]);
	}
	return 0;
}


//  los -1 son por el tamaño de los string hasta 9, hay que cambiarlo por
//  unsigned char para q sea hasta 255
int FrontCoding::decode(const std::string& word, std::string& deco) {
	if(previous.size() == 0) {
		for(int i = 1; i < word.size(); ++i) {
			deco.push_back(word[i]);
			previous.push_back(word[i]);
		}
	} else {
		std::stringstream ss;
		char cant = word[0];	//  por conversion ascii
		for(int i = 0; i < cant; ++i) {
			deco.push_back(previous[i]);
		}
		previous.erase(cant, previous.size() - cant);
		for(int i = 1; i < word.size(); ++i) {
			deco.push_back(word[i]);
			previous.push_back(word[i]);
		}
	}
	return 0;
}



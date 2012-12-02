/*
 * InvertedList.h
 *
 *  Created on: 24/11/2012
 *      Author: sebastian
 */

#ifndef INVERTEDLIST_H_
#define INVERTEDLIST_H_

#include <vector>
#include "../include/BinaryArray2.h"
#include <string>
#include "../include/TextRecoveryUtilities.h"

class InvertedList {
private:
	unsigned int id;
	std::vector<unsigned int> vec;
public:
	InvertedList();
	unsigned int size();
	void setId(unsigned int docId);
	unsigned int getId();
	void push_back(unsigned int n);
	std::vector<unsigned char> serialize();
	unsigned int& operator[](unsigned int pos);
	void deserialize(std::vector<unsigned char> data);
	virtual ~InvertedList();
};

#endif /* INVERTEDLIST_H_ */

/*
 * BinaryArray.cpp
 *
 *  Created on: 17/11/2012
 *      Author: sebastian
 */

#include "../include/BinaryArray.h"
#include <cstring>
#include <vector>
#include <list>

BinaryArray::BinaryArray(unsigned int size) {
	for(unsigned int i = 0; i < size; ++i)
		array.push_back(0);
}

BinaryArray::BinaryArray(std::vector<unsigned char> vec) {
	array = vec;
}

BinaryArray::BinaryArray(const char* vec) {
	int size = strlen(vec);
	for(int i = 0; i < size; ++i)
		array.push_back(vec[i]);
}

BinaryArray::~BinaryArray() {
	// TODO Auto-generated destructor stub
}

void BinaryArray::setBit(unsigned int pos, unsigned char bit) {
	unsigned int bytePos = pos / 8;
	char bitOffset = pos % 8;
	if(!bit) {
		char left_bit = 0x7f;
		left_bit = (0xff << (8 - bitOffset)) | (left_bit >> bitOffset);
		array[bytePos] = array[bytePos] & left_bit;
	} else {
	unsigned left_bit = 0x80;
	left_bit = left_bit >> bitOffset;
	array[bytePos] = array[bytePos] | left_bit;
	}
}

void BinaryArray::set(unsigned int posi, unsigned int posf, unsigned char bit) {
	for(unsigned int i = posi; i < posf; ++i) {
		setBit(i, bit);
	}
}

bool BinaryArray::getBitAsBool(unsigned int pos) {
	unsigned int bytePos = pos / 8;
	unsigned int bitOffset = pos % 8;
	char left_bit = 0x80;
	left_bit = left_bit >> bitOffset;
	if(left_bit & array[bytePos])
		return 1;
	return 0;
}

char BinaryArray::getBit(unsigned int pos) {
	unsigned int bytePos = pos / 8;
	unsigned int bitOffset = pos % 8;
	char left_bit = 0x80;
	left_bit = left_bit >> bitOffset;
	return (left_bit & array[bytePos]);
}

std::vector<unsigned char> BinaryArray::Binary() {
	return array;
}

unsigned char& BinaryArray::operator[](unsigned int pos) {
	return array[pos];
}

std::vector<unsigned char> BinaryArray::Ascii8() {
	std::vector<unsigned char> ret;
	for(unsigned int i = 0; i < array.size(); ++i) {
		for(int j = 0; j < 8; ++j) {
			unsigned char left_bit = 0x80;
			left_bit = (left_bit >> j);
			char c = (array[i] & left_bit);
			if(c)
				ret.push_back(49);
			else
				ret.push_back(48);
		}
	}
	return ret;
}

std::vector<unsigned char> BinaryArray::Ascii() {
	std::vector<unsigned char> ret;
	for(unsigned int i = 0; i < array.size(); ++i) {
		for(int j = 0; j < 8; ++j) {
			unsigned char left_bit = 0x80;
			left_bit = (left_bit >> j);
			char c = (array[i] & left_bit);
			if(c)
				ret.push_back(49);
			else
				ret.push_back(48);
		}
	}
	return ret;
}

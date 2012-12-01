/*
 * BinaryArray2.cpp
 *
 *  Created on: 17/11/2012
 *      Author: sebastian
 */

#include "../include/BinaryArray2.h"
#include <cstring>
#include <vector>
#include <list>

#define F 0x80


void BinaryArray2::pop_front() {
	for(unsigned int i = 0; i < array.size() - 1; ++i) {
		array[i] = array[i + 1];
	}
	array.pop_back();
}

void BinaryArray2::addInt(unsigned int n) {
	char buffer[4];
	buffer[0] = n;
	buffer[1] = n >> 8;
	buffer[2] = n >> 16;
	buffer[3] = n >> 24;
	char byte = buffer[3];
	int pos = 3;
	while(!byte) {
		--pos;
		byte = buffer[pos];
	}
	char aux = buffer[0];
	buffer[0] = (buffer[pos]);
	buffer[pos] = aux;
	if(pos == 3) {
		aux = buffer[2];
		buffer[2] = buffer[3];
		buffer[3] = aux;
	}
	for(int i = 0; i <= pos; ++i) {
		array.push_back(buffer[i]);
	}
}

BinaryArray2::BinaryArray2(unsigned int size) {
	for(unsigned int i = 0; i < size; ++i)
		array.push_back(0);
}

BinaryArray2::BinaryArray2(std::vector<unsigned char> vec) {
	array = vec;
}

BinaryArray2::~BinaryArray2() {
	// TODO Auto-generated destructor stub
}

void BinaryArray2::setBit(unsigned int pos, unsigned char bit) {
	unsigned int bytePos = pos / 8;
	char bitOffset = pos % 8;
	if((pos / 8 + 1) > array.size())
		array.push_back(0);
	if(!bit) {
		char left_bit = 0xfe;
		left_bit = (left_bit << bitOffset) | (0x7f >> 7 - bitOffset);
		array[bytePos] = array[bytePos] & left_bit;
	} else {
		unsigned left_bit = 0x01;
		left_bit = left_bit << bitOffset;
		array[bytePos] = array[bytePos] | left_bit;
	}
}

void BinaryArray2::set(unsigned int posi, unsigned int posf, unsigned char bit) {
	for(unsigned int i = posi; i <= posf; ++i) {
		setBit(i, bit);
	}
}

void BinaryArray2::setByte(unsigned int pos, unsigned char byte) {
	unsigned char leftmost_bit = F;
	unsigned char and_res;
	if(((pos + 9) / 8) > array.size())
		array.push_back(0);
	for(int i = 0; i < 8; ++i) {
		and_res = leftmost_bit & byte;
		if(and_res)
			setBit(pos + i, 1);
		else
			setBit(pos + i, 0);
		leftmost_bit = leftmost_bit >> 1;
	}
}

void BinaryArray2::setByteInNBits(unsigned int pos, unsigned int n, unsigned char byte) {
	char leftmost_bit = 0x01;
	char and_res = 0;
	unsigned char byte_aux = byte;
	int cont = 0;
	int arraySize = array.size();
	unsigned int cantBytes = (pos + n) / 8;
	if((pos + n) % 8)
		cantBytes++;
	if(cantBytes > array.size()) {
		for(int i = 0; i < (cantBytes - arraySize); ++i) {
			array.push_back(0);
		}
	}
	while(!and_res && cont < 9) {
		and_res = leftmost_bit & byte_aux;
		if(!and_res) {
			byte_aux = byte_aux << 1;
			cont++;
		}
	}
	if(cont < 9) {
		int size = 8 - cont;
		for(unsigned int i = 0; i < n - size; ++i) {
			setBit(pos + 1, 0);
		}
		for(unsigned int i = n - size; i < n; ++i) {
			and_res = leftmost_bit & byte_aux;
			byte_aux = byte_aux << 1;
			setBit((pos + i), and_res);
		}
	}
}

bool BinaryArray2::getBitAsBool(unsigned int pos) {
	unsigned int bytePos = pos / 8;
	unsigned int bitOffset = pos % 8;
	unsigned char left_bit = 0x01;
	left_bit = left_bit << bitOffset;
	if(left_bit & array[bytePos])
		return 1;
	return 0;
}

char BinaryArray2::getBit(unsigned int pos) {
	unsigned int bytePos = pos / 8;
	unsigned int bitOffset = pos % 8;
	unsigned char left_bit = 0x01;
	left_bit = left_bit << bitOffset;
	return (left_bit & array[bytePos]);
}

std::vector<unsigned char> BinaryArray2::Binary() {
	return array;
}

unsigned char& BinaryArray2::operator[](unsigned int pos) {
	return array[pos];
}

void BinaryArray2::push_byte_back(char byte) {
	array.push_back(byte);
}

void BinaryArray2::push_array_front(std::vector<unsigned char> vec) {
	std::vector<unsigned char> aux;
	for(int i = 0; i < vec.size(); ++i)
		aux.push_back(vec[i]);
	for(int i = 0; i < array.size(); ++i) {
		aux.push_back(array[i]);
	}
	array = aux;
}

std::vector<unsigned char> BinaryArray2::Ascii8() {
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


std::ostream& operator<<(std::ostream& os, BinaryArray2& ba) {
	std::vector<unsigned char> vec = ba.Ascii8();
	for(unsigned int i = 0; i < ba.size(); ++i)
		os << vec[i];
	os << std::endl;
	return os;
}

unsigned int BinaryArray2::size() {
	return array.size();
}

std::string BinaryArray2::str() {
	std::string ret;
	for(unsigned int i = 0; i < this->array.size(); ++i)
		ret.push_back(array[i]);
	return ret;
}

void BinaryArray2::append(BinaryArray2 ba, unsigned int pos, unsigned int size) {
	for(int i = 0; i < size; ++i) {
		setBit(pos + i, ba.getBit(i));
	}
}

std::vector<unsigned char> BinaryArray2::Ascii() {
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

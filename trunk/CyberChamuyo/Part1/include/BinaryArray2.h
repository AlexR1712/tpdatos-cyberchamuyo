/*
 * BinaryArray2.h
 *
 *  Created on: 17/11/2012
 *      Author: sebastian
 */

#include <vector>
#include <ostream>

#ifndef BINARYARRAY2_H_
#define BINARYARRAY2_H_

class BinaryArray2 {
public:
	void pop_front();
	void addInt(unsigned int n);
	//	initializes array of size "size" with zeros
	BinaryArray2(unsigned int size);
	//	initializes array with data from the vector "vec"
	BinaryArray2(std::vector<unsigned char> vec);
	//	sets the bit in "pos" to "bit"
	void setBit(unsigned int pos, unsigned char bit);
	//	sets all bits from "posi" to "posf" with value "bit"
	void set(unsigned int posi, unsigned int posf, unsigned char bit);
	void setByte(unsigned int pos, unsigned char byte);
	void setByteInNBits(unsigned int pos, unsigned int n, unsigned char byte);
	//	returns the bit as its value, 0 or 1
	bool getBitAsBool(unsigned int pos);
	//	return a byte wich contains the corresponding bit in position "pos"
	//	from the array, and 0 elsewhere
	char getBit(unsigned int pos);
	//	returns the array as its raw binary data
	std::vector<unsigned char> Binary();
	//	returns the corresponding ascii values of the data stored in the array
	std::vector<unsigned char> Ascii();
	//	always returns the 8 bits of each byte, even if there are zeros to the left
	std::vector<unsigned char> Ascii8();
	//	works exactly as vector::operator[] (its a delegation to that operator)
	unsigned char& operator[](unsigned int pos);
	void push_byte_back(char byte);
	void push_array_front(std::vector<unsigned char> byte);
	friend std::ostream& operator<<(std::ostream& os, BinaryArray2& ba);
	unsigned int size();
	std::string str();
	void append(BinaryArray2 ba, unsigned int pos, unsigned int size);
	virtual ~BinaryArray2();
private:
	std::vector<unsigned char> array;
};

#endif /* BINARYARRAY_H_ */

/*
 * BinaryArray.h
 *
 *  Created on: 17/11/2012
 *      Author: sebastian
 */

#include <vector>

#ifndef BINARYARRAY_H_
#define BINARYARRAY_H_

class BinaryArray {
public:
	//	initializes array of size "size" with zeros
	BinaryArray(unsigned int size);
	//	initializes array with data from the vector "vec"
	BinaryArray(std::vector<unsigned char> vec);
	//	initializes array with data from char* vec
	BinaryArray(const char* vec);
	//	sets the bit in "pos" to "bit"
	void setBit(unsigned int pos, unsigned char bit);
	//	sets all bits from "posi" to "posf" with value "bit"
	void set(unsigned int posi, unsigned int posf, unsigned char bit);
	//	returns the bit as its value, 0 or 1
	bool getBitAsBool(unsigned int pos);
	//	return a byte wich contains the corresponding bit in position "pos"
	//	from the array, and 0 elsewhere
	char getBit(unsigned int pos);
	//	returns the array as its raw binary data
	std::vector<unsigned char> Binary();
	//	returns the corresponding ascii values of the data stored in the array
	//	always returns the 8 bits of each byte, even if there are zeros to the left
	std::vector<unsigned char> Ascii();
	//	works exactly as vector::operator[] (its a delegation to that operator)
	unsigned char& operator[](unsigned int pos);
	virtual ~BinaryArray();
private:
	std::vector<unsigned char> array;
};

#endif /* BINARYARRAY_H_ */

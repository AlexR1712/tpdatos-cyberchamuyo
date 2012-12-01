/*
 * FixedLengthTRecord.h
 *
 *  Created on: 30/11/2012
 *      Author: sebastian
 */

#ifndef FIXEDLENGTHTRECORD_H_
#define FIXEDLENGTHTRECORD_H_

#include "fixedLengthRecord.h"

class FixedLengthTRecord : public FixedLengthRecord {
private:
	unsigned int termId;
	std::string term;
public:
	void setTerm(std::string term);
	void setId(unsigned int id);
	unsigned int getId();
	std::string getTerm();
	virtual void deserialize(std::vector<unsigned char>& dataAsArray);
	virtual void serialize(std::vector<unsigned char>& dataAsArray);
	FixedLengthTRecord(unsigned int size);
	virtual ~FixedLengthTRecord();
};

#endif /* FIXEDLENGTHTRECORD_H_ */

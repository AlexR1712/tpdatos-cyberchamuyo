/*
 * OcurrenceFileRecord.h
 *
 *  Created on: 22/11/2012
 *      Author: sebastian
 */

#ifndef OCURRENCEFILERECORD_H_
#define OCURRENCEFILERECORD_H_

#include "../include/record.h"

class OcurrenceFileRecord : public Record {
private:
	int termId;
	int docId;
public:
	OcurrenceFileRecord();

	int getTermId();

	void setTermId(int id);

	void setDocId(int id);

	int getDocId();

	virtual void deserialize(std::vector<unsigned char>& recordAsCharVector);

	virtual void serialize(std::vector<unsigned char>& recordAsCharVector);

	virtual ~OcurrenceFileRecord();
};

#endif /* OCURRENCEFILERECORD_H_ */

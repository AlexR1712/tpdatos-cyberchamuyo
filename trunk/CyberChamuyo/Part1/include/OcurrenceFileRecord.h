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
	unsigned int termId;

	unsigned int docId;

public:
	OcurrenceFileRecord();

	unsigned int getTermId() const;

	void setTermId(unsigned int id);

	unsigned int getDocId() const;

	void setDocId(unsigned int id);

	virtual void deserialize(std::vector<unsigned char>& recordAsCharVector);

	OcurrenceFileRecord& operator=(const OcurrenceFileRecord& other);

	bool operator>(const OcurrenceFileRecord& other);

	bool operator<(const OcurrenceFileRecord& other);

	virtual void serialize(std::vector<unsigned char>& recordAsCharVector);

	virtual ~OcurrenceFileRecord();
};

#endif /* OCURRENCEFILERECORD_H_ */

#include "../include/fixedLengthRecord.h"

#include <stdlib.h>
#include <iostream>

#include "../include/stringUtilities.h"

FixedLengthRecord::FixedLengthRecord(unsigned int recordSize) {
	this->recordSize = recordSize;
}

unsigned int FixedLengthRecord::getRecordSize() const {
    return this->recordSize;
}

void FixedLengthRecord::setRecordSize(unsigned int recordSize) {
	this->recordSize = recordSize;
}

FixedLengthRecord::~FixedLengthRecord() {
}

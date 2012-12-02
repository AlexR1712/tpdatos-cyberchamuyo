#include "../include/fixedLengthRecord.h"

#include <stdlib.h>
#include <iostream>

#include "../include/stringUtilities.h"

FixedLengthRecord::FixedLengthRecord(unsigned int recordSize) {
	this->setRecordSize(recordSize);
}

FixedLengthRecord::~FixedLengthRecord() {
}

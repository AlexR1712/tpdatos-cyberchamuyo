#include "../include/record.h"

#include <stdlib.h>
#include <iostream>

#include "../include/stringUtilities.h"

Record::Record() {
}

void Record::setRecordSize(unsigned int recordSize) {
	this->recordSize = recordSize;
}

unsigned int Record::getRecordSize() const {
	return this->recordSize;
}

Record::~Record() {
}

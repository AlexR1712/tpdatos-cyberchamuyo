#include "statisticsRecord.h"

#include <stdlib.h>
#include <iostream>

#include "stringUtilities.h"

StatisticsRecord::StatisticsRecord() {
}

std::vector<unsigned int>& StatisticsRecord::getFilesStatistics() {
    return this->filesStatistics;
}

std::string StatisticsRecord::serialize(std::string itemName) {
	std::string recordAsString;

	for (unsigned int i = 0; i < this->getFilesStatistics().size(); i++) {
		recordAsString += itemName + " " + intToString(i + 1) + " - " + intToString(this->getFilesStatistics()[i]) + " registros." + '\n';
	}

	return recordAsString;
}

StatisticsRecord::~StatisticsRecord() {
}

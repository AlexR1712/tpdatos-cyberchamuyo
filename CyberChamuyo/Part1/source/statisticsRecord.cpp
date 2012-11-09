#include "../include/statisticsRecord.h"

#include <stdlib.h>
#include <iostream>

#include "../include/stringUtilities.h"

StatisticsRecord::StatisticsRecord() {
}

std::vector<unsigned int>& StatisticsRecord::getFilesStatistics() {
    return this->filesStatistics;
}

std::string StatisticsRecord::serialize(std::string itemName) {
	std::string recordAsString;

	for (unsigned int i = 0; i < this->getFilesStatistics().size(); i++) {
		recordAsString += itemName + " " + StringUtilities::intToString(i + 1) + " - " + StringUtilities::intToString(this->getFilesStatistics()[i]) + " registros." + '\n';
	}

	return recordAsString;
}

StatisticsRecord::~StatisticsRecord() {
}

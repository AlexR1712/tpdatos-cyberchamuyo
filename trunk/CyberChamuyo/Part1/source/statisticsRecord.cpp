#include "statisticsRecord.h"

#include <stdlib.h>
#include <iostream>

#include "stringUtilities.h"

StatisticsRecord::StatisticsRecord() {
}

std::vector<unsigned int>& StatisticsRecord::getFilesStatistics() {
    return this->filesStatistics;
}

unsigned int StatisticsRecord::getLevel() const {
    return this->level;
}

void StatisticsRecord::setLevel(unsigned int level) {
    this->level = level;
}

std::string StatisticsRecord::serialize() {
	std::string recordAsString;

	recordAsString += "Etapa: " + intToString(this->getLevel()) + '\n';

	for (unsigned int i = 0; i < this->getFilesStatistics().size(); i++) {
		recordAsString += "Archivo " + intToString(i + 1) + " - " + intToString(this->getFilesStatistics()[i]) + " registros." + '\n';
	}

	recordAsString += "Total archivos: " + intToString(this->getFilesStatistics().size()) + '\n';

	return recordAsString;
}

StatisticsRecord::~StatisticsRecord() {
}

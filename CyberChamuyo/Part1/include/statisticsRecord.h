#include <string>
#include <ostream>
#include <vector>
#include "record.h"

#ifndef STATISTICSRECORD_H_
#define STATISTICSRECORD_H_

class StatisticsRecord {
public:
	std::vector<unsigned int> filesStatistics;

	StatisticsRecord();

	std::vector<unsigned int>& getFilesStatistics();

	std::string serialize(std::string itemName);

	virtual ~StatisticsRecord();
};

#endif /* STATISTICSRECORD_H_ */

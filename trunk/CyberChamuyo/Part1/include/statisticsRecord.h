#include <string>
#include <ostream>
#include <vector>
#include "record.h"

#ifndef STATISTICSRECORD_H_
#define STATISTICSRECORD_H_

class StatisticsRecord {
private:
	int level;

public:
	std::vector<unsigned int> filesStatistics;

	StatisticsRecord();

	std::vector<unsigned int>& getFilesStatistics();

	unsigned int getLevel() const;

	void setLevel(unsigned int level);

	std::string serialize();

	virtual ~StatisticsRecord();
};

#endif /* STATISTICSRECORD_H_ */

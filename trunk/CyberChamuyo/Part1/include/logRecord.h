#ifndef LOGRECORD_H_
#define LOGRECORD_H_

#include <string>
#include <vector>

#include "record.h"

class LogRecord : Record{
private:
	std::string title;

	std::string itemName;

	std::vector<unsigned int> logItems;

	std::string getTitle() const;

	void setTitle(std::string title);

	std::string getItemName() const;

	void setItemName(std::string logItemName);

public:
	LogRecord(std::string title, std::string itemName);

	void deserialize(std::string string);

	std::vector<unsigned int>& getLogItems();

	LogRecord& operator=(LogRecord& other);

	std::string serialize();

	virtual ~LogRecord();
};

#endif /* LOGRECORD_H_ */

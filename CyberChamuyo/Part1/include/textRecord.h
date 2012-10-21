#ifndef TEXTRECORD_H_
#define TEXTRECORD_H_

#include <string>
#include "record.h"

class TextRecord : public Record {
private:
	std::string data;

public:
	TextRecord();

	void deserialize(std::string string);

	TextRecord& operator=(const TextRecord& other);

	std::string getData() const;

	void setData(std::string data);

	std::string serialize();

	virtual ~TextRecord();
};

#endif /* TEXTRECORD_H_ */

#include <string>

#ifndef RECORD_H_
#define RECORD_H_

class Record {
public:
	Record();

	virtual void deserialize(std::string string) = 0;

	virtual std::string serialize() = 0;

	virtual ~Record() = 0;
};

#endif /* RECORD_H_ */

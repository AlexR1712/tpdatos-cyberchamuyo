#include <string>
#include <ostream>
#include "record.h"

#ifndef STRINGRECORD_H_
#define STRINGRECORD_H_

#ifndef ID_AS_STRING_LENGTH
#define ID_AS_STRING_LENGTH 9
#endif /*ID_AS_STRING_LENGTH*/

#ifndef ID_PADDING_CHAR
#define ID_PADDING_CHAR '0'
#endif /*ID_PADDING_CHAR*/

class StringRecord : public Record {
public:
	StringRecord(bool idVisible = true);

	void parseString(std::string string);

	std::string serialize();

	virtual ~StringRecord();
};

#endif /* STRINGRECORD_H_ */

#include <string>
#include <ostream>
#include "record.h"

#ifndef BINARYGRECORD_H_
#define BINARYGRECORD_H_

#ifndef SIZE_IN_CHAR
#define SIZE_IN_CHAR 30
#endif /*SIZE_IN_CHAR*/

class BinaryRecord : public Record {
public:
	BinaryRecord(bool idVisible = true);

	void parseString(std::string string);

	std::string serialize();

	virtual ~BinaryRecord();
};

#endif /* BINARYGRECORD_H_ */

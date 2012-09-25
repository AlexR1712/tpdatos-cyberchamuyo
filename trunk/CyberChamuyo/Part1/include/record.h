#include <string>
#include <ostream>


#include <sstream>

#ifndef RECORD_H_
#define RECORD_H_

#ifndef DEFAULT_SEPARATOR
#define DEFAULT_SEPARATOR '\t'
#endif /*DEFAULT_SEPARATOR*/

class Record {
private:
	unsigned long int id;

	std::string word;

	bool idVisible;

	unsigned short int sizeInChar;

protected:
	void setId(unsigned long int id);

	void setWord(const std::string& word);

	void setSizeInChar(unsigned short int sizeInChar);

public:
	Record(bool idVisible = true);

	unsigned long int getId() const;

	const std::string& getWord() const;

	bool isIdVisible() const;

	void setIdVisible(bool isIdVisible);

	unsigned short int getSizeInChar() const;

	Record& operator=(const Record& other);

	bool operator>(const Record& other);

	bool operator<(const Record& other);

	virtual void parseString(std::string string) = 0;

	virtual std::string serialize() = 0;

	virtual ~Record() = 0;
};

#endif /* RECORD_H_ */

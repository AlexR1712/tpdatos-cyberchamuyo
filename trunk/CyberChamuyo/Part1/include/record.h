#include <string>
#include <ostream>

#ifndef RECORD_H_
#define RECORD_H_

class Record {
private:
	int id;

	std::string word;

	void setId(int id);

	void setWord(const std::string& word);
public:
	Record();

	int getId() const;

	const std::string& getWord() const;

	void parseString(std::string string);

	Record& operator=(const Record& other);

	bool operator>(const Record& other);

	bool operator<(const Record& other);

	friend std::ostream& operator<<(std::ostream& ostream, Record& record);

	~Record();
};

#endif /* RECORD_H_ */

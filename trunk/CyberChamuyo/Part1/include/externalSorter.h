#ifndef EXTERNALSORTER_H_
#define EXTERNALSORTER_H_

#include <string>

#ifndef N
#define N 2
#endif /*N*/

class ExternalSorter {
public:
	ExternalSorter();

	void sort(std::string filepath);

	~ExternalSorter();
};

#endif /* EXTERNALSORTER_H_ */

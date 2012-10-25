/*
 * FrontCoding.h
 *
 *  Created on: 06/10/2012
 *      Author: sebastian
 */

#include <string>
#include <vector>

#ifndef FRONTCODING_H_
#define FRONTCODING_H_

class FrontCoding {
public:
	FrontCoding();
	virtual ~FrontCoding();
	int encode(const std::string& word, std::string& res);
	int encode(const std::vector<char>* word, std::vector<char>* res);
	int decode(const std::string& word, std::string& deco);
private:
	std::string previous;
};

#endif /* FRONTCODING_H_ */

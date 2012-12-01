/*
 * RegistroT.h
 *
 *  Created on: 27/11/2012
 *      Author: sebastian
 */

#ifndef REGISTROT_H_
#define REGISTROT_H_

#include <string>
#include <vector>
#include "../include/common.h"

class RegistroT {
	private:
		std::string term;
		unsigned int termId;
	public:
		RegistroT();
		std::vector<char> seriallize();
		void deseriallize(std::vector<char>& data);
		std::string getTerm();
		~RegistroT();
};


#endif /* REGISTROT_H_ */

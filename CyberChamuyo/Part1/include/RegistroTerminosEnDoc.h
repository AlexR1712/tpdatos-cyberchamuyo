/*
 * RegistroTerminosEnDoc.h
 *
 *  Created on: 27/11/2012
 *      Author: sebastian
 */

#ifndef REGISTROTERMINOSENDOC_H_
#define REGISTROTERMINOSENDOC_H_

#include <vector>

class RegistroTerminosEnDoc {
	private:
		unsigned int termId;
		unsigned int docId;
	public:
		RegistroTerminosEnDoc();
		unsigned int getTermId();
		unsigned int getDocId();
		std::vector<char> seriallize();
		void deseriallize(std::vector<char>& data);
		~RegistroTerminosEnDoc();
};


#endif /* REGISTROTERMINOSENDOC_H_ */

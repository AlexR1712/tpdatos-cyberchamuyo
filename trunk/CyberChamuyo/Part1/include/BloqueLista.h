/*
 * BloqueLista.h
 *
 *  Created on: 02/12/2012
 *      Author: sebastian
 */

#ifndef BLOQUELISTA_H_
#define BLOQUELISTA_H_

#include "InvertedList.h"

class BloqueLista {
	//	Este tipo de bloque va a tener que poder encadenarse
public:
	void putRecord(InvertedList invL);
	InvertedList getRecord();
	BloqueLista();
	virtual ~BloqueLista();
};

#endif /* BLOQUELISTA_H_ */

/*
 * IndiceArbol.h
 *
 *  Created on: 11/10/2012
 *      Author: sebastian
 */
#include "ArbolBp.h"
#include <string>
#include "../SecuentialFile/include/textInputSequentialFile.h"
#include "../SecuentialFile/include/textDictionaryRecord.h"

#ifndef INDICEARBOL_H_
#define INDICEARBOL_H_

class IndiceArbol {
public:
	IndiceArbol(TextInputSequentialFile<TextDictionaryRecord<false> >& f, const char* nombre_arch_arbol, int b_size);
	virtual ~IndiceArbol();
private:
	void crearIndice(std::ifstream& arch);
	ArbolBp arbol;
};

#endif /* INDICEARBOL_H_ */

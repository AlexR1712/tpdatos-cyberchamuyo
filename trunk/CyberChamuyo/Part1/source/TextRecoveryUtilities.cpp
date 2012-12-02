/*
 * TextRecoveryUtilities.cpp
 *
 *  Created on: 21/11/2012
 *      Author: sebastian
 */

#include "../include/TextRecoveryUtilities.h"
#include <math.h>
#include <cstring>

namespace TextRecoveryUtilities {

void uintToString(char* buffer, unsigned int i) {
	buffer[0] = i;
	buffer[1] = i >> 8;
	buffer[2] = i >> 16;
	buffer[3] = i >> 24;
}

#define HALF_MAX 2100000000

void cargarArchivosTerminos(Hash::DispersionEx F, VariableLengthRecordSequentialFile<BinaryDictionaryRecord<true> >& T, VariableLengthRecordSequentialFile<BinaryDictionaryRecord<true> >& termInDocFile) {
	/*unsigned int totalPhrases = 0; //temporal
	unsigned int processedPhrases = 0;
	while(processedPhrases < totalPhrases) {
		Data::Frase phrase = F.getNext();					//	obtener frases secuencialmente del hash
		std::vector<std::string> parsedPhrase;
		parsedPhrase = MetodoParsearFrase(phrase); 		//	parsear phrase, separar en tokens, normalizar e ignorar stopwords
		unsigned int docId = phrase.getId();			//	obtengo id de la frase
		while(i < parsedPhrase.size()) {				//	para cada palabra indexable
			if(!IndiceArbol.search(parsePhrase[j])) {	//	si no esta en el vocabulario (arbol)
				unsigned int termId = T.writeAtEnd(word);// la agrego al archivo T y obtengo el id
				termInDocFile.write(termId, docId);		//	la agrego al archivo de ocurrencia de terminos en documentos
				IndiceArbol.insert(word, id, 0);		//	la agrego al arbol junto con su id, tengo que sobrecargar el insert para q acepte esto
			}
			++i;
		}
	}
	externalSorter.sort(termInDocFile);					//	tengo que fijarme bien como decirle por que campo ordenar
*/
}

void cargarListasInvertidas(VariableLengthRecordSequentialFile<BinaryDictionaryRecord<true> > termInDocFile) {
	//	termInDocFile.reset();
	/*
	 *	RegisterTermFile reg = termInDocFile.getNext();			//	obtengo registros (termID, docId) secuencialmente
	 *	int invertedListId = 0;
	 *	while(!termInDocFile.eof()) {
	 *		unsigned int termId = reg.getTermId();
	 *		InvertedList invertedList(termId);					//	inicializo lista invertida con id de termino
	 *		while(reg.getTermId() == termId) {					//	mientras siga leyendo el mismo id del archivo
	 *			invertedList.push_back(reg.getDocId());			//	agrego docId a lista invertida
	 *			regAux = reg;
	 *			reg = termInDocFile.getNext();					//	obtengo siguiente
	 *		}
	 *		invertedListFile.write(invertedList.seriallize());	//	una vez que terminaron todos los doc para ese termino escribo la lista
	 *		std::string term = T.read(termId());				//	obtengo el termino desde el archivo T pasandole el id correspondiente
	 *		if(IndiceArbol.search(term))						//	si el termino esta en el arbol
	 *			IndiceArbol.modify(term, termId, invertedListId);//	modifica el registro agregandole la lista invertida, este metodo lo tengo que hacer
	 *		invertedListId++;									//	sumo 1 al identificador de listas invertidas
	 *	}
	 */
}

void cargarMapaTerminos() {

}



unsigned int gammaSize(unsigned int n) {
	unsigned long b = log2(n);
	return (b * 2) + 1;
}

unsigned int bitCount(unsigned int n) {
	unsigned int f = 0x80000000;
	bool res = false;
	unsigned int cont = 0;
	while(!res) {
		res = f & n;
		n = n << 1;
		cont++;
	}
	return 32 - cont + 1;
}


unsigned int bitCountByte(char c) {
	unsigned int f = 0x80;
	bool res = false;
	unsigned int cont = 0;
	while(!res) {
		res = f & c;
		c = c << 1;
		cont++;
	}
	return 8 - cont + 1;
}


char trimZeros(char c) {
	char f = 0x80;
	bool rest = f & c;
	while(!rest) {
		c = c << 1;
		rest = f & c;
	}
	return c;
}

BinaryArray2 gammaEncode(unsigned long n) {
	unsigned long b = log2(n);
	if(b == 0) {
		BinaryArray2 ret(0);
		ret.setBit(0, 0);
		return ret;
	}
	unsigned long ex = exp2((float)b);
	unsigned long rest = n - ex;
	unsigned long restAux = rest;
	unsigned int count = 0;
	if(rest) {
		while(!(rest & 0x80000000)) {
			rest = rest << 1;
			++count;
		}
	}
	unsigned int bits = sizeof(long)*8 - count;
	unsigned int topb = b/8;
	if(b % 8)
		topb++;
	BinaryArray2 enc(topb);
	enc.set(0, b - 1, 1);
	enc.setBit(b, 0);
	unsigned int cantBytes = (b - 1)/8 + 1;
	char word[4];
	uintToString(word, restAux);
	//if(cantBytes == 1) {
		//unsigned char c = word[0];
		//enc.setByteInNBits(b + 1, b, c);
	//} else {
		std::vector<unsigned char> vec_aux;
		for(int i = 0; i < (b/8 +1); ++i)
			vec_aux.push_back(word[i]);
		BinaryArray2 ba(vec_aux);
		for(int i = 0; i < b; ++i) {
			int b_pos = i / 8;
			enc.setBit(b + 1 + i, ba.getBit(b - 1 - i));
		}
	//}
	return enc;
}

unsigned int gammaDecode(BinaryArray2 array, unsigned int pos) {
	//unsigned char bit = array[pos / 8];
	//bit = bit << (pos % 8);
	//bit = bit >> (pos % 8);
	unsigned int cant = 0;
	bool bit = array.getBitAsBool(pos + cant);
	while(bit) {
		++cant;
		bit = array.getBit(pos + cant);
	}
	if(cant == 0)
		return 1;
	unsigned int n = exp2(cant);
	std::vector<unsigned char> buffer;
	BinaryArray2 ba(4);
	for(unsigned int i = 0; i < cant; ++i) {
		ba.setBit(i, array.getBit(pos + cant + cant - i));
	}
	unsigned int resto = ba[0] | (ba[1] << 8) | (ba[2] << 16) | (ba[3] << 24);
	return resto + n;
}
/*
unsigned int gammaDecode(BinaryArray2 array) {
	char bit = array[0];
	unsigned int cant = 0;
	while(bit) {
		++cant;
		bit = array.getBit(cant);
	}
	unsigned int n = exp2(cant);
	std::vector<unsigned char> buffer;
	unsigned int byte_pos = cant / 8;
	BinaryArray2 ba(4);
	for(int i = 0; i < cant; ++i) {
		ba.setBit(i, array.getBit(cant + cant - i));
	}
	unsigned int resto = ba[0] | (ba[1] << 8) | (ba[2] << 16) | (ba[3] << 24);
	return resto + n;
}
*/

}

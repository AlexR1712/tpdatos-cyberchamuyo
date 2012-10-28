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

//  FrontCoding: Clase que permite codificar y decodificar a front coding

class FrontCoding {
public:
	FrontCoding();
	virtual ~FrontCoding();

	//	recibe "word" palabra a codificar y devuelve "res" palabra codificada
	//  si es la primer palabra no se codifica. La palabra codificada incluye el prefijo de
	//  caracteres compartidos con anterior palabra
	int encode(const std::string& word, std::string& res);
	int encode(const std::vector<char>* word, std::vector<char>* res);

	//  recibe "word" palabra codificada y devuelve palabra decodificada
	int decode(const std::string& word, std::string& deco);
private:
	std::string previous;
};

#endif /* FRONTCODING_H_ */

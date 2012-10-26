/*
 * main.c
 *
 *  Created on: 06/09/2012
 *      Author: sebastian
 */
#include "../include/CEntero.h"
#include "../include/Registro.h"
#include "../include/NodoExterno.h"
#include "../include/ArbolBp.h"
#include "../include/NodoInterno.h"
#include <sstream>
#include "../include/CAlfa.h"
#include "../include/FrontCoding.h"
#include "../include/IndiceArbol.h"

void lala() {

}

int main(int argc, char** argv) {

	ArbolBp arbol("arbol.bin", N_SIZE);
	/*for(int i = 1; i < 10; ++i) {
		std::stringstream ss;
		ss << i;
		std::string s("reg");
		std::string s2;
		ss >> s2;
		s = s + s2;
		Clave* c1test = new CAlfa(s);
		Registro* r1test = new Registro(c1test, "Registrolala");
		arbol.insertarRegistro(r1test);
	}*/
	CAlfa c("reg554");
	Registro* reg;
	arbol.buscar(&c, reg);
	std::cout << *reg << std::endl << (*arbol.siguiente()) << std::endl;
	//arbol.imprimirNodos();


	/*TextInputSequentialFile<TextDictionaryRecord<false> > arch_in("dictionary.txt", 100);
	IndiceArbol ind(arch_in, "archarb.bin", 512);*/
	return 0;
}

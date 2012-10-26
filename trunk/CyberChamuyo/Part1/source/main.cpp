/*
 * main.c
 *
 *  Created on: 06/09/2012
 *      Author: sebastian
 */
#include "CEntero.h"
#include "Registro.h"
#include "NodoExterno.h"
#include "ArbolBp.h"
#include "NodoInterno.h"
#include <sstream>
#include "CAlfa.h"
#include "FrontCoding.h"
#include "IndiceArbol.h"
/*
int main(int argc, char** argv) {
/*
	ArbolBp arbol((char*)"arbol.bin", N_SIZE);
	for(int i = 1; i < 10; ++i) {
		std::stringstream ss;
		ss << i;
		std::string s("reg");
		std::string s2;
		ss >> s2;
		s = s + s2;
		Clave* c1test = new CAlfa(s);
		Registro* r1test = new Registro(c1test, "Registrolala");
		arbol.insertarRegistro(r1test);
		delete r1test;
	}
	CAlfa c("reg2");
	Registro* reg = new Registro();
	arbol.buscar(&c, reg);
	std::cout << *reg << std::endl;
	//std::cout << *(arbol.siguiente()) << std::endl;
	//std::cout << *(arbol.siguiente()) << std::endl;
	//std::cout << *(arbol.siguiente()) << std::endl;
	arbol.imprimirNodos();
	arbol.exportar(std::cout);
	delete reg;
*/
/*
	//TextInputSequentialFile<TextDictionaryRecord<false> > arch_in("dictionary_NORMALIZED.txt", 100);
	IndiceArbol ind;
	std::string path("dictionary_NORMALIZED.txt");
	ind.createIndex(path);
	std::string palabra("sarasa");
	ind.insert(palabra);
	ind.exportar("IndiceExportado.txt");
	std::cout << "El resultado de la busqueda es " << ind.find("abacio")  << std::endl;
	std::cout << "El resultado de hasNext es " << ind.hasNext() << std::endl;
	BinaryDictionaryRecord<true> reg;
	reg = ind.next();
	std::cout << "El siguiente registro es " << reg.getWord() << std::endl;
	ind.clear();
	std::cout << "Clear se ejecuto correctamente" << std::endl;
	return 0;
}
*/

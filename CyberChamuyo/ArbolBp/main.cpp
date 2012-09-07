/*
 * main.c
 *
 *  Created on: 06/09/2012
 *      Author: sebastian
 */
#include "CEntero.h"
#include "Registro.h"
#include "NodoExterno.h"

int main(int argc, char** argv) {
	Clave* c1 = new C_Entero(1);
	Clave* c2 = new C_Entero(2);
	Clave* c3 = new C_Entero(3);
	Registro* r1 = new Registro(c1, "Registro1");
	Registro* r2 = new Registro(c2, "Registro2");
	Registro* r3 = new Registro(c3, "Registro3");
	NodoExterno n1(1);
	NodoExterno n2(1);
	n1.insertarRegistro(r1);
	std::cout << "antes de la suma tengo " << n1 << std::endl;

	n2.insertarRegistro(r2);
	n1 = n1 + n2;
	std::cout << "despues de la suma tengo " << n1 << std::endl;

	n1.insertarRegistro(r3);
	std::cout << "despues de agregar r3 tengo  " << n1 << std::endl;

	std::list<Registro*> registros_derecha = n1.getRegistrosDerecha();
	std::list<Registro*>::iterator it;
	std::cout << "Los registros de la derecha son: " << std::endl;
	for(it = registros_derecha.begin(); it != registros_derecha.end(); ++it) {
		std::cout << *(*it);
	}
	std::cout << std::endl;

	n1 = n1 - n2;
	std::cout << "despues de la resta tengo " << n1 << std::endl;
	std::string s = n1.serializar();
	NodoExterno n3;
	n3.hidratar(s);
	std::cout << "Rehidratado tengo "<< n3 << std::endl;

	Clave* c4 = new C_Entero(4);
	Registro* r4 = new Registro(c4, "Registro4");
	n1.insertarRegistro(r4);
	std::cout << "Despues de insertar r4 tengo " << n1 << std::endl;
	n1.eliminarRegistro(c4);
	std::cout << "Despues de eliminar r4 tengo " << n1 << std::endl;

	return 0;
}

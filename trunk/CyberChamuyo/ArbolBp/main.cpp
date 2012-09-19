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

int main(int argc, char** argv) {
	Clave* c1 = new C_Entero(1);
	Clave* c2 = new C_Entero(5);
	Clave* c3 = new C_Entero(10);
	Clave* c4 = new C_Entero(3);
	Clave* c5 = new C_Entero(14);
	Clave* c6 = new C_Entero(8);
	Clave* c7 = new C_Entero(18);
	Clave* c8 = new C_Entero(21);
	Clave* c9 = new C_Entero(25);
	Clave* c10 = new C_Entero(30);
	Clave* c11 = new C_Entero(34);
	Clave* c12 = new C_Entero(40);
	Clave* c13 = new C_Entero(22);
	Clave* c14 = new C_Entero(39);
	Clave* c15 = new C_Entero(11);
	Clave* c16 = new C_Entero(23);
	Clave* c17 = new C_Entero(17);
	Clave* c18 = new C_Entero(19);
	Clave* c19 = new C_Entero(37);
	Clave* c20 = new C_Entero(33);
	Clave* c21 = new C_Entero(9);
	Clave* c22 = new C_Entero(50);
	Clave* c23 = new C_Entero(60);
	Clave* c24 = new C_Entero(100);
	Clave* c25 = new C_Entero(90);
	Clave* c26 = new C_Entero(85);
	Clave* c27 = new C_Entero(87);
	Clave* c28 = new C_Entero(77);
	Clave* c29 = new C_Entero(105);
	Clave* c30 = new C_Entero(69);
	Clave* c31 = new C_Entero(67);
	Clave* c32 = new C_Entero(82);
	Clave* c33 = new C_Entero(114);
	Clave* c34 = new C_Entero(200);
	Clave* c35 = new C_Entero(115);
	Clave* c36 = new C_Entero(91);
	Clave* c37 = new C_Entero(108);


	Registro* r1 = new Registro(c1, "Registro1");
	Registro* r2 = new Registro(c2, "Registro5");
	Registro* r3 = new Registro(c3, "Registro10");
	Registro* r4 = new Registro(c4, "Registro3");
	Registro* r5 = new Registro(c5, "Registro14");
	Registro* r6 = new Registro(c6, "Registro8");
	Registro* r7 = new Registro(c7, "Registro18");

	Registro* r8 = new Registro(c8, "Registro21");
	Registro* r9 = new Registro(c9, "Registro25");
	Registro* r10 = new Registro(c10, "Registro30");
	Registro* r11 = new Registro(c11, "Registro34");

	Registro* r12 = new Registro(c12, "Registro40");
	Registro* r13 = new Registro(c13, "Registro22");
	Registro* r14 = new Registro(c14, "Regis");
	Registro* r15 = new Registro(c15, "Regist");
	Registro* r16 = new Registro(c16, "Regist");
	Registro* r17 = new Registro(c17, "Regist2");
	Registro* r18 = new Registro(c18, "Regis");
	Registro* r19 = new Registro(c19, "Regro11");
	Registro* r20 = new Registro(c20, "Re9");
	Registro* r21 = new Registro(c21, "Reg1");

	Registro* r22 = new Registro(c22, "Regist");
	Registro* r23 = new Registro(c23, "Regist2");
	Registro* r24 = new Registro(c24, "Regis");
	Registro* r25 = new Registro(c25, "Regro11");
	Registro* r26 = new Registro(c26, "Re9");
	Registro* r27 = new Registro(c27, "Reg1");
	Registro* r28 = new Registro(c28, "Reg1");

	Registro* r29 = new Registro(c29, "Regist");
	Registro* r30 = new Registro(c30, "Regist2");
	Registro* r31 = new Registro(c31, "Regis");
	Registro* r32 = new Registro(c32, "Regro11");
	Registro* r33 = new Registro(c33, "Re9");
	Registro* r34 = new Registro(c34, "Reg1");
	Registro* r35 = new Registro(c35, "Reg1");
	Registro* r36 = new Registro(c36, "Reg1");
	Registro* r37 = new Registro(c37, "Reg1");


	ArbolBp arbol("arbol.bin", 480);
	arbol.insertarRegistro(r1);
	arbol.insertarRegistro(r2);
	arbol.insertarRegistro(r3);
	arbol.insertarRegistro(r4);
	arbol.insertarRegistro(r5);
	arbol.insertarRegistro(r6);
	arbol.insertarRegistro(r7);
	arbol.insertarRegistro(r8);
	arbol.insertarRegistro(r9);

	arbol.insertarRegistro(r10);
	arbol.insertarRegistro(r11);
	arbol.insertarRegistro(r12);
	arbol.insertarRegistro(r13);
	arbol.insertarRegistro(r14);
	arbol.insertarRegistro(r15);

	arbol.insertarRegistro(r16);
	arbol.insertarRegistro(r17);
	arbol.insertarRegistro(r18);
	arbol.insertarRegistro(r19);
	arbol.insertarRegistro(r20);
	arbol.insertarRegistro(r21);

	arbol.insertarRegistro(r22);
	arbol.insertarRegistro(r23);
	arbol.insertarRegistro(r24);
	arbol.insertarRegistro(r25);
	arbol.insertarRegistro(r26);
	arbol.insertarRegistro(r27);
	arbol.insertarRegistro(r28);

	arbol.insertarRegistro(r29);
	arbol.insertarRegistro(r30);
	arbol.insertarRegistro(r31);
	arbol.insertarRegistro(r32);
	arbol.insertarRegistro(r33);
	arbol.insertarRegistro(r34);
	arbol.insertarRegistro(r35);
	arbol.insertarRegistro(r36);
	arbol.insertarRegistro(r37);

	Registro* regBusqueda = NULL;
	Clave* clave_busqueda = new C_Entero(26);
	arbol.buscar(clave_busqueda, regBusqueda);
	std::cout << *regBusqueda << std::endl;
	std::cout << *(arbol.siguiente()) << std::endl;
	//  arbol.imprimirNodos();
	return 0;
}

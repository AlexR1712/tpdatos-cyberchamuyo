
/*
 * ArbolBp.h
 *
 *  Created on: 19/05/2012
 *      Author: sebastian
 */

#ifndef ARBOLBP_H_
#define ARBOLBP_H_

#include "NodoInterno.h"
#include "ArchivoBloquesFijos.h"
#include "Bloque.h"
#include <stdexcept>
#include "variableLengthRecordSequentialFile.h"
#include "DatoNodo.h"
#include "RegistroVariable.h"
#include "BloqueNodo.h"
#include "wordRankingRecord.h"

#define N_SIZE 480		//  tamaño de los nodos
#define OK 0			//  si insercion OK
#define OVERFLOW 1		//  si hubo overflow
#define GUARDAR 2		//  indicador de cambio
#define N_MIN (N_SIZE * 0.2)	//  colchon de bytes
#define REGISTRO_YA_EXISTENTE 3		//  registro ya se encuentra en el arbol

#define TIPO_ARBOL 1	//  se debe crear un tipo nuevo para cada tipo de clave
						//  y construir el arbol con ese tipo

class ArbolBp {
	friend class NodoInterno;
	friend class NodoExterno;
public:
	// Constructor que recibe nombre de archivo y tamaño de bloque
	ArbolBp(const char* filename, int block_size);

	virtual ~ArbolBp();

	//  permite visualizar el arbol en un formato entendible a simple vista.
	void imprimirNodos();

	//  Inserta un registro en el arbol. Recibe un registro creado
	int insertarRegistro(Registro* r);

	//  Busca el registro correspondiente a Clave c, lo coloca en reg y devuelve
	//  1, o si no lo encuentra coloca en reg el primero encontrado mayor al buscado
	//  y devuelve 0
	int buscar(Clave* c, Registro*& reg);

	void modify(Registro* reg);

	//  1 si esta vacio, 0 sino
	bool isEmpty();

	//  devuelve el nodo correspondiente a id, serializado
	std::vector<char>* leerNodo2(int id);

	//  registra como ultimo nodo leido a nE
	void setUltimoLeido(NodoExterno* nE);

	//  en caso de haberse realizado una busqueda antes, devuelve el registro siguiente
	//  al ultimo que fue devuelto, sino devuelve el primer registro
	Registro* siguiente();

	//  borra el arbol
	void clear();

	//  1 si hay siguiente registro, 0 sino
	bool hasNext();

	//  coloca el primer registro del arbol como ultimo leido
	void rewind();

	//  setea la posicion relativa en el nodo del ultimo registro leido
	void setUltimoRegistroLeido(int nReg);

	//  ultimoRegistroLeido++
	void aumentarUltimoRegistroLeido();

	//  devuelve un archivo secuencial os con todos los registros(datos) del arbol
	void exportar(VariableLengthRecordSequentialFile<WordRankingRecord>& os);

	//  devuelve el numero de nodo del primer nodo externo
	int encontrarPrimero();

	//  devuelve el ultimo nodo leido en memoria
	NodoExterno* getUltimoNodoLeido();
private:
	Nodo* raiz;											//  nodo raiz del arbol
	ArchivoBloquesFijos arch_arbol;						//  archivo de bloques donde se guardan los nodos
	int b_size;											//  tamaño nodos
	int max;											//  altura del arbol
	NodoExterno* ultimoNodoLeido;						//  para lectura secuencial
	int ultimoRegistroLeido;							//  para lectura secuencial

	void guardarNodo(Nodo* n);							// no se usa
	void guardarNodo(Nodo* n, unsigned int id);			// metodo para guardar un nodo
	int crearNodo();	// metodo en el que hay que obtener un bloque vacio


};

class Exc_GuardarArchivo : public runtime_error {
public:
	Exc_GuardarArchivo() : runtime_error("Error al guardar el archivo"){}
};

class Exc_LeerArchivo : public runtime_error {
public:
	Exc_LeerArchivo() : runtime_error("Error al leer el archivo"){}
};

class Exc_ArchivoInvalido : public runtime_error {
public:
	Exc_ArchivoInvalido() : runtime_error("El archivo de entrada esta corrupto"){}
};

class Exc_CrearArchivo : public runtime_error {
public:
	Exc_CrearArchivo() : runtime_error("No se pudo crear archivo"){}
};

class Exc_DesbordeBloque : public runtime_error {
public:
	Exc_DesbordeBloque() : runtime_error("El registro es demasiado grande para el tamaño de bloque elegido"){}
};

class Exc_UltimoNodo : public runtime_error {
public:
	Exc_UltimoNodo() : runtime_error("No hay mas registros"){}
};

#endif /* ARBOLBP_H_ */

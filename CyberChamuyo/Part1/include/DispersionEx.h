/*
 * DispersionEx.h
 *
 *  Created on: Sep 15, 2012
 *      Author: lucasj
 */

#ifndef DISPERSIONEX_H_
#define DISPERSIONEX_H_

#include "ArchivoBloquesFijos.h"
#include "DispersionExCtes.h"
#include "BloqueDato.h"
#include "BloqueTabla.h"
#include "_Aux.h"
#include "Tabla.h"
#include <iostream>
#include <sstream>


typedef std::list<Hash::RegistroDato*> listReg;
typedef std::list<Hash::RegistroDato*>::iterator itListReg;

// DISPERSION EX: Clase que implementa la dispersión extensible,

// ATRIBUTOS DISPERSION EX:
//
// ARCH_DISP: El archivo de bloques fijos que guarda los datos
// de la dispersión.
//
// TABLA: Clase que contiene la tabla de dispersión.
//
// numRandom: Número aleatorio que se le asigna a la frase.


namespace Hash {

class DispersionEx {
private:
	ArchivoBloquesFijos arch_disp;
	Tabla tabla;
	int insertarRecursivo(RegistroDato* r, unsigned int clave);
	void redistribuir(listReg& list);
	void ActualizarTablaAlta(unsigned int td, int posTabla);
	void ActualizarDispersion(BloqueDato& bl, int posTabla, int numBloque);
	void ActualizarBloqueDispersado(BloqueDato& bl, unsigned int td,
			int numBloque);
	void LlenarListaRegistros(BloqueDato& bl, listReg& list);
	void crearNuevoBloque(int nuevoBloque, unsigned int td);
	void Borrar(unsigned int clave);
	void Modificar(RegistroDato* r, unsigned int clave);
	void inicializarDispersion(void);
	void modificarTdBloques(void);
	void cambiarTdBloque(int posTabla);
public:
	DispersionEx(std::string archDir);
	void createIndex(std::string path);
	void insertarRegistro(RegistroDato* r, unsigned int clave);
	void modificarRegistro(RegistroDato* r, unsigned int clave);
	void modificar(std::string frase, std::string autor, unsigned int id);
	void borrarRegistro(unsigned int clave);
	void cargarFrases(const char* archFrases);
	bool getFrase(unsigned int clave, std::string& frase);
	void insert(std::string& phrase);
	bool isEmpty();
	unsigned int getLastId();
	void clear(void);
	virtual ~DispersionEx();
	friend std::ostream& operator<<(std::ostream& oss,
					  DispersionEx &disp);

};

std::ostream& operator<<(std::ostream& oss, DispersionEx &disp);

}
#endif

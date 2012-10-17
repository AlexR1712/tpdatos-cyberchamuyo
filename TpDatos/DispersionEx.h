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
#include "Aux.h"
#include "Tabla.h"
#include <iostream>


typedef std::list<RegistroVariable*> listReg;
typedef std::list<RegistroVariable*>::iterator itListReg;

namespace Hash {

class DispersionEx {
private:
	ArchivoBloquesFijos arch_disp;
	Tabla tabla;
	int insertarRecursivo(RegistroVariable* r, unsigned int clave);
	void redistribuir(listReg& list);
	void ActualizarTablaAlta(unsigned int td, int posTabla);
	void ActualizarDispersion(BloqueDato& bl, int posTabla, int numBloque);
	void ActualizarBloqueDispersado(BloqueDato& bl, unsigned int td,
			int numBloque);
	void LlenarListaRegistros(BloqueDato& bl, listReg& list);
	void crearNuevoBloque(int nuevoBloque, unsigned int td);
	void Borrar(unsigned int clave);
	void Modificar(RegistroVariable* r, unsigned int clave);
	int buscarRegistro(unsigned int clave, BloqueDato& bl);
	void modificarTdBloques(void);
public:
	DispersionEx(const char* archDir);
	void insertarRegistro(RegistroVariable* r, unsigned int clave);
	void modificarRegistro(RegistroVariable* r, unsigned int clave);
	void borrarRegistro(unsigned int clave);
	void cargarFrases(const char* archFrases);
	virtual ~DispersionEx();
	friend std::ostream& operator<<(std::ostream& oss,
					  DispersionEx &disp);

};

std::ostream& operator<<(std::ostream& oss, DispersionEx &disp);

}
#endif

/*
 * Tabla.h
 *
 *  Created on: Sep 29, 2012
 *      Author: lucasj
 */

#ifndef TABLA_H_
#define TABLA_H_

#include <math.h>
#include "ArchivoBloquesFijos.h"
#include "TablaCtes.h"
#include "BloqueTabla.h"
#include "Aux.h"

typedef std::list<unsigned int>::iterator itListaTabla;
typedef std::list<unsigned int> listaTabla;

// TABLA: Clase que representa la tabla de la dispersión.

// ATRIBUTOS TABLA:
//
// TABLA: Array de unsigned int con la tabla completa.
//
// ARCH: Archivo de Bloques Fijos.
//

namespace Hash {

class Tabla {
private:
	array tabla;
	ArchivoBloquesFijos& arch;
	void CargarTabla(void);
	void CrearBloqueTabla(Data::ArrayBytes* dato);
	void cargarListaBloquesTablaRecursiva(unsigned int pos, listaTabla& list);
	void cargarListaBloquesTabla(listaTabla& lBlTabla);
	void CargarTablaRecursivo(unsigned long int pos);
	void VincularAnterior(int pos, int siguiente);
	void Hidratar(const std::string& dato);
	void ActualizarBloque(unsigned int pos, Data::ArrayBytes* dato);
	void CrearBloqueTabla(int nuevoBloque, Data::ArrayBytes*& dato);
	void ParticionarTabla(listaTabla& list);
	void GuardarUnicaParticion(listaTabla& list);
	void ActualizarSiguiente(unsigned int pos);
	void ActualizarOCrear(itListaTabla& jt, listaTabla& list,
			Data::ArrayBytes* dato);
public:
	Tabla(ArchivoBloquesFijos& arch_disp);
	void GuardarTabla(void);
	void GuardarTablaInicial(void);
	unsigned int getSize(void);
	unsigned int getNumeroBloque(int posTabla);
	void actualizarTablaAlta(int nuevoBloque, int posTabla, unsigned int td);
	void RecorrerYReemplazar(int posTabla, long nuevoValor, unsigned int td);
	bool BuscarYReemplazar(int posTabla, unsigned int td);
	bool disminuirTabla(void);
	void Imprimir();
	virtual ~Tabla();
	void AumentarTabla();
	bool verificarEspejamiento();
};

}
#endif

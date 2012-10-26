/*
 * BloqueTabla.h
 *
 *  Created on: Sep 23, 2012
 *      Author: lucasj
 */

#ifndef BLOQUETABLA_H_
#define BLOQUETABLA_H_

#include "Bloque.h"
#include "RegistroTabla.h"

// BLOQUE TABLA: Tipo de Bloque que contiene particiones de la tabla
// de dispersión. Como esta tabla se guarda como una lista enlazada
// en el archivo binario, los bloques poseen una referencia al
// siguiente bloque con la continuación de la tabla.

// ATRIBUTOS BLOQUE TABLA
//
// SIGUIENTE: Número de bloque que contiene el próximo bloque
// tabla con la próxima partición de la tabla de dispersión.
//

class BloqueTabla: public Bloque {
private:
	unsigned int siguiente;
	virtual void LlenarRegistros(std::istream& oss, int cantReg);
	virtual void print(std::ostream& oss) const;
	virtual void input(std::istream& oss) const;
public:
	BloqueTabla(long tamanoBloque);
	unsigned int getSiguiente(void);
	void setSiguiente(unsigned int siguiente);
	void cargarTabla(array& vec);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual ~BloqueTabla();
};


#endif /* BLOQUETABLA_H_ */

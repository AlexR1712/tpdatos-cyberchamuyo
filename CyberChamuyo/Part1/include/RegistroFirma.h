/*
 * RegistroFirma.h
 *
 *  Created on: Dec 4, 2012
 *      Author: lucasj
 */

#ifndef REGISTROFIRMA_H_
#define REGISTROFIRMA_H_

#include "RegistroVariable.h"
#include "Signature.h"

class RegistroFirma: public RegistroVariable {
private:
	Signature::Signature* dato;
	virtual void print(std::ostream& oss);
	virtual void read(std::istream& oss);
public:
	RegistroFirma(Signature::Signature* dato);
	void obtenerListaFrases(listaFrases& lista);
	RegistroFirma();
	virtual ~RegistroFirma();
	void insertarFrase(unsigned int nFrase);
	void borrarFrase(unsigned int nFrase);
	virtual void serializar(std::ostream& oss);
	virtual void ImprimirATexto(std::ostream& oss);
	virtual void borrarDato();
    virtual unsigned long int getClaveDato(void);
    virtual int getTamanoDato(void);
    friend std::ostream& operator<<(std::ostream& oss,
					  RegistroFirma &reg);
	friend std::istream& operator>>(std::istream& oss,
					  RegistroFirma &reg);

};

#endif /* REGISTROFIRMA_H_ */

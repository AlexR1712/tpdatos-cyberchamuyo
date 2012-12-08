/*
 * SignatureFile.h
 *
 *  Created on: Dec 5, 2012
 *      Author: lucasj
 */

#ifndef SIGNATUREFILE_H_
#define SIGNATUREFILE_H_

#include "ArchivoBloquesFijos.h"
#include "Signature.h"
#include "BloqueFirma.h"
#include <list>

#define TAM_BLOQUE_SIG_FILE 480

namespace Signature {

class SignatureFile {
private:
	ArchivoBloquesFijos archSig;
public:
	SignatureFile(const char* filename);
	bool inicializar(unsigned int N);
	bool insertarFirma(Signature* firma, unsigned int idTerm);
	void insertarFrase(unsigned int nFrase, unsigned int nTermino);
	void borrarFrase(unsigned int nFrase, unsigned int nTermino);
	void getListaFrases(unsigned int nTermino, listaFrases& lista);
	bool insertarTermino(unsigned int nTermino);
	void cargar();
	void clear(void);
	virtual ~SignatureFile();
	friend std::ostream& operator<<(std::ostream& oss,
					  SignatureFile &sigFile);
	friend std::istream& operator>>(std::istream& oss,
					  SignatureFile &sigFile);
};

std::ostream& operator<<(std::ostream& oss, SignatureFile &sigFile);

}
#endif

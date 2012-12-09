/*
 * SignatureFile.cpp
 *
 *  Created on: Dec 5, 2012
 *      Author: lucasj
 */

#include "../include/SignatureFile.h"

namespace Signature {

SignatureFile::SignatureFile(const char* filename):archSig(filename, TAM_BLOQUE_SIG_FILE) {

}

SignatureFile::~SignatureFile() {

}

bool SignatureFile::insertarFirma(Signature* firma, unsigned int idTerm) {
	BloqueFirma bl(this->archSig.getTamanoBloque());
	RegistroFirma* reg = new RegistroFirma(firma);
	bl.addRegistro(reg);
	firma->setClaveDato(idTerm);
	if (this->archSig.Escribir(&bl, firma->getClaveDato()) != RES_OK)
		return false;
	else return true;
}

void SignatureFile::cargar() {

}

void SignatureFile::clear(void) {
	this->archSig.clear();
}

void SignatureFile::borrarFrase(unsigned int nFrase, unsigned int nTermino) {
	/*BloqueFirma bl(this->archSig.getTamanoBloque());
	if (this->archSig.Leer(nTermino, &bl) == RES_OK) {
		RegistroFirma* reg = bl.getRegistro();
		reg->borrarFrase(nFrase);
		bl.addRegistro(reg);
		this->archSig.Escribir(&bl, nTermino);
	}*/
	nTermino--;
	unsigned int corrimiento = 0;
	corrimiento = corrimiento + sizeof(bool);
	corrimiento = corrimiento + sizeof(unsigned int)*2;
	if (nFrase <= this->archSig.getTamanoBloque())
		--nFrase;
		this->archSig.borrarBit(nFrase, nTermino, corrimiento);
}

void SignatureFile::insertarFrase(unsigned int nFrase,  unsigned int nTermino) {
	/*BloqueFirma bl(this->archSig.getTamanoBloque());
	if (this->archSig.Leer(nTermino, &bl) == RES_OK) {
		RegistroFirma* reg = bl.getRegistro();
		reg->insertarFrase(nFrase);
		bl.addRegistro(reg);
		this->archSig.Escribir(&bl, nTermino);
	}*/
	nTermino--;
	unsigned int corrimiento = 0;
	corrimiento = corrimiento + sizeof(bool);
	corrimiento = corrimiento + sizeof(unsigned int)*2;
	if (nFrase <= this->archSig.getTamanoBloque())
		--nFrase;
		this->archSig.insertarBit(nFrase, nTermino, corrimiento);
}

std::ostream& operator<<(std::ostream& oss, SignatureFile &sigFile) {
	oss << sigFile.archSig;
	for (int i = 0; i < sigFile.archSig.getCantidadBloques(); ++i) {
		oss << "***********************" << std::endl;
		oss << "BLOQUE " << i << std::endl;
			BloqueFirma* bl = new BloqueFirma(sigFile.archSig.getTamanoBloque());
			if (sigFile.archSig.Leer(i, bl) == ERR_BLOQUE_LIBRE)
				oss << "BLOQUE LIBRE" << std::endl;
			else bl->ImprimirATexto(oss);
			delete bl;
		}
	return oss;
}

void SignatureFile::getListaFrases(unsigned int nTermino, listaFrases& lista) {
	BloqueFirma bl(this->archSig.getTamanoBloque());
	if (this->archSig.Leer(nTermino - 1, &bl) == RES_OK) {
		bl.obtenerListaFrases(lista);
	}
}

bool SignatureFile::inicializar(unsigned int N) {
	for (unsigned int i = 0; i < N; ++i) {
		BloqueFirma* bl = new BloqueFirma(this->archSig.getTamanoBloque());
		Signature* firma = new Signature;
		RegistroFirma* reg = new RegistroFirma(firma);
		bl->addRegistro(reg);
		firma->setClaveDato(this->archSig.getNuevoId());
		if (this->archSig.Escribir(bl, firma->getClaveDato() - 1) != RES_OK) {
			delete bl;
			return false;
		}
		delete bl;
	}
	return true;
}

bool SignatureFile::insertarTermino(unsigned int nTermino) {
	BloqueFirma* bl = new BloqueFirma(this->archSig.getTamanoBloque());
	Signature* firma = new Signature;
	RegistroFirma* reg = new RegistroFirma(firma);
	bl->addRegistro(reg);
	firma->setClaveDato(nTermino);
	if (this->archSig.Escribir(bl, firma->getClaveDato() - 1) != RES_OK) {
		delete bl;
		return false;
	}
	return true;
}

}


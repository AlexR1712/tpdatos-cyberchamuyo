/*
 * SignaturePortionIndex.h
 *
 *  Created on: Nov 27, 2012
 *      Author: SLMG
 */

#ifndef SIGNATUREPORTIONINDEX_H_
#define SIGNATUREPORTIONINDEX_H
#include <list>
#include "SignatureFile.h"
#include "IndiceArbol.h"
#include "fixedLengthRecordSequentialFile.h"
#include "FixedLengthTRecord.h"
#include "OcurrenceFileRecord.h"
#include "externalSorter.h"
#include "variableLengthRecordSequentialFile.h"

class SignaturePortionIndex {
private:
	Signature::SignatureFile sigFile;
	IndiceArbol* vocabulary;
	// ATRIBUTOS

/*	ArchivoBloquesFijos& fileF;
	ArchivoBloquesFijos& fileTOA;						//  Atributo que maneja el archivo de Terminos por Orden de Aparición.
	ArchivoBloquesFijos& fileOTF;						//  Atributo que maneja el archivo de Ocurrencia de Terminos en Frases donde se guardan el idFrase+idTermino.
	ArbolBp& vocabulario;
	ArchivoBloquesFijos& fileOTFOrdenado;				//  Atributo que maneja el archivo de Ocurrencia de Terminos en Frases Ordenado donde se guardan el idFrase+idTermino ordenado por idTermino.
	unsigned int tamanioIndicePorcionesFirmas;			//  Atributo que contempla el 20% solicitado para el archivo de Indice de Porciones de Firmas.

	// METODOS PRIVADOS

	void cargarArchivosTOA_OTD(ListadoTerminos& listaTerminosRelevantes, unsigned int idFrase);
	ListadoTerminos& validarExistenciaArbolVocabulario(ListadoTerminos& listaTerminosRelevantes);
	//ListadoTerminos& validarStopwords(RegistroArchivoF registroArchivoF);
	void cargarTerminoArchivoOTF(unsigned int idFrase, unsigned int idTermino);
	unsigned int cargarTerminoArchivoTOA(void);
	void aplicarSortExterno();
*/

public:
	SignaturePortionIndex(void);
	virtual ~SignaturePortionIndex();
	void load(FixedLengthRecordSequentialFile<FixedLengthTRecord>* T, std::string ocurrenceFilePath, IndiceArbol* vocabulary);
	std::list<unsigned int> search(std::string term, IndiceArbol* vocabulary);
	friend std::ostream& operator<<(std::ostream& oss, SignaturePortionIndex &sigPortionIndex);
	/*

	//PARTE A

	//Construccion del archivo de Terminos por Orden de Aparicion y del archivo de Ocurrencias de Terminos en Frases.
	void buildFile_TOA_OTF();

	//Construccion del archivo de Terminos por Orden de Aparicion Ordenado.
	void buildFile_OTFO();

	//Construccion del archivo de Indice de Porciones de Firmas.
	void buildFile_IPF();

	//PARTE B

	//Buscar registro en el indice de porciones de firmas
	void busquedaRegistro(unsigned int idTermino, unsigned int idFrase);

	//Consulta de Terminos contenidos en el indice de porciones de firmas
	void busquedaRegistrosListaTerminos(ListadoTerminos consulta, const char *nameArchivoTextoResultante);

	//Dar de alta el registro (idFrase, idTermino) al archivo de Ocurrencias de Terminos en Frases conocido como archivo P.
	void altaRegistro(unsigned int idTermino, unsigned int idFrase);

	//Dar de baja el registro (idFrase, idTermino) al archivo de Ocurrencias de Terminos en Frases conocido como archivo P.
	void bajaRegistro(unsigned int idTermino, unsigned int idFrase);

	//Modificar el registro (idFrase, idTermino) al archivo de Ocurrencias de Terminos en Frases conocido como archivo P.
	void modificarRegistro(unsigned int idTermino, unsigned int idFrase, unsigned int idTerminoActual, unsigned int idFraseActual);
	ArchivoBloquesFijos& getFileOtf() const;
	ArchivoBloquesFijos& getFileOtfOrdenado() const;
	ArchivoBloquesFijos& getFileToa() const;
	ArbolBp getVocabulario() const;
	void setVocabulario(ArbolBp& vocabulario);
	unsigned int getTamanioIndicePorcionesFirmas() const;
	void setTamanioIndicePorcionesFirmas(
	unsigned int tamanioIndicePorcionesFirmas);
*/
}
;

std::ostream& operator<<(std::ostream& oss, SignaturePortionIndex &sigPortionIndex);

#endif /* SIGNATUREPORTIONINDEX_H_*/

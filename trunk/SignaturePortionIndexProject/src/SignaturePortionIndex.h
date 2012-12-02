/*
 * SignaturePortionIndex.h
 *
 *  Created on: Nov 27, 2012
 *      Author: SLMG
 */

#ifndef SIGNATUREPORTIONINDEX_H_
#define SIGNATUREPORTIONINDEX_H
#include <list>


class SignaturePortionIndex {
private:
	// ATRIBUTOS

	ArchivoBloquesFijos fileF;
	ArchivoBloquesFijos fileTOA;						//  Atributo que maneja el archivo de Terminos por Orden de Aparición.
	ArchivoBloquesFijos fileOTF;						//  Atributo que maneja el archivo de Ocurrencia de Terminos en Frases donde se guardan el idFrase+idTermino.
	ArbolBp vocabulario;
	ArchivoBloquesFijos fileOTFOrdenado;				//  Atributo que maneja el archivo de Ocurrencia de Terminos en Frases Ordenado donde se guardan el idFrase+idTermino ordenado por idTermino.
	unsigned int tamanioIndicePorcionesFirmas;			//  Atributo que contempla el 20% solicitado para el archivo de Indice de Porciones de Firmas.

	// METODOS PRIVADOS

	void cargarArchivosTOA_OTD(List listaTerminosRelevantes, unsigned int idFrase);
	List validarExistenciaArbolVocabulario(List listaTerminosRelevantes);
	List validarStopwords(RegistroArchivoF registroArchivoF);
	void cargarTerminoArchivoOTF(unsigned int idFrase, unsigned int idTermino);
	unsigned int SignaturePortionIndex::cargarTerminoArchivoTOA();
	void aplicarSortExterno();


public:
	SignaturePortionIndex(const char *nameArchivoF, const char *nameArchivoTOA, const char *nameArchivoOTF, const char *nameArchivoOTFO);
	virtual ~SignaturePortionIndex();


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
	ArchivoBloquesFijos getFileOtf() const;
	ArchivoBloquesFijos getFileOtfOrdenado() const;
	ArchivoBloquesFijos getFileToa() const;
	ArbolBp getVocabulario() const;
	void setVocabulario(ArbolBp vocabulario);
	unsigned int getTamanioIndicePorcionesFirmas() const;
	void setTamanioIndicePorcionesFirmas(
	unsigned int tamanioIndicePorcionesFirmas);

}
;

#endif /* SIGNATUREPORTIONINDEX_H_ */

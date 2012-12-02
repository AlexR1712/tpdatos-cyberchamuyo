/*
 * SignaturePortionIndex.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: SLMG
 */

#include "SignaturePortionIndex.h"
#include <list>


SignaturePortionIndex::SignaturePortionIndex(const char *nameArchivoF, const char *nameArchivoTOA, const char *nameArchivoOTF, const char *nameArchivoOTFO) {
	this->fileF = abrirArchivo(nameArchivoF);               // Se asocia el archivo F ya existente al atributo fileF
	this->fileTOA = Inicializar(nameArchivoTOA);            // Se crea el archivo nameArchivoTOA y se lo asocia al fileTOA
	this->fileOTF = Inicializar(nameArchivoOTF);            // Se crea el archivo nameArchivoOTF y se lo asocia al fileOTF
	this->fileOTFOrdenado = Inicializar(nameArchivoOTFO);   // Se crea el archivo nameArchivoOTFO y se lo asocia al fileOTFOrdenado
}

SignaturePortionIndex::~SignaturePortionIndex() {
	// TODO Auto-generated destructor stub
}


// METODOS PRIVADOS

unsigned int SignaturePortionIndex::cargarTerminoArchivoTOA(){
	unsigned int idTermino;
	// Acá se usa el atributo fileTOA para serializar el nuevo Termino relevante en el archivo TOA y se retorna el idTermino.
	return idTermino;
}

void SignaturePortionIndex::cargarTerminoArchivoOTF(unsigned int idFrase, unsigned int idTermino){
	// Acá se usa el atributo fileOTF para serializar el registro (idFrase, idTermino) en el archivo OTF.
}

List SignaturePortionIndex::validarStopwords(RegistroArchivo registroArchivoF){
	List listaTerminosRelevantes;
	return listaTerminosRelevantes;
}

List SignaturePortionIndex::validarExistenciaArbolVocabulario(List terminosRelevantes){
	bool existenciaVocabulario;
	List terminosRelevantesInexistentesVocabulario;

	vocabulario = this->getVocabulario(); // Devuelve la referencia al arbol de vocabulario.

	while not finalLista(terminosRelevantes) {
		terminoRelevante = extraerTerminoListaTerminosRelevantes(terminosRelevantes);
		existenciaVocabulario = vocabulario.buscar(terminoRelevante); // Se busca en el arbol de vocabulario por termino relevante. ESTO HAY QUE ADAPTARLO AL MÉTODO USADO EN EL ARBOL.
		if (not (existenciaVocabulario)){
			terminosRelevantesInexistentesVocabulario->Add; //SE USA ALGUNA PRIMITIVA PARA AGREGAR A UNA LISTA NUEVA EL TERMINO RELEVANTE NO EXISTENTE EN EL VOCABULARIO.
		}
		terminosRelevantes->MoverSiguiente;
	}

	return terminosRelevantesInexistentesVocabulario;
}

// Se guardan en los archivos TOA y OTD.
void SignaturePortionIndex::cargarArchivosTOA_OTD(List terminosRelevantesInexistentesVocabulario, unsigned int idFrase){
	std::string terminoRelevante;
	unsigned int idTermino;

	while not finalLista(terminosRelevantesInexistentesVocabulario) {
		terminoRelevante = extraerTerminoListaTerminosRelevantes(terminosRelevantesInexistentesVocabulario);
		idTermino = cargarTerminoArchivoTOA(); // Se guarda al final del archivo de Terminos por Orden de Aparicion el termino relevante y devuelve el idTermino asociado a su posicion.
		cargarTerminoArchivoOTF(idFrase, idTermino); // Se guarda en el archivo de Ocurrencia de Terminos en Frases los datos (idFrase, idTermino).
		terminosRelevantesInexistentesVocabulario->MoverSiguiente;
	}
}

// Se la puede reemplazar o adaptar por el implementado aparte.
void SignaturePortionIndex::aplicarSortExterno(){
	//Code...
}


//PARTE A

//Construccion del archivo de Terminos por Orden de Aparicion y del archivo de Ocurrencias de Terminos en Frases.
void SignaturePortionIndex::buildFile_TOA_OTF(){
	RegistroArchivoF registroArchivoF;
	List terminosRelevantes;
	List terminosRelevantesInexistentesVocabulario;
	unsigned int idFrase;

	while not finalArchivo(this->fileF) {
		registroArchivoF = extraerBloqueArchivo(this->fileF);
		terminosRelevantes = validarStopwords(registroArchivoF); // Se filtran los stopwords para guardarlos en una lista de terminos relevantes.
		terminosRelevantesInexistentesVocabulario = validarExistenciaArbolVocabulario(terminosRelevantes); // Verifica la existencia de estos posibles terminos relevantes nuevos en el arbol de vocabulario
		if (not (terminosRelevantesInexistentesVocabulario->vacia)) {
			idFrase = registroArchivoF->getIdFrase;
			cargarArchivosTOA_OTD(terminosRelevantesInexistentesVocabulario, idFrase); // Se guardan en archivos TOA y OTD.
		}
	}
}

//Construccion del archivo de Terminos por Orden de Aparicion Ordenado.
void SignaturePortionIndex::buildFile_OTFO(){

	aplicarSortExterno(); // Se aplica Sort Externo mediante el uso del atributo que maneja el archivo de Ocurrencias de Terminos en Frases.

}


//PARTE B

//Buscar registro en el indice de porciones de firmas
void SignaturePortionIndex::busquedaRegistro(unsigned int idTermino, unsigned int idFrase){

}

//Consulta de Terminos contenidos en el indice de porciones de firmas
void SignaturePortionIndex::busquedaRegistrosListaTerminos(ListadoTerminos consulta, const char *nameArchivoTextoResultante){

}

//Dar de alta el registro (idFrase, idTermino) al archivo de Ocurrencias de Terminos en Frases conocido como archivo P.
void SignaturePortionIndex::altaRegistro(unsigned int idTermino, unsigned int idFrase){

}

//Dar de baja el registro (idFrase, idTermino) al archivo de Ocurrencias de Terminos en Frases conocido como archivo P.
void SignaturePortionIndex::bajaRegistro(unsigned int idTermino, unsigned int idFrase){

}

ArchivoBloquesFijos SignaturePortionIndex::getFileOtf() const {
	return fileOTF;
}

ArchivoBloquesFijos SignaturePortionIndex::getFileOtfOrdenado() const {
	return fileOTFOrdenado;
}

ArchivoBloquesFijos SignaturePortionIndex::getFileToa() const {
	return fileTOA;
}

ArbolBp SignaturePortionIndex::getVocabulario() const {
	return vocabulario;
}

unsigned int SignaturePortionIndex::getTamanioIndicePorcionesFirmas() const {
	return tamanioIndicePorcionesFirmas;
}

void SignaturePortionIndex::setTamanioIndicePorcionesFirmas(
		unsigned int tamanioIndicePorcionesFirmas) {
	this->tamanioIndicePorcionesFirmas = tamanioIndicePorcionesFirmas;
}

void SignaturePortionIndex::setVocabulario(ArbolBp vocabulario) {
	this->vocabulario = vocabulario;
}

//Modificar el registro (idFrase, idTermino) al archivo de Ocurrencias de Terminos en Frases conocido como archivo P.
void SignaturePortionIndex::modificarRegistro(unsigned int idTermino, unsigned int idFrase, unsigned int idTerminoActual, unsigned int idFraseActual){

}

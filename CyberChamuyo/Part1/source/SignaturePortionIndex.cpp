/*
 * SignaturePortionIndex.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: SLMG
 */

#include "../include/SignaturePortionIndex.h"

SignaturePortionIndex::SignaturePortionIndex(void):sigFile("bin/SignatureFile.bin") {
	vocabulary = NULL;
}

SignaturePortionIndex::~SignaturePortionIndex() {

}

void SignaturePortionIndex::load(FixedLengthRecordSequentialFile<FixedLengthTRecord>* T, std::string ocurrenceFilePath, IndiceArbol* vocabulary) {
	//ExternalSorter<VariableLengthRecordSequentialFile<OcurrenceFileRecord>,OcurrenceFileRecord> sorter(5,false);
	//std::string orderedOcurrenceFilePath = "orderedOcurrenceFile.bin";
	//sorter.sort(ocurrenceFilePath,orderedOcurrenceFilePath,true);
	this->sigFile.inicializar(T->getLastRecordPosition());
	VariableLengthRecordSequentialFile<OcurrenceFileRecord> ocurrenceFile;
	ocurrenceFile.open(ocurrenceFilePath);
	OcurrenceFileRecord ocurrenceRecord = ocurrenceFile.getNextRecord();
	while(!ocurrenceFile.endOfFile()) {
		FixedLengthTRecord termRecord = T->getRecord(ocurrenceRecord.getTermId());
		std::string term = termRecord.getTerm();
		std::string termSearch = "mundo";
		if (term == termSearch)
			std::cout << "hola";
		unsigned int previousTerm = ocurrenceRecord.getTermId();
		Signature::Signature* firma = new Signature::Signature;
		while(ocurrenceRecord.getTermId() == previousTerm) {
			unsigned int docId = ocurrenceRecord.getDocId();
			/*if (docId == 69)
				std::cout << "hola";*/
			firma->setBit(docId);
			ocurrenceRecord = ocurrenceFile.getNextRecord();
		}
		if(!ocurrenceFile.endOfFile())
			this->sigFile.insertarFirma(firma, previousTerm + 1);
	}
}

std::list<unsigned int> SignaturePortionIndex::search(std::string term, IndiceArbol* vocabulary) {
	RegistroArbol reg(vocabulary->textSearch(term));
	std::list<unsigned int> res;
	unsigned int termId = reg.getTermId();
	if(termId == 0) {
		res.push_back(0);
		return res;
	}
	this->sigFile.getListaFrases(termId, res);
	return res;
}

void SignaturePortionIndex::addTerm(unsigned int idTerm, unsigned int docId) {
	this->sigFile.insertarTermino(idTerm);
	Signature::Signature* firma = new Signature::Signature;
	firma->setBit(docId);
	this->sigFile.insertarFirma(firma, idTerm);
}

void SignaturePortionIndex::addDocToTerm(std::string term, unsigned int docId, IndiceArbol* vocabulary) {
	RegistroArbol reg(vocabulary->textSearch(term));
	unsigned int termId = reg.getTermId();
	this->sigFile.insertarFrase(docId, termId);
}

std::ostream& operator<<(std::ostream& oss, SignaturePortionIndex &sigPortionIndex) {
	oss << sigPortionIndex.sigFile;
	return oss;
}

/*
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

ListadoTerminos& validarExistenciaArbolVocabulario(ListadoTerminos& listaTerminosRelevantes) {
	bool existenciaVocabulario;
	ListadoTerminos terminosRelevantesInexistentesVocabulario;

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

ListadoTerminos SignaturePortionIndex::validarExistenciaArbolVocabulario(ListadoTerminos terminosRelevantes){

}

// Se guardan en los archivos TOA y OTD.
void SignaturePortionIndex::cargarArchivosTOA_OTD(ListadoTerminos terminosRelevantesInexistentesVocabulario, unsigned int idFrase){
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
	ListadoTerminos terminosRelevantes;
	ListadoTerminos terminosRelevantesInexistentesVocabulario;
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

ArchivoBloquesFijos& SignaturePortionIndex::getFileOtf() const {
	return fileOTF;
}

ArchivoBloquesFijos& SignaturePortionIndex::getFileOtfOrdenado() const {
	return fileOTFOrdenado;
}

ArchivoBloquesFijos& SignaturePortionIndex::getFileToa() const {
	return fileTOA;
}

ArbolBp& SignaturePortionIndex::getVocabulario() const {
	return vocabulario;
}

unsigned int SignaturePortionIndex::getTamanioIndicePorcionesFirmas() const {
	return tamanioIndicePorcionesFirmas;
}

void SignaturePortionIndex::setTamanioIndicePorcionesFirmas(
		unsigned int tamanioIndicePorcionesFirmas) {
	this->tamanioIndicePorcionesFirmas = tamanioIndicePorcionesFirmas;
}

void SignaturePortionIndex::setVocabulario(ArbolBp& vocabulario) {
	this->vocabulario = vocabulario;
}

//Modificar el registro (idFrase, idTermino) al archivo de Ocurrencias de Terminos en Frases conocido como archivo P.
void SignaturePortionIndex::modificarRegistro(unsigned int idTermino, unsigned int idFrase, unsigned int idTerminoActual, unsigned int idFraseActual){

}
*/

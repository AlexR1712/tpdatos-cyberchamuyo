/*
 * MapaDeTerminos.cpp
 *
 *  Created on: 21/11/2012
 *      Author: sebastian
 */

#include "../include/MapaDeTerminos.h"

MapaDeTerminos::MapaDeTerminos(long termCount) {
}
/*
void MapaDeTerminos::cargar(std::string path) {
	BinaryInputSequentialFile<BinaryDictionaryRecord<true> > arch_ocurrencias;
	while(!arch_ocurrencias.endOfFile()) {
		int currentDoc;
		BinaryDictionaryRecord<true> record = arch_ocurrencias.getRecord();
		int termId = record.getTermId();
		int docId = record.getDocId();

		BinaryArray portion(docCount);

	}
}

void MapaDeTerminos::search(std::vector<long> terms) {
	BinaryArray res(docCount);
	res.set(0, res.size(), 1);
	for(int i = 0; i < terms.size(); ++i) {
		char* buffer;
		map_file.read(buffer);
		BinaryArray doc_line(buffer);
		res = res & doc_line;
	}
	//	obtener los textos del hash usando res
	//	escribir los textos
}

void MapaDeTerminos::update() {

}
*/
MapaDeTerminos::~MapaDeTerminos() {
	// TODO Auto-generated destructor stub
}

#ifndef EXTERNALSORTER_H_
#define EXTERNALSORTER_H_

#include <string>
#include "heap.h"
#include "binaryInputSequentialFile.h"
#include "binaryOutputSequentialFile.h"
#include "binaryDictionaryRecord.h"
#include "textOutputSequentialFile.h"
#include "logRecord.h"

#ifndef TEMP_FOLDER_NAME_PREFIX
#define TEMP_FOLDER_NAME_PREFIX "particiones"
#endif /*TEMP_FOLDER_NAME_PREFIX*/

#ifndef PHASE_FOLDER_NAME_PREFIX
#define PHASE_FOLDER_NAME_PREFIX "Etapa"
#endif /*PHASE_FOLDER_NAME_PREFIX*/

#ifndef OUTPUTFILES_FOLDER_NAME
#define OUTPUTFILES_FOLDER_NAME "outputFiles"
#endif /*OUTPUTFILES_FOLDER_NAME*/

#ifndef FREEZE_FILE_NAME
#define FREEZE_FILE_NAME "freezeFile.bin"
#endif /*FREEZE_FILE_NAME*/

#ifndef ORDERED_FILE_PART_PREFIX
#define ORDERED_FILE_PART_PREFIX "orderedFile"
#endif /*ORDERED_FILE_PART_PREFIX*/

#ifndef LOG_FILE_NAME
#define LOG_FILE_NAME "estadisticas.txt"
#endif /*LOG_FILE_NAME*/

//Clase para realizar ordenamiento externo de archivos con registros de diccionario.
class ExternalSorter {
private:
	//Monticulo para realizar el ordenamiento
	Heap<BinaryDictionaryRecord<true> > sortBuffer;

	//Indica si se debe guardar el ID en el archivo final ordenado.
	bool showId;

	//Tamaño del buffer de los archivos.
	unsigned int filesBufferSize;

	//Nombre de la carpeta temporal en la que se guardarán los archivos de trabajo.
	std::string tempFolderName;

	//Log donde se guardaran los datos del ordenamiento.
	TextOutputSequentialFile<LogRecord> log;

	Heap<BinaryDictionaryRecord<true> >& getSortBuffer();

	bool isShowId() const;

	unsigned int getFilesBufferSize() const;

	std::string getTempFolderName() const;

	TextOutputSequentialFile<LogRecord>& getLog();

	//Metodo para llenar el monticulo desde un archivo
	void createSortBuffer(BinaryInputSequentialFile<BinaryDictionaryRecord<true> >& inputFile);

	//Metodo para escribir en un archivo el monticulo
	void flushSortBuffer(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& outputFile);

	//Metodo para armar el monticulo con los registros congelados.
	void unfreeze(BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& freezeFile);

	//Metodo para cargar los archivos de trabajo a unir.
	void loadMergeBuffer(std::vector<BinaryInputSequentialFile<BinaryDictionaryRecord<true> >*>& inputFiles, std::string folderName, unsigned int inputFileLevelCounter, unsigned int& inputFileFileCounter);

	//Metodo para generar el nombre de la carpeta temporal segun la fecha y hora actual
	std::string generateTempFolderName();

	//Metodo para borrar los archivos de trabajo creados en las sucesivas etapas de ordenamiento.
	void clearPhase(std::string parentFolderName, unsigned int level);

	//Metodo para borrar la carpeta temporal de archivos de trabajo.
	void clearTemp();

	//Metodo para crear las particiones ordenadas.
	void createOrderedParts(std::string inputFilepath);

	//Metodo para unir las particiones ordenadas.
	void merge(std::string outputFilepath);

public:
	//Constructor
	ExternalSorter(unsigned int filesBufferSize, bool showId);

	//Metodo para ordenar un archivo desordenado.
	void sort(std::string inputFilepath, std::string outputFilepath, bool leaveTraces);

	//Destructor
	~ExternalSorter();
};

#endif /* EXTERNALSORTER_H_ */

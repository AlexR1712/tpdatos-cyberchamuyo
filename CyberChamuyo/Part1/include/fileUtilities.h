#ifndef FILEUTILITIES_H_
#define FILEUTILITIES_H_

#include <sys/stat.h>
#include <string>

namespace FileUtilities {

//Metodo para crear una carpeta.
void createFolder(std::string directoryName);

//Metodo para borrar una carpeta.
void deleteFolder(std::string directoryName);

//Metodo para borrar un archivo.
void deleteFile(std::string fileName);

//Chequea si existe un directorio
bool directoryExists(std::string path);

}

#endif /* FILEUTILITIES_H_ */

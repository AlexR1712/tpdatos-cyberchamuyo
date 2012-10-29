#ifndef FILEUTILITIES_H_
#define FILEUTILITIES_H_

#define LINUX

#ifdef WINDOWS
#include "windows.h"
#endif

#ifdef LINUX
#include <sys/stat.h>
#endif

#include <string>

namespace FileUtilities {

//Metodo para crear una carpeta.
void createFolder(std::string directoryName);

//Metodo para borrar una carpeta.
void deleteFolder(std::string directoryName);

//Metodo para borrar un archivo.
void deleteFile(std::string fileName);

}

#endif /* FILEUTILITIES_H_ */

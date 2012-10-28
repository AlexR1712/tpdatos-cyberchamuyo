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

void createFolder(std::string directoryName);

void deleteFolder(std::string directoryName);

void deleteFile(std::string fileName);

}

#endif /* FILEUTILITIES_H_ */

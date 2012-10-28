#include "fileUtilities.h"

namespace FileUtilities {

void createFolder(std::string directoryName) {
	#ifdef WINDOWS
	CreateDirectory(directoryName.c_str(),NULL);
	#endif
	#ifdef LINUX
	mkdir(directoryName.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	#endif
}

void deleteFolder(std::string directoryName) {
	#ifdef WINDOWS
	RemoveDirectory(directoryName.c_str());
	#endif
	#ifdef LINUX
	rmdir(directoryName.c_str());
	#endif
}

void deleteFile(std::string fileName) {
	#ifdef WINDOWS
	DeleteFile(fileName.c_str());
	#endif
	#ifdef LINUX
	unlink(fileName.c_str());
	#endif
}


}

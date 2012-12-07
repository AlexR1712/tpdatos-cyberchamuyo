#include "../include/fileUtilities.h"

namespace FileUtilities {

void createFolder(std::string directoryName) {
	mkdir(directoryName.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void deleteFolder(std::string directoryName) {
	rmdir(directoryName.c_str());
}

void deleteFile(std::string fileName) {
	unlink(fileName.c_str());
}

bool directoryExists(std::string path) {
	struct stat sb;	
	if(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
		return true;
	return false;
}

std::ifstream::pos_type fileSize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    return in.tellg();
}

}

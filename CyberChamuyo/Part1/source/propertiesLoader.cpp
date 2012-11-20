#include "../include/propertiesLoader.h"

#include <iostream>

#include "../include/textInputSequentialFile.h"
#include "../include/textRecord.h"
#include "../include/stringUtilities.h"

PropertiesLoader::PropertiesLoader(std::string propertiesFilePath) {
	loadProperties(propertiesFilePath);
}

std::unordered_map<std::string,std::string>& PropertiesLoader::getProperties() {
	return this->properties;
}

void PropertiesLoader::loadProperties(std::string propertiesFilePath) {
	//TODO buffer por defecto debe ser configurable para el archivo
	TextInputSequentialFile<TextRecord> propertiesFile(propertiesFilePath,10);
	std::vector<std::string> propertiesContents;

	if (propertiesFile.exists()) {
		while (!propertiesFile.endOfFile()) {
			StringUtilities::splitString(propertiesFile.getRecord().getData(),propertiesContents,'=');
			this->getProperties().insert(std::pair<std::string,std::string>(propertiesContents[0],propertiesContents[1]));
		}
	} else {
		std::cout << TEXT_PROPERTIES_FILE_NOT_FOUND(propertiesFilePath) << std::endl;
		throw(1);
	}
}

std::string PropertiesLoader::getPropertyValue(const std::string propertyName) {
	std::string propertyValue;
	std::unordered_map<std::string,std::string>::iterator it = this->getProperties().find(propertyName);

	if (it != this->getProperties().end())
		propertyValue = it->second;

	return propertyValue;
}

PropertiesLoader::~PropertiesLoader() {
}

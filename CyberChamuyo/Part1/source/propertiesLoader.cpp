#include "../include/propertiesLoader.h"

#include <iostream>

#include "../include/textFile.h"
#include "../include/textRecord.h"
#include "../include/stringUtilities.h"

PropertiesLoader::PropertiesLoader(std::string propertiesFilePath) {
	loadProperties(propertiesFilePath);
}

std::unordered_map<std::string,std::string>& PropertiesLoader::getProperties() {
	return this->properties;
}

void PropertiesLoader::loadProperties(std::string propertiesFilePath) {
	TextFile<TextRecord> propertiesFile;
	TextRecord record;
//	std::ifstream propertiesFile;
	std::vector<std::string> propertiesContents;
//	std::string propertyLine;

	propertiesFile.open(propertiesFilePath);
	if (propertiesFile.isFileExists()) {
//		std::getline(propertiesFile,propertyLine);
		while (!propertiesFile.endOfFile()) {
			record = propertiesFile.getNextRecord();
			StringUtilities::splitString(record.getData(),propertiesContents,'=');
			this->getProperties().insert(std::pair<std::string,std::string>(propertiesContents[0],propertiesContents[1]));
//			std::getline(propertiesFile,propertyLine);
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

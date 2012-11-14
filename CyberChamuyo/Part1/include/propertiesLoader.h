#ifndef PROPERTIESLOADER_H_
#define PROPERTIESLOADER_H_

#include <string>
#include <unordered_map>

#ifndef TEXT_PROPERTIES_FILE_NOT_FOUND
#define TEXT_PROPERTIES_FILE_NOT_FOUND(propertiesFilePath) "El archivo de propiedades \"" + propertiesFilePath + "\" no existe"
#endif /*TEXT_PROPERTIES_FILE_NOT_FOUND*/

//Clase cuya función es cargar propiedades desde un archivo de propiedades.
class PropertiesLoader {
private:
	//Mapa de propiedades.
	std::unordered_map<std::string,std::string> properties;

	std::unordered_map<std::string,std::string>& getProperties();

	//Metodo para cargar las propiedades desde un archivo.
	void loadProperties(std::string propertiesFilePath);

public:
	//Constructor
	PropertiesLoader(std::string propertiesFilePath);

	//Metodo para obtener el valor de una propiedad en base a su nombre.
	std::string getPropertyValue(const std::string propertyName);

	//Destructor
	~PropertiesLoader();
};


#endif /* PROPERTIESLOADER_H_ */

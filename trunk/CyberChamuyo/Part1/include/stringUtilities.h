#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include <string>
#include <vector>


namespace StringUtilities {

//Metodo para quitar el \r del final de las l�neas.
void sacarR(std::string& s);

//Metodo para quitar los \n del final de las lineas.
void sacarN(std::string& s);

//Metodo para dividir un string seg�n un separador indicado.
void splitString(std::string string, std::vector<std::string>& splittedString, char delimiter);

//Indica si el string es numerico.
bool isNumeric(std::string string);

//Metodo para rellenar a izquierda con el caracter indicado hasta la longitud indicada.
std::string padLeft(std::string string, char padWith, unsigned int padTo);

//Metodo para rellenar a derecha con el caracter indicado hasta la longitud indicada.
std::string padRight(std::string string, char padWith, unsigned int padTo);

//Metodo para convertir un string a int.
int stringToInt (const std::string Text );

//Metodo para convertir un int a string.
std::string intToString(int i);

//Metodo para convertir un float a string.
std::string floatToString(float f);

//Metodo para convertir un string a wstring.
std::wstring stringToWstring(std::string string);

//Metodo para remover los espacios en blanco al comienzo y al final del string.
std::string trim(std::string string);

//Metodo para remover signos de puntuacion y de expresion en una linea
void quitarPuntuacion(std::string& s);

}

#endif /* STRINGUTILITIES_H_ */

#include "../include/DispersionEx.h"
#include "../include/Frase.h"
#include "../include/RegistroDato.h"
/*
void cargar(std::string valor, Hash::DispersionEx& disp, std::ifstream& entradaTexto) {
	getline(entradaTexto, valor);
	while (!entradaTexto.eof()) {
		unsigned long int num = stoi(valor);
		std::string autor;
		getline(entradaTexto, autor);
		std::string frase;
		getline(entradaTexto, frase);
		getline(entradaTexto, valor);
		Data::Frase* datoInsertar = new Data::Frase(autor, frase, num);
		Hash::RegistroDato* reg = new Hash::RegistroDato(datoInsertar);
		disp.insertarRegistro(reg, num);
	}
}

int main(void) {
	std::string valor;
	Hash::DispersionEx disp("archDisp.bin");
	//std::ifstream entradaTexto("Frases_Celebres2.csv");
	disp.cargarFrases("inputFiles/Frases_Celebres.csv");
	/*std::string linea;
	getline(entradaTexto, linea);
	while(!entradaTexto.eof()) {
		disp.insert(linea);
		getline(entradaTexto, linea);

	}
	entradaTexto.close();*/
	/*disp.borrarRegistro(1);
	disp.borrarRegistro(5);
	disp.borrarRegistro(9);
	disp.borrarRegistro(13);
	disp.borrarRegistro(17);*/
/*
std::ofstream salidaTexto("archDisp.txt");
	salidaTexto << disp;
	salidaTexto.close();
	//disp.clear();
	return 0;
}
*/

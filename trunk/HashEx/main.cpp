#include "DispersionEx.h"
#include "Frase.h"
#include "RegistroDato.h"

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
		RegistroVariable* reg = new Hash::RegistroDato(datoInsertar);
		disp.insertarRegistro(reg, num);
	}
}

int main(void) {
	std::string valor;
	Hash::DispersionEx disp("arch.bin");
	/*std::ifstream entradaTexto("Frases_Celebres.csv");
	//disp.cargarFrases("Frases_Celebres.csv");
	std::string linea;
	getline(entradaTexto, linea);
	while(!entradaTexto.eof()) {
		disp.insert(linea);
		getline(entradaTexto, linea);

	}
	entradaTexto.close();
	//disp.borrarRegistro(234);
	std::ofstream salidaTexto("arch.txt");
	salidaTexto << disp;
	salidaTexto.close();*/
	disp.clear();
	return 0;
}


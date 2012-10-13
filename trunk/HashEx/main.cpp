#include "DispersionEx.h"


int main(void) {
	Hash::DispersionEx disp("arch.bin");
	//disp.CargarFrases("Frases_Celebres.csv");
	std::ofstream salidaTexto("arch.txt");
	salidaTexto << disp;
	salidaTexto.close();

	return 0;
}

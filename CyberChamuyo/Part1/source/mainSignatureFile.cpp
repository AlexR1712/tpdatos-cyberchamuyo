/*#include "../include/SignatureFile.h"
#define N 20

int main(void) {
	Signature::SignatureFile sigFile("SignatureFile.bin");
	//Signature::Signature* firma = new Signature::Signature;
	for (unsigned int i = 15; i < N; ++i) {
				firma->setBit(i + 2);
		//firma->setBit(34);
	}
	//sigFile.insertarFirma(firma);
	//sigFile.borrarFrase(12, 0);
	//sigFile.borrarFrase(12, 0);
	/*listaFrases lista;
	sigFile.getListaFrases(1, lista);
	listaFrases::iterator it;
	for (it = lista.begin(); it != lista.end(); ++it)
		std::cout << *it;
	sigFile.insertarFrase(22, 1);
	std::ofstream arch("archSig.text");
	arch << sigFile;
	/*std::ifstream arch("archSig.bin");
	arch >> firma;
	return 0;
}*/

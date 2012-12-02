/*#include "../include/ListaInvertida.h"
#include "../include/InvertedListFile.h"
#include <iostream>
#define N 8

int main() {
	invertedList::InvertedListFile file("arch.bin");
	invertedList::ListaInvertida* lista = new invertedList::ListaInvertida;

	for (unsigned int i = 2; i < N; ++i) {
		lista->insertar(i);
	}
	lista->setId(567);
	file.insertarLista(lista);
	//file.actualizarLista(vec, 0);
	/*invertedList::ListaInvertida* lista = file.getLista(0);
	lista->Imprimir(std::cout);
	delete lista;
	std::ofstream archText("arch.txt");
	archText << file;
	archText.close();
	return 0;
}*/


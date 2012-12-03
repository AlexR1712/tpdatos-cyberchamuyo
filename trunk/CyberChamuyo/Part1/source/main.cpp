/*#include "../include/ListaInvertida.h"
#include "../include/InvertedListFile.h"
#include <iostream>
#define N 12

int main() {
	invertedList::InvertedListFile file("arch.bin");
	invertedList::ListaInvertida* lista = new invertedList::ListaInvertida;

	for (unsigned int i = 8; i < N; ++i) {
		lista->insertar(i);
	}
	file.insertarLista(lista);
	//file.actualizarLista(vec, 0);
	invertedList::ListaInvertida* lista = file.getLista(0);
	lista->Imprimir(std::cout);
	delete lista;
	std::ofstream archText("arch.txt");
	archText << file;
	archText.close();
	return 0;
}*/


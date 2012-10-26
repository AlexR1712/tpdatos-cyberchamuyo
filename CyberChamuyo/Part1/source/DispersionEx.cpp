/*
 * DispersionEx.cpp
 *
 *  Created on: Sep 15, 2012
 *      Author: lucasj
 */

#include "../include/DispersionEx.h"

namespace Hash {

// FUNCIONAMIENTO CONSTRUCTOR DE DISPERSION EX:
// Crea el archivo de bloques fijos y la tabla. Si el objeto
// fué creado por primera vez crea un bloque tabla nuevo y un bloque
// dato vacio.

DispersionEx::DispersionEx(const char* archDir) :
		arch_disp(archDir, TAM_BLOQUE),tabla(arch_disp) {
	if (this->arch_disp.getCantidadBloques() == 0)
		this->tabla.GuardarTablaInicial();
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	if (this->arch_disp.Leer(1, &bl) == ERR_BLOQUE_INEXISTENTE)
		crearNuevoBloque(1, this->tabla.getSize());
	this->numRandom = 1;
}

// FUNCIONAMIENTO CLEAR
// Borra el archivo de bloques fijos.

void DispersionEx::clear(void) {
	this->arch_disp.clear();
}

// FUNCIONAMIENTO CARGAR FRASES
// Carga las frases desde un archivo de frases.

void DispersionEx::cargarFrases(const char* archFrases) {
	std::string linea;
	std::ifstream entradaTexto(archFrases);
	getline(entradaTexto, linea);
	unsigned int num = 1;
	while(!entradaTexto.eof()) {
		int posActual = linea.find("\t");
		int posAnterior = 0;
		std::string autor = linea.substr(posAnterior, posActual);
		obtenerSiguientePosicion(posAnterior, posActual, linea);
		std::string nombre = linea.substr(posAnterior + 1, posActual - posAnterior - 1);
		autor.append(" ");
		autor.append(nombre);
		obtenerSiguientePosicion(posAnterior, posActual, linea);
		std::string frase = linea.substr(posAnterior + 1, posActual - posAnterior - 1);
		Data::Frase* datoInsertar = new Data::Frase(autor, frase, num);
		RegistroVariable* reg = new Hash::RegistroDato(datoInsertar);
		this->insertarRegistro(reg, num);
		getline(entradaTexto, linea);
		++num;
	}
	entradaTexto.close();
}

// FUNCIONAMIENTO INSERT
// Inserta una frase desde un string.

void DispersionEx::insert(std::string& phrase) {
	int posActual = phrase.find("\t");
	int posAnterior = 0;
	std::string autor = phrase.substr(posAnterior, posActual);
	obtenerSiguientePosicion(posAnterior, posActual, phrase);
	std::string nombre = phrase.substr(posAnterior + 1, posActual - posAnterior - 1);
	autor.append(" ");
	autor.append(nombre);
	obtenerSiguientePosicion(posAnterior, posActual, phrase);
	std::string frase = phrase.substr(posAnterior + 1, posActual - posAnterior - 1);
	Data::Frase* datoInsertar = new Data::Frase(autor, frase, this->numRandom);
	RegistroVariable* reg = new Hash::RegistroDato(datoInsertar);
	this->insertarRegistro(reg, this->numRandom);
	++this->numRandom;
}

// FUNCIONAMIENTO CREAR NUEVO BLOQUE
// Crea un nuevo bloque.

void DispersionEx::crearNuevoBloque(int nuevoBloque, unsigned int td) {
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	bl.setTd(td);
	this->arch_disp.Escribir(&bl, nuevoBloque);
}

// FUNCIONAMIENTO ACTUALIZAR TABLA ALTA
// Actualiza la tabla cuando se realiza un alta. Se debe reemplazar
// la mitad de las ocurrencias del bloque desbordado por uno
// nuevo. Este nuevo puede ser un bloque libre o uno nuevo.
// En caso del td ser igual al tamaño de la tabla (lo que implica
// que aparece una sola vez en la tabla) esta se duplica.

void DispersionEx::ActualizarTablaAlta(unsigned int td, int posTabla) {
	long nuevoBloque = this->arch_disp.ObtenerBloqueLibre();
	if (nuevoBloque == -1)
		nuevoBloque = this->arch_disp.getCantidadBloques();
	if (td == this->tabla.getSize())
		this->tabla.AumentarTabla();
	this->tabla.RecorrerYReemplazar(posTabla, nuevoBloque, td*2);
	//this->tabla.Imprimir();
	crearNuevoBloque(nuevoBloque, td*2);
}

// FUNCIONAMIENTO REDISTRIBUIR
// Redistribuye los registros desbordados insertándolos de vuelta
// en la estructura.

void DispersionEx::redistribuir(listReg& list) {
	itListReg it;
	for (it = list.begin(); it != list.end(); ++it) {
		int clave = (*it)->getClaveDato();
		insertarRecursivo(*it, clave);
	}
}

// FUNCIONAMIENTO ACTUALIZAR BLOQUE DISPERSADO
// Actualiza el td y borra los registros del bloque desbordado.

void DispersionEx::ActualizarBloqueDispersado(BloqueDato& bl, unsigned int td,
		int numBloque) {
	bl.setTd(td * 2);
	bl.setCantRegistros(0);
	bl.anularRegistros();
	this->arch_disp.Escribir(&bl, numBloque);
}

// FUNCIONAMIENTO LLENAR LISTA REGISTROS
// Llena en una lista los registros del bloque desbordado.

void DispersionEx::LlenarListaRegistros(BloqueDato& bl, listReg& list) {
	int cantRegistros = bl.getCantRegistros();
	for (int j = 0; j < cantRegistros; ++j) {
		RegistroVariable* reg = bl.getRegistro(j);
		list.push_back(reg);
	}
}

// FUNCIONAMIENTO ACTUALIZAR DISPERSION
// Al producirse un desborde este método actualiza la tabla,
// el bloque y redistribuye los registros.

void DispersionEx::ActualizarDispersion(BloqueDato& bl, int posTabla,
		int numBloque) {
	listReg list;
	unsigned int td = bl.getTd();
	ActualizarTablaAlta(td, posTabla);
	LlenarListaRegistros(bl, list);
	ActualizarBloqueDispersado(bl, td, numBloque);
	redistribuir(list);
}

// FUNCIONAMIENTO INSERTAR RECURSIVO
// Inserta un registro. En caso de desborde se actualiza
// la dispersión y se intenta insertarlo nuevamente.

int DispersionEx::insertarRecursivo(RegistroVariable* r, unsigned int clave) {
	unsigned int posTabla = clave % this->tabla.getSize();
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	unsigned int numBloque = this->tabla.getNumeroBloque(posTabla);
	this->arch_disp.Leer(numBloque, &bl);
	if (bl.addRegistro(r) == ERR_NO_MEMORIA) {
		ActualizarDispersion(bl, posTabla, numBloque);
		insertarRecursivo(r, clave);
	} else this->arch_disp.Escribir(&bl, numBloque);
	return RES_OK;
}

void DispersionEx::insertarRegistro(RegistroVariable* r, unsigned int clave) {
		insertarRecursivo(r, clave);
		this->tabla.GuardarTabla();
}

int DispersionEx::buscarRegistro(unsigned int clave, BloqueDato& bl) {
	int cantReg = bl.getCantRegistros();
	int i = 0;
	bool encontrado = false;
	while ((i <= cantReg) && (encontrado == false)) {
		RegistroVariable* reg = bl.getRegistro(i);
		if (clave == reg->getClaveDato())
			encontrado = true;
		else ++i;
	}
	if (encontrado == true)
		return i;
	else return ERR_NO_ENCONTRADO;
}

// FUNCIONAMIENTO MODIFICAR TD BLOQUES
// Recorre el archivo de bloques modificando a la mitad
// el td de los bloques datos.

void DispersionEx::modificarTdBloques(void) {
	BloqueTabla* bl = new BloqueTabla(this->arch_disp.getTamanoBloque());
	this->arch_disp.Leer(POSTABLA, bl);
	int siguienteTab = bl->getSiguiente();
	int cantBloques = this->arch_disp.getCantidadBloques();
	delete bl;
	for (int i = 1; i < cantBloques; ++i) {
		if (siguienteTab == i) {
			BloqueTabla* bl = new BloqueTabla(this->arch_disp.getTamanoBloque());
			this->arch_disp.Leer(i, bl);
			siguienteTab = bl->getSiguiente();
			delete bl;
		} else {
			BloqueDato* bl = new BloqueDato(this->arch_disp.getTamanoBloque());
			if (this->arch_disp.Leer(i, bl) == RES_OK) {
				unsigned int td = bl->getTd();
				if (td > this->tabla.getSize())
					bl->setTd(td/2);
				this->arch_disp.Escribir(bl, i);
			}
			delete bl;
		}
	}
}

// FUNCIONAMIENTO BORRAR
// Borra un registro a partir de su clave y actualiza
// la tabla en caso necesario.

void DispersionEx::Borrar(unsigned int clave) {
	unsigned int posTabla = clave % this->tabla.getSize();
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	unsigned int numBloque = this->tabla.getNumeroBloque(posTabla);
	if (this->arch_disp.Leer(numBloque, &bl) == RES_OK) {
		int posReg = buscarRegistro(clave, bl);
		if (posReg != ERR_NO_ENCONTRADO) {
			bl.borrarRegistro(posReg);
			this->arch_disp.Escribir(&bl, numBloque);
			if (bl.estaVacio()) {
				if (this->tabla.BuscarYReemplazar(posTabla, bl.getTd()/2)) {
					if (this->tabla.disminuirTabla()) {
						this->arch_disp.Borrar(numBloque);
						modificarTdBloques();
					}
				}
			}
		}
	}
}

void DispersionEx::borrarRegistro(unsigned int clave) {
	Borrar(clave);
	this->tabla.GuardarTabla();
}

// FUNCIONAMIENTO MODIFICAR
// Modifica un registro en caso que el tamaño de este
// sea menor que el tamaño del bloque.
//

void DispersionEx::Modificar(RegistroVariable* r, unsigned int clave) {
	unsigned int posTabla = clave % this->tabla.getSize();
	BloqueDato bl(this->arch_disp.getTamanoBloque());
	unsigned int numBloque = this->tabla.getNumeroBloque(posTabla);
	if (r->getTamanoDato() <= this->arch_disp.getTamanoBloque()) {
		if (this->arch_disp.Leer(numBloque, &bl) == RES_OK) {
			int posReg = buscarRegistro(clave, bl);
			if (posReg != ERR_NO_ENCONTRADO) {
				bl.borrarRegistro(posReg);
				if (bl.addRegistro(r) == ERR_NO_MEMORIA) {
					ActualizarDispersion(bl, posTabla, numBloque);
					insertarRecursivo(r, clave);
				} else this->arch_disp.Escribir(&bl, numBloque);
			}
		}
	}
}

void DispersionEx::modificarRegistro(RegistroVariable* r, unsigned int clave) {
	Modificar(r, clave);
	this->tabla.GuardarTabla();
}

// FUNCIONAMIENTO OPERATOR<<
// Escribe en un archivo de texto el contenido de la dispersión.

std::ostream& operator<<(std::ostream& oss, DispersionEx &disp) {
	oss << disp.arch_disp;
	BloqueTabla* bl = new BloqueTabla(disp.arch_disp.getTamanoBloque());
	disp.arch_disp.Leer(POSTABLA, bl);
	oss << "***********************" << std::endl;
	oss << "BLOQUE 0" << std::endl;
	bl->ImprimirATexto(oss);
	int siguienteTab = bl->getSiguiente();
	int cantBloques = disp.arch_disp.getCantidadBloques();
	delete bl;
	for (int i = 1; i < cantBloques; ++i) {
		oss << "***********************" << std::endl;
		oss << "BLOQUE " << i << std::endl;
		if (siguienteTab == i) {
			BloqueTabla* bl = new BloqueTabla(disp.arch_disp.getTamanoBloque());
			if (disp.arch_disp.Leer(i, bl) == ERR_BLOQUE_LIBRE)
				oss << "BLOQUE LIBRE" << std::endl;
			else {
				siguienteTab = bl->getSiguiente();
				bl->ImprimirATexto(oss);
			}
			delete bl;
		} else {
			BloqueDato* bl = new BloqueDato(disp.arch_disp.getTamanoBloque());
			if (disp.arch_disp.Leer(i, bl) == ERR_BLOQUE_LIBRE)
				oss << "BLOQUE LIBRE" << std::endl;
			else bl->ImprimirATexto(oss);
			delete bl;
		}
	}
	return oss;

}

DispersionEx::~DispersionEx() {

}

}

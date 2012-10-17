/* 
 * File:   RegistroVariable.h
 * Author: emperor
 *
 * Created on 6 de abril de 2012, 19:41
 */

#ifndef REGISTROVARIABLE_H
#define	REGISTROVARIABLE_H

#include <string>
#include <iostream>
#include <sstream>
using std::string;

class RegistroVariable
{
public:
    RegistroVariable();
    virtual ~RegistroVariable();
    virtual void borrarDato() = 0;
    virtual void serializar(std::ostream& oss) = 0;
    virtual unsigned long int getClaveDato(void) = 0;
    virtual int getTamanoDato(void) = 0;
    virtual void ImprimirATexto(std::ostream& oss) = 0;
    friend std::ostream& operator<<(std::ostream& oss,
					  RegistroVariable &reg);
	friend std::istream& operator>>(std::istream& oss,
					  RegistroVariable &reg);
private:
	virtual void print(std::ostream& oss) = 0;
	virtual void read(std::istream& oss) = 0;
};


std::ostream& operator<<(std::ostream& oss, RegistroVariable &reg);
std::istream& operator>>(std::istream& oss, RegistroVariable &reg);

#endif	/* REGISTROVARIABLE_H */


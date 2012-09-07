/* 
 * File:   RegistroVariable.h
 * Author: emperor
 *
 * Created on 6 de abril de 2012, 19:41
 */

#ifndef REGISTROVARIABLE_H
#define	REGISTROVARIABLE_H

#include <string>
using std::string;

class RegistroVariable
{
public:
    RegistroVariable();
    RegistroVariable(string* dato, long tamanoDato);
    string* getDato();
    void setDato(string* dato, long tamanoDato);
    long getTamanoDato();
    virtual ~RegistroVariable();
private:
    string* dato;
    long tamanoDato;
};


#endif	/* REGISTROVARIABLE_H */


/*
 * File:   Estruct.cpp
 * Author: emperor
 *
 * Created on 7 de abril de 2012, 20:30
 */

#include <iosfwd>

#include "../include/RegistroVariable.h"
using std::string;

RegistroVariable::RegistroVariable(){
 }


RegistroVariable::~RegistroVariable(){

}

std::ostream& operator<<(std::ostream& oss, RegistroVariable &reg) {
	reg.print(oss);
	return oss;
}

std::istream& operator>>(std::istream& oss, RegistroVariable &reg) {
	reg.read(oss);
	return oss;
}






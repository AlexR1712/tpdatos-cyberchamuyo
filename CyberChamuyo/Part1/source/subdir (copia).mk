################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../ArbolBp.o \
../ArchivoBloquesFijos.o \
../Bloque.o \
../CAlfa.o \
../CEntero.o \
../Clave.o \
../FrontCoding.o \
../IndiceArbol.o \
../Nodo.o \
../NodoExterno.o \
../NodoInterno.o \
../Registro.o \
../RegistroArbol.o \
../RegistroVariable.o \
../common.o \
../main.o 

CPP_SRCS += \
../ArbolBp.cpp \
../ArchivoBloquesFijos.cpp \
../Bloque.cpp \
../CAlfa.cpp \
../CEntero.cpp \
../Clave.cpp \
../FrontCoding.cpp \
../IndiceArbol.cpp \
../Nodo.cpp \
../NodoExterno.cpp \
../NodoInterno.cpp \
../Registro.cpp \
../RegistroArbol.cpp \
../RegistroVariable.cpp \
../common.cpp \
../main.cpp 

OBJS += \
./ArbolBp.o \
./ArchivoBloquesFijos.o \
./Bloque.o \
./CAlfa.o \
./CEntero.o \
./Clave.o \
./FrontCoding.o \
./IndiceArbol.o \
./Nodo.o \
./NodoExterno.o \
./NodoInterno.o \
./Registro.o \
./RegistroArbol.o \
./RegistroVariable.o \
./common.o \
./main.o 

CPP_DEPS += \
./ArbolBp.d \
./ArchivoBloquesFijos.d \
./Bloque.d \
./CAlfa.d \
./CEntero.d \
./Clave.d \
./FrontCoding.d \
./IndiceArbol.d \
./Nodo.d \
./NodoExterno.d \
./NodoInterno.d \
./Registro.d \
./RegistroArbol.d \
./RegistroVariable.d \
./common.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g -c -fmessage-length=0 -fpermissive -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



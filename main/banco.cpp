#include <stdio.h>
#include "banco.hpp"

Banco::Banco(){
    this->memoria_i2c = Memoria();
}

//ralph
void Banco::resetBanco(){
    this->memoria_i2c.init(0)
    // memoria tem 65536 endereços de 1byte (8bits)
    memori

}

//ralph
void Banco::adicionaRegistro(Registro reg){

}

//ralph
void Banco::removeRegistro(int add){

}

//manu
Registro Banco::getRegistro(int add){

}

//manu
int Banco::getIndiceRegistroPorNome(){

}

//manu
int Banco::getIndiceRegistroPorTelefone(){

}

//ralph
void Banco::desfragmentaBanco(){

}

//manu
void Banco::getStatusBanco(){

}
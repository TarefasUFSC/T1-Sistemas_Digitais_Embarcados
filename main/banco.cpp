#include <stdio.h>
#include "banco.hpp"
#include "serial.h"

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
    printf("Digite o nome: ");
    serial.readString((uint8_t *)leitura,20);
    printf("%s\n",leitura);

}

//manu
int Banco::getIndiceRegistroPorTelefone(){
    printf("Digite o telefone: ");
    serial.readString((uint8_t *)leitura,10);
    printf("%s\n",leitura);

}

//ralph
void Banco::desfragmentaBanco(){

}

//manu
void Banco::getStatusBanco(){

}
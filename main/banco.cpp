#include <stdio.h>
#include "banco.hpp"
#include "serial.h"

void Banco::resetBanco(){

}

void Banco::adicionaRegistro(Registro reg){

}

void Banco::removeRegistro(int add){

}

Registro Banco::getRegistro(int add){

}

int Banco::getIndiceRegistroPorNome(){
    printf("Digite o nome: ");
    serial.readString((uint8_t *)leitura,20);
    printf("%s\n",leitura);

}

int Banco::getIndiceRegistroPorTelefone(){
    printf("Digite o telefone: ");
    serial.readString((uint8_t *)leitura,10);
    printf("%s\n",leitura);

}

void Banco::desfragmentaBanco(){

}

void Banco::getStatusBanco(){

}
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

}

//ralph
void Banco::adicionaRegistro(Registro reg){

}

//ralph
void Banco::removeRegistro(int add){

}

//manu
Registro Banco::getRegistro(int add){
    //return the register objetc at the address add
    char read_data[64];
    Registro reg;
    memoria_i2c.le(add, (char*) read_data, 64);
    for(int i = 0; i < 20; i++){
        reg.nome[i] = read_data[i];
    }
    for(int i = 0; i < 14; i++){
        reg.telefone[i] = read_data[i+20];
    }
    for(int i = 0; i < 30; i++){
        reg.endereco[i] = read_data[i+34];
    }
    return reg;
}

//manu
int Banco::getIndiceRegistroPorNome(){
    char leitura[20];
    printf("Digite o nome: ");
    serial.readString((uint8_t *)leitura,20);
    printf("%s\n",leitura);

    //find the address of the name in the memory
    int address = 0;
    for(int i = 0; i < 65536; i++){
        char read_data[64];
        memoria_i2c.le(i, (char*) read_data, 64);
        for(int j = 0; j < 20; j++){
            if(read_data[j] != leitura[j]){
                break;
            }
            if(j == 19){
                address = i;
            }
        }
    }

    return address;

}

//manu
int Banco::getIndiceRegistroPorTelefone(){
    char leitura[14];
    printf("Digite o telefone: ");
    serial.readString((uint8_t *)leitura,14);
    printf("%s\n",leitura);

}

//ralph
void Banco::desfragmentaBanco(){

}

//manu
void Banco::getStatusBanco(){

}
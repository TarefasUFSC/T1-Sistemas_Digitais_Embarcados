#include <stdio.h>
#include "banco.hpp"
#include "serial.h"

Banco::Banco()
{
    //this->memoria_i2c = Memoria();
    this->resetBanco();
}

// ralph
void Banco::resetBanco()
{
    //this->memoria_i2c.init(0);
    // memoria tem 65536 endereços de 1byte (8bits)
    // maior tamanho possivel, considerando cada registro com 64 bytes, é 1024 registros
    // mas como vou gastar 64 bytes para guardar o indice, o maximo de registros é 1023
    uint8_t header[64];
    header[0] = 0;
    header[1] = 0;
    // como 1023 tem 10bits, 11 1111 1111
    //  vou salvar como:
    //     11 1111 1111 >> 8 = 0000 0011
    //     11 1111 1111, que quando salva em 8 bits fica 1111 1111
    //  ai na hr de ler é só juntar essas duas infos
    header[2] = 1023 >> 8;
    header[3] = 1023;
    //this->memoria_i2c.escreve(0, header, 64);
}

// ralph
void Banco::adicionaRegistro(Registro reg)
{
}

// ralph
void Banco::removeRegistro(int add)
{
}

// manu
Registro Banco::getRegistro(int add)
{
    Registro reg = Registro();
    return reg;
}

// manu
int Banco::getIndiceRegistroPorNome()
{
    printf("Digite o nome: ");
    //serial.readString((uint8_t *)leitura, 20);
    //printf("%s\n", leitura);
    return 0;
}

// manu
int Banco::getIndiceRegistroPorTelefone()
{
    printf("Digite o telefone: ");
    //serial.readString((uint8_t *)leitura, 10);
    //printf("%s\n", leitura);
    return 0;
}

// ralph
void Banco::desfragmentaBanco()
{
}

// manu
void Banco::getStatusBanco()
{
    uint8_t header[64];
    //memoria_i2c.le(0, (uint8_t *)header, 4);

    //printf("N. de Registros = %d\n", (header[0]<<8) * 4 + header[1]);
    //printf("Endereço do ultimo registro = %d\n", (header[2]<<8) * 4 + header[3]);
}
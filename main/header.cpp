#include "banco.hpp"
#include "serial.hpp"
#include "memoria.hpp"

Header::Header()
{
    for (int i = 0; i < 64; i++)
    {
        this->bytes[i] = 0;
    }
}

void Header::leHeader(Memoria &memoria_i2c)
{
    memoria_i2c.le(0, this->bytes, 64);
    this->quantidade_atual = this->bytes[0] << 8 | this->bytes[1];
    this->tamanho_maximo = this->bytes[2] << 8 | this->bytes[3];
}
void Header::escreveHeader(Memoria &memoria_i2c)
{
    // maior tamanho possivel, considerando cada registro com 64 bytes, é 1024 registros
    // mas como vou gastar 64 bytes para guardar o indice, o maximo de registros é 1023
    // como 1023 tem 10bits, 11 1111 1111
    //  vou salvar como:
    //     11 1111 1111 >> 8 = 0000 0011
    //     11 1111 1111, que quando salva em 8 bits fica 1111 1111
    // ai na hr de ler é só juntar essas duas infos
    // header[2] = 1023 >> 8;  //0000 0011
    // header[3] = 1023;       //1111 1111
    this->bytes[0] = this->quantidade_atual >> 8;
    this->bytes[1] = this->quantidade_atual;
    this->bytes[2] = this->tamanho_maximo >> 8;
    this->bytes[3] = this->tamanho_maximo;
    memoria_i2c.escreve(0, this->bytes, 64);
}
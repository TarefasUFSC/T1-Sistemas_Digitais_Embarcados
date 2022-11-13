#include "registro.hpp"


Registro::Registro()
{
    this->nome = "";
    this->telefone = "";
    this->endereco = "";
}
Registro::Registro(string nome, string telefone, string endereco)
{
    this->nome = nome.c_str();
    this->telefone = telefone.c_str();
    this->endereco = endereco.c_str();
}

Registro::Registro(uint8_t* bytes)
{
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        this->nome[i] = bytes[i];
    }
    for (i = 0; i < 14; i++)
    {
        this->telefone[i] = bytes[i+20];
    }
    for (i = 0; i < 30; i++)
    {
        this->endereco[i] = bytes[i+34];
    }
}

uint8_t* Registro::returnBytes()
{
    uint8_t bytes[64];
    for(int i = 0; i < 20; i++)
    {
        bytes[i] = this->nome[i];
    }
    for(int i = 0; i < 14; i++)
    {
        bytes[i+20] = this->telefone[i];
    }
    for(int i = 0; i < 30; i++)
    {
        bytes[i+34] = this->endereco[i];
    }
    return bytes;
}


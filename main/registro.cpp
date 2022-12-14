#include "registro.hpp"

Registro::Registro()
{
    for (int i = 0; i < 21; i++)
    {
        this->nome[i] = '\0';
    }
    for (int i = 0; i < 15; i++)
    {
        this->telefone[i] = '\0';
    }
    for (int i = 0; i < 31; i++)
    {
        this->endereco[i] = '\0';
    }
}
Registro::Registro(string nome, string telefone, string endereco)
{
    for (int i = 0; i < 20; i++)
    {
        this->nome[i] = nome[i];
    }
    for (int i = 0; i < 14; i++)
    {
        this->telefone[i] = telefone[i];
    }
    for (int i = 0; i < 30; i++)
    {
        this->endereco[i] = endereco[i];
    }
    this->nome[20] = '\0';
    this->telefone[14] = '\0';
    this->endereco[30] = '\0';
}

Registro::Registro(uint8_t *bytes)
{
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        this->nome[i] = bytes[i];
    }
    for (i = 0; i < 14; i++)
    {
        this->telefone[i] = bytes[i + 20];
    }
    for (i = 0; i < 30; i++)
    {
        this->endereco[i] = bytes[i + 34];
    }
    
    this->nome[20] = '\0';
    this->telefone[14] = '\0';
    this->endereco[30] = '\0';
}

uint8_t *Registro::returnBytes()
{
    uint8_t *bytes = new uint8_t[64];
    for (int i = 0; i < 20; i++)
    {
        bytes[i] = this->nome[i];
    }
    for (int i = 0; i < 14; i++)
    {
        bytes[i + 20] = this->telefone[i];
    }
    for (int i = 0; i < 30; i++)
    {
        bytes[i + 34] = this->endereco[i];
    }
    return bytes;
}

void Registro::printRegistro()
{
    printf("Nome: %s\n", this->nome);
    printf("Telefone: %s\n", this->telefone);
    printf("Endereco: %s\n", this->endereco);
    printf(" \n");
}

#ifndef _BANCO_
#define _BANCO_

#include "registro.hpp"
#include "serial.hpp"
#include "memoria.hpp"
#include <vector>

class Header
{
public:
    uint16_t quantidade_atual;
    uint16_t tamanho_maximo;
    uint8_t bytes[64];

public:
    Header();
    void leHeader(Memoria &memoria_i2c);
    void escreveHeader(Memoria &memoria_i2c);
};

class Banco
{
private:
    Memoria memoria_i2c;

private:
    bool verificaTextoIgual(char *texto1, char *texto2, uint8_t tamanho);

public:
    Banco();
    void resetBanco();
    void adicionaRegistro(Registro reg);
    void removeRegistro(uint8_t add);
    vector<Registro> getTodosRegistros();
    Registro *getRegistro(uint8_t add);
    uint8_t getIndiceRegistroPorNome(char *nome);
    uint8_t getIndiceRegistroPorTelefone(char *telefone);
    void desfragmentaBanco(uint8_t pos_excluida);
    void getStatusBanco();
};

#endif
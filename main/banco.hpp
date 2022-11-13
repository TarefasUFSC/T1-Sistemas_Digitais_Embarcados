#ifndef _BANCO_
#define _BANCO_

#include "registro.hpp"
#include "serial.hpp"
#include "memoria.hpp"
#include <vector>

class Banco {
    private:
        Memoria memoria_i2c;
    public:
        Banco();
        void resetBanco();
        void adicionaRegistro(Registro reg);
        void removeRegistro(uint8_t add);
        vector<Registro> getTodosRegistros();
        Registro* getRegistro(uint8_t add);
        uint8_t getIndiceRegistroPorNome(char* nome);
        uint8_t getIndiceRegistroPorTelefone(char* telefone);
        void desfragmentaBanco(uint8_t pos_excluida);
        void getStatusBanco();
};


#endif
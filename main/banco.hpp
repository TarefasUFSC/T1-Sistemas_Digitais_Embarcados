#ifndef _BANCO_
#define _BANCO_

#include "registro.hpp"
#include "serial.hpp"
#include "memoria.hpp"

class Banco {
    private:
        Memoria memoria_i2c;
    public:
        Banco();
        void resetBanco();
        void adicionaRegistro(Registro reg);
        void removeRegistro(int add);
        Registro getRegistro(int add);
        int getIndiceRegistroPorNome();
        int getIndiceRegistroPorTelefone();
        void desfragmentaBanco();
        void getStatusBanco();
};


#endif
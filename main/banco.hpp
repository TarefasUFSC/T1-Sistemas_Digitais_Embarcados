#ifndef _BANCO_
#define _BANCO_

#include <iostream>
#include "registro.hpp"

class Banco {
    public:
        void resetBanco()
        void adicionaRegistro(Registro reg)
        void removeRegistro(int add)
        Registro getRegistro(int add)
        int getIndiceRegistroPorNome()
        int getIndiceRegistroPorTelefone()
        void desfragmentaBanco()
        void getStatusBanco()
};


#endif
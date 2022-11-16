#ifndef _REGISTRO_
#define _REGISTRO_

#include <string>

using namespace std;

class Registro {
    public:
        char nome[21];
        char telefone[15];
        char endereco[31];
    
    public:
        Registro();
        Registro(string nome, string telefone, string endereco);
        Registro(uint8_t* bytes);
        uint8_t* returnBytes();
        void printRegistro();
};

#endif
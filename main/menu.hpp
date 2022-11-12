#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include <string.h>
#include "banco.hpp"
void listaRegistros(Banco banco);
void buscaRegistroPorNome(Banco banco);
void buscaRegistroPorTelefone(Banco banco);
void addRegistro(Banco banco);
void subRegistro(Banco banco);
void statusRegistros(Banco banco);
void resetBanco(Banco banco);

#endif
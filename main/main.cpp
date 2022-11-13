#include <stdio.h>
#include <map>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.hpp"
#include "banco.hpp"
//#include "menu.hpp"
//#include "memoria.hpp"
#include <inttypes.h>

extern "C" void app_main();
int v=0;


void printMenu()
{
    

    printf(" \n");
    printf("[1] - Lista todos os registros\n");
    printf("[2] - pesquisa registro por nome\n");
    printf("[3] - pesquisa registro por telefone\n");
    printf("[4] - adiciona novo registro\n");
    printf("[5] - remove registro baseado no telefone\n");
    printf("[6] - mostra a quantidade de registros atualmente armazenados\n");
    printf("[7] - Inicializa o banco de dados (todas as informacoes armazenadas serao perdidas)\n");
    
    //return '1';
}

static Banco banco = Banco();
void listaRegistros(){
    printf("Lista de registros\n");
    vector<Registro> registros = banco.getTodosRegistros();
    for (int i = 0; i < registros.size(); i++)
    {
        registros.at(i).printRegistro();
    }
}
void buscaRegistroPorNome(){
    printf("Busca registro por nome\n");
    char nome[20];
    printf("Digite o nome: \n");
    serial.readString((uint8_t *)nome, 20);
    printf("%s\n", nome);
    uint8_t add = banco.getIndiceRegistroPorNome(nome);
    printf("Indice: %d\n", add);
    if(add != 0){
        Registro *reg = banco.getRegistro(add);
        reg->printRegistro();
    }
    else{
        printf("Registro nao encontrado\n");
    }
}
void buscaRegistroPorTelefone(){
    printf("Busca registro por telefone\n");
    printf("Digite o telefone: \n");
    char telefone[14];
    serial.readString((uint8_t *)telefone, 14);
    printf("%s\n", telefone);
    uint8_t add = banco.getIndiceRegistroPorTelefone(telefone);
    printf("Indice: %d\n", add);
    if(add != 0){
        Registro *reg = banco.getRegistro(add);
        reg->printRegistro();
    }
    else{
        printf("Registro nao encontrado\n");
    }
}
void addRegistro(){
    printf("Adiciona registro\n");
    char nome[20];
    char telefone[14];
    char endereco[40];
    printf("Digite o nome: \n");
    serial.readString((uint8_t *)nome, 20);
    printf("%s\n", nome);
    printf("Digite o telefone: \n");
    serial.readString((uint8_t *)telefone, 14);
    printf("%s\n", telefone);
    printf("Digite o endereco: \n");
    serial.readString((uint8_t *)endereco, 40);
    printf("%s\n", endereco);
    Registro reg = Registro(nome, telefone, endereco);
    banco.adicionaRegistro(reg);
}
void subRegistro(){
    printf("Remove registro\n");
    char telefone[14];
    printf("Digite o telefone: \n");
    serial.readString((uint8_t *)telefone, 14);
    printf("%s\n", telefone);
    banco.removeRegistro(banco.getIndiceRegistroPorTelefone(telefone));
}
void statusRegistros(){
    printf("Status de registros\n");
    banco.getStatusBanco();
}
void resetBanco(){
    printf("Reset Banco banco de dados\n");
    banco.resetBanco();
}

void app_main()
{
    serial.begin(9600);
    typedef void (*funcP)();
    map<char, funcP> myMap;
    myMap['1'] = listaRegistros;
    myMap['2'] = buscaRegistroPorNome;
    myMap['3'] = buscaRegistroPorTelefone;
    myMap['4'] = addRegistro;
    myMap['5'] = subRegistro;
    myMap['6'] = statusRegistros;
    myMap['7'] = resetBanco;

    while (1)
    {
       printMenu();
       
        char choice = serial.readChar();
        if (myMap.find(choice) != myMap.end())
        {
            printf("choice: %c\n", choice);
            myMap[choice]();
        }
        else
        {
            printf("Opcao invalida\n\n\n");
        }
    }
    
}
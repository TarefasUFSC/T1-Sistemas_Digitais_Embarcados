#include <stdio.h>
#include <map>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.h"
//#include "banco.hpp"
#include "menu.hpp"
//#include "memoria.h"
#include <inttypes.h>

using namespace std;
extern "C" void app_main();

void printMenu()
{
    

    char choice;
    printf(" \n");
    printf("[1] - Lista todos os registros\n");
    printf("[2] - pesquisa registro por nome\n");
    printf("[3] - pesquisa registro por telefone\n");
    printf("[4] - adiciona novo registro\n");
    printf("[5] - remove registro baseado no telefone\n");
    printf("[6] - mostra a quantidade de registros atualmente armazenados\n");
    printf("[7] - Inicializa o banco de dados (todas as informacoes armazenadas serao perdidas)\n");
    
    //choice = serial.readChar();
    //return '1';
}

void app_main()
{
    //static Banco banco = Banco();
    serial.begin(9600);
    // typedef void (*funcP)(Banco banco);
    // map<char, funcP> myMap;
    // myMap['1'] = listaRegistros;
    // myMap['2'] = buscaRegistroPorNome;
    // myMap['3'] = buscaRegistroPorTelefone;
    // myMap['4'] = addRegistro;
    // myMap['5'] = subRegistro;
    // myMap['6'] = statusRegistros;
    // myMap['7'] = resetBanco;

    // while (1)
    // {
        printMenu();
    //     if (myMap.find(choice) != myMap.end())
    //     {
    //         myMap[choice](banco);
    //     }
    //     else
    //     {
    //         printf("Opcao invalida\n\n\n");
    //     }
    // }
    
}
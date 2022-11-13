#include <stdio.h>
#include "banco.hpp"
#include "serial.hpp"
#include "memoria.hpp"
#include <vector>

Banco::Banco()
{
    this->memoria_i2c = Memoria();
    this->resetBanco();
}

// ralph
void Banco::resetBanco()
{
    this->memoria_i2c.init(0);
    // memoria tem 65536 endereços de 1byte (8bits)

    // maior tamanho possivel, considerando cada registro com 64 bytes, é 1024 registros
    // mas como vou gastar 64 bytes para guardar o indice, o maximo de registros é 1023
    uint8_t header[64];
    header[0] = 0;
    header[1] = 0;
    // como 1023 tem 10bits, 11 1111 1111
    //  vou salvar como:
    //     11 1111 1111 >> 8 = 0000 0011
    //     11 1111 1111, que quando salva em 8 bits fica 1111 1111
    //  ai na hr de ler é só juntar essas duas infos
    header[2] = 1023 >> 8;  //0000 0011
    header[3] = 1023;       //1111 1111
    // 11 1111 1111


    this->memoria_i2c.escreve(0, header, 64);

}

// ralph
void Banco::adicionaRegistro(Registro reg)
{
    // 1 - ler o header
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    // 2 - ler a qtd
    uint16_t quantidade_atual = header[0] << 8 | header[1];
    // 3 - ler o tamanho maximo
    uint16_t tamanho_maximo = header[2] << 8 | header[3];
    // 4 - verificar se o indice é menor que o tamanho maximo
    if (quantidade_atual < tamanho_maximo)
    {
        // 5 - escrever o registro na memoria
        // ele começa a colocar na posição 1, pois a posição 0 é o header
        this->memoria_i2c.escreve(((quantidade_atual + 1)) * 64, reg.returnBytes(), 64);
        // 6 - incrementar a qtd
        quantidade_atual++;
        // 7 - salvar a qtd no header
        header[0] = quantidade_atual >> 8;
        header[1] = quantidade_atual;
        // 8 - salvar o header na memoria
        this->memoria_i2c.escreve(0, header, 64);
    }
}

// ralph
void Banco::removeRegistro(uint8_t add)
{
    // 1 - ler o header
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    // 2 - ler a qtd
    uint16_t quantidade_atual = header[0] << 8 | header[1];
    // 3 - ler o tamanho maximo
    uint16_t tamanho_maximo = header[2] << 8 | header[3];
    
    uint8_t vazio[64];
    for (int i = 0; i < 64; i++)
    {
        vazio[i] = 0;
    }
    quantidade_atual--;
    // salva o novo header
    header[0] = quantidade_atual >> 8;
    header[1] = quantidade_atual;
    this->memoria_i2c.escreve(0, header, 64);
    // salva o vazio
    this->memoria_i2c.escreve(add * 64, vazio, 64);
    // desfragmenta o banco
    this->desfragmentaBanco(add);
}

//ralph
vector<Registro> Banco::getTodosRegistros()
{
    vector<Registro> registros;
    // 1 - ler o header
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    // 2 - ler a qtd
    uint16_t quantidade_atual = header[0] << 8 | header[1];
    // 3 - ler o tamanho maximo
    uint16_t tamanho_maximo = header[2] << 8 | header[3];
    // 4 - ler todos os registros
    for (int i = 1; i <= quantidade_atual; i++)
    {
        uint8_t reg[64];
        this->memoria_i2c.le(i * 64, reg, 64);
        registros.push_back(Registro(reg));
    }
    return registros;
}


//manu
Registro* Banco::getRegistro(uint8_t add){
    // 1 - ler o header
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    // 2 - ler a qtd
    uint16_t quantidade_atual = header[0] << 8 | header[1];
    // 4 - verificar se o endereço é menor que a quantidade atual
    Registro *reg;
    if (add <= quantidade_atual){
        uint8_t read_data[64];
        memoria_i2c.le(add*64, read_data, 64);
        reg = new Registro(read_data);
    }
    else{
        reg = new Registro();
    }
    return reg;
}

//manu
uint8_t Banco::getIndiceRegistroPorNome(char* nome){
    // 1 - ler o header
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    // 2 - ler a qtd
    uint16_t quantidade_atual = header[0] << 8 | header[1];
    //find the address of the name in the memory
    for(int i = 1; i <= quantidade_atual; i++){
        bool achou = true;
        uint8_t read_data[64];
        memoria_i2c.le(i*64, read_data, 64);
        for(int j = 0; j < 20; j++){
            printf("%d - %d ",  read_data[j],nome[j] );
            if(nome[j] == 0 || nome[j] == '\n'){
                break;
            }
            if(read_data[j] != nome[j]){
                achou = false;
                printf("diferene \n");
                break;
            }
            
        }
        if(achou){
            printf("encontrado no endereco %d\n", i);
            return i;
        }
    }
    return 0;
}

//manu
uint8_t Banco::getIndiceRegistroPorTelefone(char* telefone){
    // 1 - ler o header
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    // 2 - ler a qtd
    uint16_t quantidade_atual = header[0] << 8 | header[1];
    //find the address of the name in the memory
    for(int i = 1; i <= quantidade_atual; i++){
        bool achou = true;
        uint8_t read_data[64];
        memoria_i2c.le(i*64, read_data, 64);
        for(int j = 20; j < 24; j++){
            //printf("%d - %d",  read_data[j],telefone[j-20] );
            if(telefone[j-20] == 0 || telefone[j-20] == '\n'){
                break;
            }
            if(read_data[j] != telefone[j-20]){
                achou = false;
                //printf("diferene \n");
                break;
            }
            
        }
        if(achou){
            printf("encontrado no endereco %d\n", i);
            return i;
        }
    }
    return 0;
}

// ralph
void Banco::desfragmentaBanco(uint8_t pos_excluida)
{
    // 1 - ler o header
    uint8_t header[64];
    this->memoria_i2c.le(0, header, 64);
    // 2 - ler a qtd
    uint16_t quantidade_atual = header[0] << 8 | header[1];
    // 3 - ler o tamanho maximo
    uint16_t tamanho_maximo = header[2] << 8 | header[3];

    // troca o ultimo registro com o registro excluido
    uint8_t ultimo_registro[64];
    this->memoria_i2c.le((quantidade_atual+1) * 64, ultimo_registro, 64);
    this->memoria_i2c.escreve(pos_excluida * 64, ultimo_registro, 64);

    // se quiser apagar completamente o ultimo registro
    // uint8_t vazio[64];
    // for (int i = 0; i < 64; i++)
    // {
    //     vazio[i] = 0;
    // }
    // this->memoria_i2c.escreve((quantidade_atual+1) * 64, vazio, 64);
}

// manu
void Banco::getStatusBanco()
{
    uint8_t header[64];
    memoria_i2c.le(0, (uint8_t *)header, 4);

    printf("N. de Registros = %d\n", (header[0]<<8)+ header[1]);
    // 0000 0011 <<8 = 11 0000 0000
    printf("Posicao maxima para registro = %d\n", (header[2]<<8) + header[3]);
}
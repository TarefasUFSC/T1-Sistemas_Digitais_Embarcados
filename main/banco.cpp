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
Registro Banco::getRegistro(int add){
    //return the register objetc at the address add
    char read_data[64];
    Registro reg;
    memoria_i2c.le(add, (char*) read_data, 64);
    for(int i = 0; i < 20; i++){
        reg.nome[i] = read_data[i];
    }
    for(int i = 0; i < 14; i++){
        reg.telefone[i] = read_data[i+20];
    }
    for(int i = 0; i < 30; i++){
        reg.endereco[i] = read_data[i+34];
    }
    return reg;
}

//manu
int Banco::getIndiceRegistroPorNome(){
    char leitura[20];
    printf("Digite o nome: ");
    serial.readString((uint8_t *)leitura,20);
    printf("%s\n",leitura);

    //find the address of the name in the memory
    int address = 0;
    for(int i = 0; i < 65536; i++){
        char read_data[64];
        memoria_i2c.le(i, (char*) read_data, 64);
        for(int j = 0; j < 20; j++){
            if(read_data[j] != leitura[j]){
                break;
            }
            if(j == 19){
                address = i;
            }
        }
    }

    return address;

}

//manu
int Banco::getIndiceRegistroPorTelefone(){
    char leitura[14];
    printf("Digite o telefone: ");
    serial.readString((uint8_t *)leitura,14);
    printf("%s\n",leitura);


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
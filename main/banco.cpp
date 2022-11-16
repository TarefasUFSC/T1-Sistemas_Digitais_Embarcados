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
    Header header = Header();
    header.quantidade_atual = 0;
    header.tamanho_maximo = 1023;
    header.escreveHeader(this->memoria_i2c);
}

// ralph
void Banco::adicionaRegistro(Registro reg)
{
    Header header = Header();
    header.leHeader(this->memoria_i2c);
    // 4 - verificar se o indice é menor que o tamanho maximo
    if (header.quantidade_atual < header.tamanho_maximo)
    {
        // 5 - escrever o registro na memoria
        // ele começa a colocar na posição 1, pois a posição 0 é o header
        this->memoria_i2c.escreve(((header.quantidade_atual + 1)) * 64, reg.returnBytes(), 64);
        // 6 - incrementar a qtd
        header.quantidade_atual++;
        // 7 - salvar a qtd no header
        header.escreveHeader(this->memoria_i2c);
    }
}

// ralph
void Banco::removeRegistro(uint8_t add)
{
    // 1 - ler o header
    Header header = Header();
    header.leHeader(this->memoria_i2c);

    uint8_t vazio[64];
    for (int i = 0; i < 64; i++)
    {
        vazio[i] = 0;
    }
    header.quantidade_atual--;
    // salva o novo header
    header.escreveHeader(this->memoria_i2c);
    // salva o vazio
    this->memoria_i2c.escreve(add * 64, vazio, 64);
    // desfragmenta o banco
    this->desfragmentaBanco(add);
}

// ralph
vector<Registro> Banco::getTodosRegistros()
{
    vector<Registro> registros;
    // 1 - ler o header

    Header header = Header();
    header.leHeader(this->memoria_i2c);
    // 4 - ler todos os registros
    for (int i = 1; i <= header.quantidade_atual; i++)
    {
        uint8_t reg[64];
        this->memoria_i2c.le(i * 64, reg, 64);
        registros.push_back(Registro(reg));
    }
    return registros;
}

// manu
Registro *Banco::getRegistro(uint8_t add)
{
    // 1 - ler o header
    Header header = Header();
    header.leHeader(this->memoria_i2c);
    // 4 - verificar se o endereço é menor que a quantidade atual
    Registro *reg;
    if (add <= header.quantidade_atual)
    {
        uint8_t read_data[64];
        memoria_i2c.le(add * 64, read_data, 64);
        reg = new Registro(read_data);
    }
    else
    {
        reg = new Registro();
    }
    return reg;
}

bool Banco::verificaTextoIgual(char *texto1, char *texto2, uint8_t tamanho)
{
    for (int j = 0; j < tamanho; j++)
    {
        //printf("%d - %d ", texto1[j], texto2[j]);
        if (texto2[j] == 0 || texto2[j] == '\n')
        {
            return true;
        }
        if (texto1[j] != texto2[j])
        {
            //printf("diferente \n");
            return false;
        }
    }
    return false;
    // manu
}
uint8_t Banco::getIndiceRegistroPorNome(char *nome)
{
    // 1 - ler o header

    Header header = Header();
    header.leHeader(this->memoria_i2c);
    // find the address of the name in the memory
    for (int i = 1; i <= header.quantidade_atual; i++)
    {
        uint8_t read_data[64];
        memoria_i2c.le(i * 64, read_data, 64);
        Registro reg = Registro(read_data);
        if (verificaTextoIgual(reg.nome, nome, 20))
        {
            printf("encontrado no endereco %d\n", i);
            return i;
        }
    }
    return 0;
}

// manu
uint8_t Banco::getIndiceRegistroPorTelefone(char *telefone)
{
    // 1 - ler o header
    Header header = Header();
    header.leHeader(this->memoria_i2c);
    // find the address of the name in the memory
    for (int i = 1; i <= header.quantidade_atual; i++)
    {

        for (int i = 1; i <= header.quantidade_atual; i++)
        {
            uint8_t read_data[64];
            memoria_i2c.le(i * 64, read_data, 64);
            Registro reg = Registro(read_data);
            if (verificaTextoIgual(reg.telefone, telefone, 14))
            {
                printf("encontrado no endereco %d\n", i);
                return i;
            }
        }
    }
    return 0;
}

// ralph
void Banco::desfragmentaBanco(uint8_t pos_excluida)
{
    // 1 - ler o header
    Header header = Header();
    header.leHeader(this->memoria_i2c);

    // troca o ultimo registro com o registro excluido
    uint8_t ultimo_registro[64];
    this->memoria_i2c.le((header.quantidade_atual + 1) * 64, ultimo_registro, 64);
    this->memoria_i2c.escreve(pos_excluida * 64, ultimo_registro, 64);

    // se quiser apagar completamente o ultimo registro
    uint8_t vazio[64];
    for (int i = 0; i < 64; i++)
    {
        vazio[i] = 0;
    }
    this->memoria_i2c.escreve((header.quantidade_atual + 1) * 64, vazio, 64);
}

// manu
void Banco::getStatusBanco()
{

    Header header = Header();
    header.leHeader(this->memoria_i2c);

    printf("N. de Registros = %d\n", header.quantidade_atual);
    // 0000 0011 <<8 = 11 0000 0000
    printf("Posicao maxima para registro = %d\n", header.tamanho_maximo);
}
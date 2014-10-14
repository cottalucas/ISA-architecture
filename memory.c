///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
/////// memory.c
/////// Modulo de controle de memoria
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
 
#include "memory.h"
#include <string.h>
#include <math.h>
 
 
///////////////////////////////////////
//variaveis privadas do mуdulo de memуria
//funcoes publicas serao localizadas em memory.h
///////////////////////////////////////
__uint40_t Memory[__MEMORY_MAX__]; //memуria total tem 4096 espaзos para armazenar
int firstOperation; //primeira instrucao
int firstVariable;
int lastMemory;
 
int getFirstOperation() {return firstOperation}
 
void resetMemory()
{
    firstOperation = 0;
    firstVariable = 0;
    lastMemory = 0;
    int i;
    for(i = 0; i<0x1000; i++){
        Memory[i] = 0;
    }
}
 
//hexStrToMemory
//CUIDADO: esta funзгo assume que serб enviado um nъmero hexadecimal
//         como parametro. Ela nao faz nenhuma verificacao de parametro
//         e retorna o valor numerico da string utilizada como parametro
__uint40_t hexStrToMemory(const char* hexStr)
{
    char *f;
    return strtoll(hexStr, &f, 0);
}
 
char* memoryToStr(addr);
{
 
}
 
//loadMemory(stream)
//Carrega os valores hexadecimais de stream na memуria
int loadMemory(FILE* stream)
{
    if(stream == NULL)
        return -1; //TODO: erro de arquivo nulo
 
    resetMemory();
 
    char c[12]; //12 caracteres: 10 para o hex, 1 para \n e 1 para \0
    int i = 0;
    do
    {
        if( fgets(c, 12, stream) != NULL )
        {
            if(strncmp(c, "0000000000", 10) == 0)
            {
                i++;
                firstVariable = i;
            }
            else
            {
                Memory[i] = hexStrToMemory(c);
                i++;
            }
        }
    }while(!feof(stream));
    lastMemory = i;
    return 0;
}
 
//LoadMemoryAddress(addr)
//Coloca o valor de ADDR em MBR para uso posterior
//retorna -1 se addr estiver fora dos limites, ou 0 se nao ocorrer erro
int LoadMemoryAddress(int addr)
{
    if(addr >= lastMemory)
        return -1; //TODO: erro de memoria fora dos limites
 
    MBR = Memory[addr];
    return 0;
}
 
//AlterMemoryAddress(addr, value, range, firstBitFrom, firstBitTo)
//Modifica o valor no contexto de range para value
//firstBitFrom й o primeiro bit de value que sera considerado
//firstBitTo й o primeiro bit da memoria que sera modificado
//da direita pra esquerda; ou seja, "range=12" e "firstBitFrom=08" significa 08->19
int AlterMemoryAddress(int addr, __uint40_t value, int range, int firstBitFrom, int firstBitTo)
{
    if(addr >= lastMemory)
        return -1; //TODO: erro de memoria fora dos limites
 
    if(range < 1 || range > 40)
        return -2; //TODO: erro de area fora dos limites
 
    int rollSize = 40 - range;
 
    if(firstBitFrom < 0 || firstBitFrom >= rollSize || firstBitTo < 0 || firstBitTo >= rollSize)
        return -3; //TODO: erro de primeiro bit fora de limites
 
    if(range == 40){
        Memory[addr] = value;
        return 0;
    }
 
 
    __uint40_t modifier = NORMALIZE( (uint64_t)pow(2.0, (double)range ) - 1);
    value &= ( modifier << (rollSize - firstBitFrom) ); //pega o valor no espaco determinado
    value >>= ( rollSize - firstBitFrom ); //Tirar zeros а direita
 
    /* exemplo
        range = 4; fBF = 0
        modifier = 0000 0000 1111 << 8 = 1111 0000 0000
        1101 0110 1101 &
        1111 0000 0000  =
        1101 0000 0000 >> 8 = 0000 0000 1101
    */
 
    Memory[addr] &= ~( modifier << (rollSize - firstBitTo) ); //limpa o espaзo de memoria que sera modificado
    Memory[addr] |= ( value << (rollSize - firstBitTo) ); //coloca o novo valor no espaзo de memoria que foi limpo
 
    return 0;
}

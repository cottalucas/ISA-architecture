#ifndef __WORD_H__
#define __WORD_H__
 
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
 
 
//macros para permitir compilação cross-platform
#ifndef __LINUX__ //__LINUX__ pode ser definido forcadamente
  #if !defined(__WIN32__) || !defined (_WIN32)
    #define __LINUX__
  #endif
#endif
 
//Tamanho máximo que um endereço de memória pode ter
#define __MEMORY_MAX__ 0x1000
 
 
//tipo __uint40_t
//Tipo de 40 bits sem sinal
//baseado no tipo de 64bits definido em C
typedef uint64_t __uint40_t;
#define __UINT40_MAX__ 0xFFFFFFFFFFL
 
__uint40_t NORMALIZE(uint64_t a); //garantia de 40 bits // L força interpretador a ler como 64 bits
uint32_t LEFT(__uint40_t a);
uint32_t RIGHT(__uint40_t a);
 
//Tipo de 40 bits com sinal
//Implementado como módulo de 2
typedef int64_t __int40_t;
 
//Função INV40(a), retorna o valor inverso de a, ou seja, -a
//O valor é retornado normalizado
__int40_t INV40(__int40_t a); //INV40(a) == -a
//Função ABS40(a), retorna o valor absoluto de a, ou seja, |a|
__int40_t ABS40(__int40_t a); //ABS40(a) == |a|
 
 
//Operações aritméticas e lógicas não precisam ser implementadas
//Basta utilizar NORMALIZE(a+b) por exemplo
//O mesmo é válido para operações de desvio(shift)
//Basta utilizar NORMALIZE(a<<1) ou NORMALIZE(a>>1)
 
//Sinal do __int40_t, esta é a posição binária que representa positivo ou negativo
//0 = positivo, 1 = negativo
#define __INT40_SIGNAL__   0x8000000000L
//Registrador de buffer mecanico
__uint40_t MBR;
__uint40_t MAR;
//funções da UC
void initModule();
 
typedef enum ControlSignals
{
    SIGNAL_NULL,
    SIGNAL_LOAD,
    SIGNAL_LOADABS,
    SIGNAL_LOADNEG,
    SIGNAL_LOADNABS,
    SIGNAL_LOADMQ,
    SIGNAL_LOADMQX,
    SIGNAL_ADD,
    SIGNAL_ADDABS,
    SIGNAL_SUB,
    SIGNAL_SUBABS,
    SIGNAL_MUL,
    SIGNAL_DIV,
    SIGNAL_RSH,
    SIGNAL_LSH
} ControlSignal;
 
 
typedef enum {
    OPCODE_EXIT         = 0x00, //fim de arquivo
    OPCODE_LOAD         = 0x01, // LOAD M(x)
    OPCODE_LOADNEG      = 0x02, // LOAD -M(x)
    OPCODE_LOADABS      = 0x03, // LOAD |M(x)|
    OPCODE_LOADNABS     = 0x04, // LOAD -|M(x)|
 
    OPCODE_ADD          = 0x05, // ADD M(x)
    OPCODE_ADDABS       = 0x06, // ADD |M(x)|
    OPCODE_SUB          = 0x07, // SUB M(x)
    OPCODE_SUBABS       = 0x08, // SUB |M(x)|
    OPCODE_LOADMQX      = 0x09, // LOAD MQ,M(x)
    OPCODE_LOADMQ       = 0x0A, // LOAD MQ
    OPCODE_MUL          = 0x0B, // MUL M(x)
    OPCODE_DIV          = 0x0C, // DIV M(x)
 
    OPCODE_JUMPL        = 0x0D, // JUMP M(x, 0:19)
    OPCODE_JUMPR        = 0x0E, // JUMP M(x, 20:39)
    OPCODE_JUMPLX       = 0x0F, // JUMP+ M(x, 0:19)
    OPCODE_JUMPRX       = 0x10, // JUMP+ M(x, 20:39)
 
    OPCODE_STORE        = 0x11, // STOR M(x)
    OPCODE_STORELPAR    = 0x12, // STOR M(x, 8:19)
    OPCODE_STORERPAR    = 0x13, // STOR M(x, 28:39)
 
    OPCODE_SHIFTLEFT    = 0x14, // LSH
    OPCODE_SHIFTRIGHT   = 0x15, // RSH
    OPCODE_ERROR        = 0xFFFFF  //uso interno
} OperationType;
 
 
#endif // WORD_H_INCLUDED

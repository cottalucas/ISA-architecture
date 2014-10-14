///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
/////// memory.c
/////// Módulo da unidade de controle
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
 
#include "word.h"
#include "memory.h"
#include <stdbool.h>
 
__uint40_t IBR;
__uint40_t IR;
__uint40_t PC;
 
bool forceRightInstruction = false;
bool nextInIBR = false;
 
 
void runExecutionCycle();
 
void initModule()
{
    PC = getFirstOperation(); //primeira operação
    printf("\n");
    printf("Operation: %s");
    while(runExecutionCycle())
    {
        //Este é o "debugger" que irá permitir ao usuário ler o estado de cada registrador
        printf("");
    }
}
 
bool runFetchCycle()
{
    if(nextInIBR){
        IR = IBR & 0x00000000FF; //0-7
        MAR = IBR & 0x00000FFF00; //8-19
        PC++;
        nextInIBR = false;
    }
    else{
        MAR = PC;
        LoadMemoryAddress(MAR);
        if(forceRightInstruction){
            forceRightInstruction = false;
            IR = (MBR & 0x000FF00000) >> 20; //20-27
            MAR = (MBR & 0xFFF0000000) >> 20; //28-39
            PC++;
        }
        else{
            IBR = (MBR & 0xFFFFF00000) >> 20; //20-39
            IR = MBR & 0x00000000FF; //0-7
            MAR = MBR & 0x00000FFF00; //8-19
            nextInIBR = true;
        }
    }
 
    if(IR == 0) return false;
 
    runExecutionCycle();
    return true;
}
 
void runExecutionCycle()
{
    //IR é a instrucao
    //MAR é o parametro
 
    if(IR == OPCODE_STORE || IR == OPCODE_STORELPAR || IR == OPCODE_STORERPAR)
    {
        //LoadAcumulator() //carregar AC em MBR, funcao da ULA
        if(IR == OPCODE_STORE){
            AlterMemoryAddress(MAR, MBR, 40, 0, 0);
        }
        else if(IR == OPCODE_STORELPAR){
            AlterMemoryAddress(MAR, MBR, 12, 28, 8);
        }
        else{ //IR == OPCODE_STORERPAR
            AlterMemoryAddress(MAR, MBR, 12, 28, 28);
        }
    }
    else if(IR == OPCODE_JUMPL || IR == OPCODE_JUMPR || IR == OPCODE_JUMPLX || IR == OPCODE_JUMPRX)
    {
        if(IR == OPCODE_JUMPL || IR == OPCODE_JUMPR /*|| isAcumulatorNonNegative()*/)
        {
            //isAcumulatorNonNegative é funcao da ULA
            PC = MAR;
            if(IR == OPCODE_JUMPR || IR == OPCODE_JUMPRX)
            {
                forceRightInstruction = true;
            }
        }
    }
    else{
        LoadMemoryAddress(MAR);
        uint8_t signal = SIGNAL_NULL;
        switch(IR)
        {
            case OPCODE_LOAD:
                signal = SIGNAL_LOAD;
                break;
            case OPCODE_LOADABS:
                signal = SIGNAL_LOADABS;
                break;
            case OPCODE_LOADNEG:
                signal = SIGNAL_LOADNEG;
                break;
            case OPCODE_LOADNABS:
                signal = SIGNAL_LOADNABS;
                break;
            case OPCODE_LOADMQ:
                signal = SIGNAL_LOADMQ;
                break;
            case OPCODE_LOADMQX:
                signal = SIGNAL_LOADMQX;
                break;
            case OPCODE_ADD:
                signal = SIGNAL_ADD;
                break;
            case OPCODE_ADDABS:
                signal = SIGNAL_ADDABS;
                break;
            case OPCODE_SUB:
                signal = SIGNAL_SUB;
                break;
            case OPCODE_SUBABS:
                signal = SIGNAL_SUBABS;
                break;
            case OPCODE_MUL:
                signal = SIGNAL_MUL;
                break;
            case OPCODE_DIV:
                signal = SIGNAL_DIV;
                break;
            case OPCODE_SHIFTRIGHT:
                signal = SIGNAL_RSH;
                break;
            case OPCODE_SHIFTLEFT:
                signal = SIGNAL_LSH;
                break;
            default:
                printf("ERRO: OPCODE NAO DETECTADO");
                break;
        }
 
        if(signal != SIGNAL_NULL){
            //callArithmeticLogicUnit(signal); //chama a ULA com o parametro carregado
        }
    }
}

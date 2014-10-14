#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "word.h"
 
__uint40_t MBR;
__uint40_t AC;
__uint40_t MQ;
 
 
void inicializaULA();
void printUlaRegs();
 
void inicializaULA() {
    AC = 0;
    MBR = 0;
    MQ = 0;
}
 
void printUlaRegs() {
    printf("ULA:\n");
    printf("   MBR: %010lX\n", MBR);
    printf("    AC: %010lX\n", AC);
    printf("    MQ: %010lX\n", MQ);
}
 
 
void LoadAcumulator(){
    MBR = AC;
}
 
bool isAcumulatorNonNegative(){
if (NEGATIVE(AC))
    return false;
else
    return true;
}
 
void callArithmeticLogicUnit(uint8_t signal){
    LoadMemoryAddress(MAR);    
 
__uint40_t result;
 
    switch(signal)
    {
            case SIGNAL_LOAD:
                AC = MBR;
                break;
             
            case SIGNAL_LOADABS:
                AC = ABS40(MBR);
                break;
             
            case SIGNAL_LOADNEG:
                 AC = INV40(MBR);
                break;
             
            case SIGNAL_LOADNABS:
                AC = INV40(ABS40(MBR));                
                break;
             
            case SIGNAL_LOADMQ:
                AC = MQ;
                break;
             
            case SIGNAL_LOADMQX:
                MQ = MBR;
                break;                          
 
            case SIGNAL_ADD:
                AC += MBR;
                break;
 
            case SIGNAL_ADDABS:
                if(NEGATIVE(MBR))                
                    AC -= ABS40(MBR);
                else
                    AC += ABS40(MBR);
                break;
 
            case SIGNAL_SUB:
                AC -= MBR;
                break;
 
            case SIGNAL_SUBABS:
                if(NEGATIVE(MBR))                
                    AC += ABS40(MBR);
                else
                    AC -= ABS40(MBR);                
                break;
 
            case SIGNAL_MUL:
            {
                if(NEGATIVE(MBR) && !NEGATIVE(MQ) || !NEGATIVE(MBR) && NEGATIVE(MQ)){
                    result = INV40(ABS40(MBR) * ABS40(MQ));
                    MQ = ABS40(result);
                    result >>= 40;
                    AC = result;
                }
                else{
                    result = ABS40(MBR) * ABS40(MQ);
                    MQ = ABS40(result);
                    result >>= 40;
                    AC = result;
                }
            }
                break;
 
            case SIGNAL_DIV:
            {
                if(NEGATIVE(MBR) && !NEGATIVE(MQ) || !NEGATIVE(MBR) && NEGATIVE(MQ)){
                    AC = ABS40(AC)%ABS40(MBR);                  
                    MQ = INV40(ABS40(AC) / ABS40(MBR));
                }               
                else{
                    AC = ABS40(AC)%ABS40(MBR);                  
                    MQ = (ABS40(AC) / ABS40(MBR));
                }
            }                
                break;
 
            case SIGNAL_LSH:
                AC <<= 1;
            break;            
 
            case SIGNAL_RSH:
                AC >>= 1;
                break;
 
            default:
                printf("ERRO: OPCODE NAO DETECTADO");
                break;
        }
 
 
         
}

///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
/////// word.c
/////// Definiушes de funушes gerais
/////// relacionadas com __uint40_t
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
 
#include "word.h"
 
__uint40_t NORMALIZE(uint64_t a){
    a &= __INT40_SIGNAL__-1; //Isto forуa 39 bits do nЩmero a serem "salvos"
    //O sinal ж tratado separadamente
    if(a < 0){
        a |= __INT40_SIGNAL__;
    }
     return a;
}
 
//Funусo INV40(a), retorna o valor inverso de a, ou seja, -a
//O valor ж retornado normalizado
__int40_t INV40(__int40_t a){ return  a ^ __INT40_SIGNAL__ ; } //Inverter sinal utilizando XOR; se sinal = 1 vira 0, se sinal = 0 vira 1
//Funусo ABS40(a), retorna o valor absoluto de a, ou seja, |a|
__int40_t ABS40(__int40_t a){ return a & ~__INT40_SIGNAL__ ; } //Remove sinal
 
bool NEGATIVE(__int40_t a) {
    if(a & __INT40_SIGNAL__){
        return true;
    }
    return false;
}

///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
// Arquivo main.c
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
 
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "word.h"
 
//Macro PRINT_ERROR(msg)
//Deve ser utilizado dentro da função main
//o argumento msg é igual ao argumento de printf
#define PRINT_ERROR(msg) {printf(msg); return EXIT_FAILURE;}
///////////////////////////////////////
 
 
typedef enum ProgramModes {
    MODE_NULL,
    MODE_AJUDA,
    MODE_TRADUZIR,
    MODE_INTERPRETAR
} ProgramMode;
 
ProgramMode pMode = MODE_NULL;
 
void lowercase(char* str)
{
    int i;
    for (i=0; str[i] != '\0'; i++)
        str[i] = tolower(str[i]);
}
 
int stringToOpcode(const char* line)
{
    OperationType operation;
    char cpy[25];
    char *pch, *param = NULL, *param2 = NULL;
    strcpy(cpy, line);
    lowercase(cpy);
 
 
    if(strncmp(cpy, "load", 4) == 0)
    {
        if(strtok(cpy, " ") == NULL)
            return OPCODE_ERROR;
 
        //Funções tipo LOAD:
        //LOAD M(x)
        //LOAD |M(x)|
        //LOAD -M(x)
        //LOAD -|M(x)|
        //LOAD MQ,M(x)
        //LOAD MQ
        pch = strtok(NULL, " ");
        if(pch == NULL) return OPCODE_ERROR;
 
        if(pch[0] == '-'){
            //LOAD -
            if(pch[1] == '|'){
                operation = OPCODE_LOADNABS; //LOAD -|M(x)|
                param = strtok(pch, "-|m()|");
            }
            else{
                operation = OPCODE_LOADNEG; // LOAD -M(x)
                param = strtok(pch, "-m()");
            }
        }
        else if(pch[0] == '|'){
                operation = OPCODE_LOADABS; //LOAD |M(x)|
                param = strtok(pch, "|m()|");
        }
        else{ //LOAD M---
            if(pch[1] == 'q'){ //LOAD MQ
                param = strtok(pch, "mq,m()");
                if(param != NULL) operation = OPCODE_LOADMQX; //LOAD MQ,M(x)
                else operation = OPCODE_LOADMQ;
            }
            else{ //LOAD M(x)
                param = strtok(pch, "m()");
                operation = OPCODE_LOAD;
            }
        }
    }
    else if(strncmp(cpy, "add", 3) == 0)
    {
        if(strtok(cpy, " ") == NULL)
            return OPCODE_ERROR;
 
        //Funções tipo ADD:
        //ADD M(x)
        //ADD |M(x)
        pch = strtok(NULL, " ");
        if(pch == NULL) return OPCODE_ERROR;
 
        if(pch[0] == '|'){
            operation = OPCODE_ADDABS; //ADD |M(x)|
            param = strtok(pch, "|m()|");
        }
        else{
            operation = OPCODE_ADD;
            param = strtok(pch, "m()");
        }
    }
    else if(strncmp(cpy, "sub", 3) == 0)
    {
        if(strtok(cpy, " ") == NULL)
            return OPCODE_ERROR;
 
        //Funções tipo SUB:
        //SUB M(x)
        //SUB |M(x)
        pch = strtok(NULL, " ");
        if(pch == NULL) return OPCODE_ERROR;
 
        if(pch[0] == '|'){
            operation = OPCODE_SUBABS; //SUB |M(x)|
            param = strtok(pch, "|m()|");
        }
        else{
            operation = OPCODE_SUB;
            param = strtok(pch, "m()");
        }
    }
    else if(strncmp(cpy, "mul", 3) == 0)
    {
        if(strtok(cpy, " ") == NULL)
            return OPCODE_ERROR;
 
        pch = strtok(NULL, " ");
        if(pch == NULL) return OPCODE_ERROR;
 
        operation = OPCODE_MUL;
        param = strtok(pch, "m()");
    }
    else if(strncmp(cpy, "div", 3) == 0)
    {
        if(strtok(cpy, " ") == NULL)
            return OPCODE_ERROR;
 
        pch = strtok(NULL, " ");
        if(pch == NULL) return OPCODE_ERROR;
 
        operation = OPCODE_DIV;
        param = strtok(pch, "m()");
    }
    else if(strncmp(cpy, "jump", 4) == 0)
    {
        if(strtok(cpy, " ") == NULL)
            return OPCODE_ERROR;
 
        pch = strtok(NULL, " ");
        if(pch == NULL) return OPCODE_ERROR;
 
        param2 = strtok(NULL, " "); // A ordem importa aqui
        param = strtok(pch, "m(, )");
        if(param2[0] == '0')
        {
            if(cpy[4] == '+')
                operation = OPCODE_JUMPLX;
            else
                operation = OPCODE_JUMPL;
        }
        else{
            if(cpy[4] == '+')
                operation = OPCODE_JUMPRX;
            else
                operation = OPCODE_JUMPR;
        }
    }
    else if(strncmp(cpy, "stor", 4) == 0)
    {
        if(strtok(cpy, " ") == NULL)
            return OPCODE_ERROR;
 
        pch = strtok(NULL, " ");
        if(pch == NULL) return OPCODE_ERROR;
 
        param2 = strtok(NULL, ",");
        param = strtok(pch, "m()");
        if(param2 != NULL)
        {
            if(param2[0] == '8')
                operation = OPCODE_STORELPAR;
            else
                operation = OPCODE_STORERPAR;
        }
        else
            operation = OPCODE_STORE;
    }
    else if(strncmp(cpy, "lsh", 3) == 0)
        operation = OPCODE_SHIFTLEFT;
    else if(strncmp(cpy, "rsh", 3) == 0)
        operation = OPCODE_SHIFTRIGHT;
    else
        operation = OPCODE_EXIT;
 
 
    int parameter;
    if(param != NULL) parameter = atoi(param);
    else parameter = 0x00000;
    return (operation << 12) + (parameter & 0x00000FFF); //12 bits da direita do parametro + 8 bits da operacao
}
 
void translateFile(FILE* ias)
{
    //Ler linhas
    //enquanto nao encontrar uma instruçao, cada linha é 1 memoria
    //ao encontrar uma instruçao, cada 2 linhas é 1 memoria
 
    //seja n a linha da primeira instrucao
    //n e n+1 sao a memoria n
    //n+2 e n+3 sao a memoria n+1
    //etc
    //n+(a/2) é o valor da memoria, onde a%2 determina o lado(0=esq, 1=dir)
 
    //as primeiras linhas serão instruções, enquanto as últimas serão memórias
    //dividido pela instrução 00000
 
    /* Exemplo programa IAS:
    10
    23
    29
    0xFA
    .text
    Load M(1)
    Add M(2)
    Sub M(3)
    Stor M(4)
 
    Saída:
    <load m(1)><add m(2)>
    <sub m(3)><stor m(4)>
    <end>
    0000000A
    00000017
    0000001D
    000000FA
    */
 
    char c[42];
    uint16_t line = 0;
    uint16_t firstOp = 0;
    bool operations = false;
    __int40_t lineValue;
    __int40_t  valores[__MEMORY_MAX__];
 
    FILE* hex = fopen("translated.hex", "w"); //TODO: salvar como <arquivo>.hex ou dar a opcao de nomear
    if(!hex)
        return; //erro: nao conseguiu criar o arquivo achou o arquivo. TODO: tratar
 
    do
    {
        if( fgets(c, 42, ias) != NULL) //transforma linha em string
        {
            char *f;
            lineValue = NORMALIZE( strtoll(c, &f, 0) ); //64 -> 40 bits
 
            if(f[0] == c[0] && !operations)
            {
                operations = true;
                firstOp = line;
            }
 
            if(!operations)
            {
                valores[line] = lineValue;
            }
            else
            {
                int operation = stringToOpcode(c);
                OperationType opcode = (operation & 0x000FF000)>>12;
                int param = operation & 0x00000FFF;
                switch(opcode)
                {
                case OPCODE_ERROR:
                    return; //
 
                case OPCODE_EXIT:
                    break;
 
                case OPCODE_STORERPAR:
                case OPCODE_STORELPAR:
                case OPCODE_JUMPL:
                case OPCODE_JUMPLX:
                case OPCODE_JUMPR:
                case OPCODE_JUMPRX:
                {
                    if(param >= firstOp)
                    {
                        int newLine = param - firstOp;
                        param = (int)(newLine/2);
 
                    }
                    else{
                        param += firstOp/2;
                    }
                    operation = (opcode<<12) | param;
                }
                break;
 
                default:
                    break;
                }
 
                if((line-firstOp) % 2 == 0)
                    fprintf(hex, "%.5X", operation);
                else
                    fprintf(hex, "%.5X\n", operation);
            }
 
            line++;
        }
    }
    while(!feof(ias));
    fprintf(hex, "0000000000\n");
 
    //Imprimir memórias
    int i ;
    for(i = 0; i < firstOp; ++i){
        fprintf(hex, "%.10llX\n", valores[i]);
    }
 
    fclose(hex);
}
 
int main(int argc, char** argv)
{
 
    //argc = número de argumentos ao chamar o programa
    //argv = lista de strings destes argumentos
    //argv[0] = nome do programa
 
    //possíveis comandos:
    // /?: mostra a lista de ajuda
    // /t: força modo tradução
    //(abre o ultimo argumento como arquivo e traduz para .hex)
 
    // /i: força modo interpretação
    //(abre o ultimo argumento como arquivo e simula o processador)
 
    // etc
 
    int c;
    opterr = 0;
    //char* svalue = NULL;
    while( (c = getopt(argc, argv, "ti")) != -1 )
    {
        switch(c)
        {
            case 't':
                pMode = (pMode == MODE_NULL? MODE_TRADUZIR : MODE_AJUDA);
                break;
 
            case 'i':
                pMode = (pMode == MODE_NULL? MODE_INTERPRETAR : MODE_AJUDA);
                break;
 
 
            case '?':
            default:
                pMode = MODE_AJUDA;
                break;
        }
    }
 
 
    switch(pMode)
    {
        case MODE_TRADUZIR:
        {
            FILE *ias = fopen(argv[optind], "r");
            if(ias == NULL)
                PRINT_ERROR("Could not open file!");
 
            translateFile(ias);
            break;
        }
 
        case MODE_INTERPRETAR:
        {
            FILE *hex = fopen(argv[optind], "r");
            if(hex == NULL)
                PRINT_ERROR("Could not open file!");
 
            if(loadMemory(hex) == -1)
                PRINT_ERROR("Could not open file!");
 
                initModule();
 
            break;
        }
 
        case MODE_AJUDA:
        default:
        {
            printf("Este programa permite os seguintes argumentos:\n");
            printf("-[i | t]  arquivo\n");
            printf("-i: Modo de interpretação. Abre o arquivo pra interpretar\n");
            printf("-t: Modo de tradução. Abre o arquivo IAS e reescreve em HEX\n");
            printf("-?: Modo de ajuda. Escreve esta tela.");
            break;
        }
    }
 
 
    return (EXIT_SUCCESS);
}

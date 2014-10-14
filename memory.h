#ifndef __MEMORY_H__
#define __MEMORY_H__
 
#include "word.h"
#include <stdlib.h>
 
int getFirstOperation();
int loadMemory(FILE* stream);
int LoadMemoryAddress(int addr);
int AlterMemoryAddress(int addr, __uint40_t value, int range, int firstBitFrom, int firstBitTo);
 
 
#endif // MEMORY_H_INCLUDED

#include <iostream>
#include <string>

#include "LongArithmetic.h"

unsigned int* MuCalculus(std::string& modString, int bitRate, long long modSize, long long& muSize);

unsigned int* BarrettReduction(unsigned int* number, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberSize, long long modSize, long long muSize, long long& remainderSize);

unsigned int* ModAdd(unsigned int* numberA, unsigned int* numberB, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberASize, long long numberBSize, long long modSize, long long muSize, long long& remainderSize);

unsigned int* ModSub(unsigned int* numberA, unsigned int* numberB, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberASize, long long numberBSize, long long modSize, long long muSize, long long& remainderSize);

unsigned int* ModMul(unsigned int* numberA, unsigned int* numberB, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberASize, long long numberBSize, long long modSize, long long muSize, long long& remainderSize);

unsigned int* ModPow(unsigned int* numberA, std::string& numberB, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberASize, long long numberBSize, long long modSize, long long muSize, long long& remainderSize);
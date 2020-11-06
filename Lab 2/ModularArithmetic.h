#include <iostream>
#include <string>

#include "LongArithmetic.h"

unsigned int* MuCalculus(std::string& modString, int bitRate, long long modSize, long long& muSize);

unsigned int* BarrettReduction(unsigned int* number, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberSize, long long modSize, long long muSize, long long& remainderSize);


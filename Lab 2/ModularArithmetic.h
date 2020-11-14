#include <iostream>
#include <string>

#include "LongArithmetic.h"

void KillLastDigits(bigInteger* number, long long count);

bigInteger* MuCalculus(bigInteger* mod, int bitRate);
bigInteger* BarrettReduction(bigInteger* number, bigInteger* mod, bigInteger* bigMu, int bitRate);

bigInteger* ModAdd(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);
bigInteger* ModSub(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);
bigInteger* ModMul(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);
bigInteger* ModPow(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);

bigInteger* GreatCommonDivisor(bigInteger* numberA, bigInteger* numberB, int bitRate);
bigInteger* LeastCommonMultiple(bigInteger* numberA, bigInteger* numberB, bigInteger* greatCommonDivisor, int bitRate);
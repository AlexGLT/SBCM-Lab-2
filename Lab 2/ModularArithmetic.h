#include <iostream>
#include <string>

#include "LongArithmetic.h"

void KillLastDigits(bigInteger* number, int count);

bigInteger* MuCalculus(bigInteger* mod, int bitRate);
bigInteger* BarrettReduction(bigInteger* number, bigInteger* mod, bigInteger* bigMu, int bitRate);

bigInteger* ModAdd(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);
bigInteger* ModSub(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);
bigInteger* ModMul(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);
bigInteger* ModPow(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate);
#include <iostream>
#include <string>

#include "LongArithmetic.h"

void KillLastDigits(std::shared_ptr<bigInteger> number, long long count);

std::shared_ptr<bigInteger> MuCalculus(std::shared_ptr<bigInteger> mod, int bitRate);
std::shared_ptr<bigInteger> BarrettReduction(std::shared_ptr<bigInteger> number, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate);

std::shared_ptr<bigInteger> ModAdd(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate);
std::shared_ptr<bigInteger> ModSub(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate);
std::shared_ptr<bigInteger> ModMul(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate);
std::shared_ptr<bigInteger> ModPow(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate);

std::shared_ptr<bigInteger> GreatCommonDivisor(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, int bitRate);
std::shared_ptr<bigInteger> LeastCommonMultiple(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> greatCommonDivisor, int bitRate);
#include <iostream>

#include "ModularArithmetic.h"

unsigned int* MuCalculus(std::string& modString, int bitRate, long long modSize, long long& muSize)
{
	long long calculusBaseSize = 2 * modSize + 1;

	auto* calculusBase = new unsigned int[calculusBaseSize];
	std::fill(&calculusBase[0], &calculusBase[calculusBaseSize], 0);
	calculusBase[0] = 1;
	std::string* calculusBaseString = toHexConverting(calculusBase, bitRate, calculusBaseSize);

	long long temp;
	long long wholePartLength;
	unsigned int* mu = LongDiv(*calculusBaseString, modString, bitRate, wholePartLength, temp)[0];

	std::string muTemp = *toHexConverting(mu, 1, wholePartLength);

	unsigned int* bigMu = toBigIntConverting(muTemp, bitRate, muSize);

	return bigMu;
}

unsigned int* BarrettReduction(unsigned int* number, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberSize, long long modSize, long long muSize, long long& remainderSize)
{
	long long newNumberSize = 2 * modSize;
	auto* newNumber = new unsigned int[newNumberSize];

	std::fill(&newNumber[0], &newNumber[newNumberSize - numberSize], 0);
	std::copy(number, number + numberSize, newNumber + newNumberSize - numberSize);

	long long qSize = newNumberSize - modSize + 1;
	auto* q = new unsigned int[qSize];
	
	std::fill(&q[0], &q[qSize], 0);
	std::copy(newNumber, newNumber + qSize, q);

	q = LongMul(q, bigMu, bitRate, qSize, muSize, qSize);

	long long q_1Size = qSize - modSize - 1;
	auto* q_1 = new unsigned int[q_1Size];

	std::fill(&q_1[0], &q_1[q_1Size], 0);
	std::copy(q, q + q_1Size, q_1);

	long long wholePartSize;
	unsigned int* wholePart = LongMul(q_1, mod, bitRate, q_1Size, modSize, wholePartSize);

	unsigned int* modRemainder = LongSub(number, wholePart, bitRate, numberSize, wholePartSize, remainderSize);

	while (LongComp(modRemainder, mod, remainderSize, modSize, false))
	{
		modRemainder = LongSub(modRemainder, mod, bitRate, remainderSize, modSize, remainderSize);
	}

	return modRemainder;
}

unsigned int* ModAdd(unsigned int* numberA, unsigned int* numberB, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberASize, long long numberBSize, long long modSize, long long muSize, long long& remainderSize)
{
	long long numberCSize;

	unsigned int* numberC = LongAdd(numberA, numberB, bitRate, numberASize, numberBSize, numberCSize);

	unsigned int* modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate, numberCSize, modSize, muSize, remainderSize);

	return modRemainder;
}

unsigned int* ModSub(unsigned int* numberA, unsigned int* numberB, unsigned int* mod, unsigned int* bigMu, int bitRate, long long numberASize, long long numberBSize, long long modSize, long long muSize, long long& remainderSize)
{
	long long numberCSize;

	unsigned int* numberC = LongSub(numberA, numberB, bitRate, numberASize, numberBSize, numberCSize);

	unsigned int* modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate, numberCSize, modSize, muSize, remainderSize);

	return modRemainder;
}
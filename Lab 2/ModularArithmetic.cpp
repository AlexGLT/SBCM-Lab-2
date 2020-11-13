#include <iostream>

#include "ModularArithmetic.h"

void KillLastDigits(bigInteger* number, long long count)
{
	long long newNumberSize = number->size - count;
	auto* newNumberValue = new unsigned int[newNumberSize];

	std::copy(number->value, number->value + newNumberSize, newNumberValue);

	delete[] number->value;
	number->value = NULL;

	number->size = newNumberSize;
	number->value = newNumberValue;
}

bigInteger* MuCalculus(bigInteger* mod, int bitRate)
{
	auto* calculusBase = new bigInteger(2 * mod->size + 1);
	
	std::fill(&calculusBase->value[1], &calculusBase->value[calculusBase->size], 0);
	calculusBase->value[0] = 1;

	toHexConverting(calculusBase, bitRate);

	auto* mu = LongDiv(calculusBase, mod, bitRate)[0];

	freeMemory(1, calculusBase);

	auto* bigMu = toBigIntConverting(mu->hexString, bitRate);

	freeMemory(1, mu);

	return bigMu;
}

bigInteger* BarrettReduction(bigInteger* number, bigInteger* mod, bigInteger* bigMu, int bitRate)
{
	auto* wholePart = new bigInteger(2 * mod->size);

	std::fill(&wholePart->value[0], &wholePart->value[wholePart->size - number->size], 0);
	std::copy(number->value, number->value + number->size, wholePart->value + wholePart->size - number->size);

	KillLastDigits(wholePart, mod->size - 1);

	wholePart = LongMul(wholePart, bigMu, bitRate, false, 1);

	KillLastDigits(wholePart, mod->size + 1);

	auto* subtractor = LongMul(wholePart, mod, bitRate, false);
	
	freeMemory(1, wholePart);

	auto* remainder = LongSub(number, subtractor, bitRate, false);

	freeMemory(1, subtractor);

	while (LongComp(remainder, mod, false))
	{
		remainder = LongSub(remainder, mod, bitRate, false, 1);
	}

	return remainder;
}

bigInteger* ModAdd(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate)
{
	auto* numberC = LongAdd(numberA, numberB, bitRate, false);

	auto* modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	freeMemory(1, numberC);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

bigInteger* ModSub(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate)
{
	auto* numberC = LongSub(numberA, numberB, bitRate, false);

	auto* modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	freeMemory(1, numberC);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

bigInteger* ModMul(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate)
{
	auto* numberC = LongMul(numberA, numberB, bitRate, false);

	auto* modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	freeMemory(1, numberC);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

bigInteger* ModPow(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate)
{
	auto* bitNumberB = toBigIntConverting(numberB->hexString, 1);

	auto* modRemainder = new bigInteger();
	modRemainder->value[0] = static_cast<unsigned int>(1);

	auto* changedNumberA = numberA;

	for (long long i = bitNumberB->size - 1; i >= 0; i--)
	{
		if (bitNumberB->value[i] == 1)
		{
			auto* tempC = LongMul(modRemainder, changedNumberA, bitRate, false);
			
			modRemainder = BarrettReduction(tempC, mod, bigMu, bitRate);

			freeMemory(1, tempC);
		}

		auto* tempA = LongMul(changedNumberA, changedNumberA, bitRate, false);
		
		if (changedNumberA != numberA)
		{
			freeMemory(1, changedNumberA);
		}

		changedNumberA = BarrettReduction(tempA, mod, bigMu, bitRate);

		freeMemory(1, tempA);
	}

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}
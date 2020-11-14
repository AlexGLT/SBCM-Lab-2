#include <iostream>
#include <memory>

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

	auto bigMu = LongDiv(calculusBase, mod, bitRate, true)->first;

	freeMemory(calculusBase);

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
	
	freeMemory(wholePart);

	auto* remainder = LongSub(number, subtractor, bitRate, false);

	freeMemory(subtractor);

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

	freeMemory(numberC);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

bigInteger* ModSub(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate)
{
	auto* numberC = LongSub(numberA, numberB, bitRate, false);

	auto* modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	freeMemory(numberC);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

bigInteger* ModMul(bigInteger* numberA, bigInteger* numberB, bigInteger* mod, bigInteger* bigMu, int bitRate)
{
	auto* numberC = LongMul(numberA, numberB, bitRate, false);

	auto* modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	freeMemory(numberC);

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

			freeMemory(tempC);
		}

		auto* tempA = LongMul(changedNumberA, changedNumberA, bitRate, false);
		
		if (changedNumberA != numberA)
		{
			freeMemory(changedNumberA);
		}

		changedNumberA = BarrettReduction(tempA, mod, bigMu, bitRate);

		freeMemory(tempA);
	}

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

bigInteger* GreatCommonDivisor(bigInteger* numberA, bigInteger* numberB, int bitRate)
{
	auto* bitGreatCommonDivisor = new bigInteger(1);
	bitGreatCommonDivisor->value[0] = static_cast<unsigned int>(1);

	auto* two = new bigInteger(1, "2");
	two->value[0] = static_cast<unsigned int>(2);

	auto* tempA = toBigIntConverting(numberA->hexString, 1);
	auto* tempB = toBigIntConverting(numberB->hexString, 1);
	ZeroEraser(tempA);
	ZeroEraser(tempB);

	int count = 0;

	for (int i = 0; true; i++)
	{
		if ((tempA->size != 1) && (tempB->size != 1) && (tempA->value[tempA->size - i - 1] == 0) && (tempB->value[tempB->size - i - 1] == 0))
		{
			count++;
		}
		else
			break;
	}
	
	if (count != 0)
	{
		KillLastDigits(tempA, count);
		KillLastDigits(tempB, count);

		bitGreatCommonDivisor = LongShiftBitsToHigh(bitGreatCommonDivisor, count, true);

		count = 0;
	}

	SmallFix(bitGreatCommonDivisor);
	toHexConverting(bitGreatCommonDivisor, 1);

	for (int i = 0; true; i++)
	{
		if ((tempA->size != 1) && (tempA->value[tempA->size - i - 1] == 0))
		{
			count++;
		}
		else
			break;
	}

	if (count != 0)
	{
		KillLastDigits(tempB, count);

		count = 0;
	}


	while ((tempB->size != 1) || (tempB->value[0] != 0))
	{
		for (int i = 0; true; i++)
		{
			if ((tempB->size != 1) && (tempB->value[tempB->size - i - 1] == 0))
			{
				count++;
			}
			else
				break;
		}

		if (count != 0)
		{
			KillLastDigits(tempB, count);
			

			count = 0;
		}

		auto* difference = LongSub(tempA, tempB, 1, false);

		if (difference->size == 1 && difference->value[0] == 0)
		{
			freeMemory(difference);
			difference = LongSub(tempB, tempA, 1, false);
		}

		switch (LongComp(tempA, tempB, false))
		{
		case true: 
			freeMemory(tempA); 
			tempA = tempB;
			tempB = difference;
			
			ZeroEraser(tempA);
			ZeroEraser(tempB);
			break;
		case false: 
			freeMemory(tempB); 
			tempB = difference;
			
			ZeroEraser(tempB);
			break;
		}
	}

	tempA->hexString = "";
	SmallFix(tempA);
	toHexConverting(tempA, 1);
	auto* multiplier = toBigIntConverting(tempA->hexString, bitRate);
	
	auto* greatCommonDivisor = toBigIntConverting(bitGreatCommonDivisor->hexString, bitRate);

	greatCommonDivisor = LongMul(greatCommonDivisor, multiplier, bitRate, true, 1);

	return greatCommonDivisor;
}

bigInteger* LeastCommonMultiple(bigInteger* numberA, bigInteger* numberB, bigInteger* greatCommonDivisor, int bitRate)
{
	auto* multiplication = LongMul(numberA, numberB, bitRate);

	auto leastCommonMultiple = LongDiv(multiplication, greatCommonDivisor, bitRate, true)->first;

	freeMemory(multiplication);

	return leastCommonMultiple;
}
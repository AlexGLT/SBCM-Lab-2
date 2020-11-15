#include <iostream>

#include "ModularArithmetic.h"

std::shared_ptr<bigInteger> MuCalculus(std::shared_ptr<bigInteger> mod, int bitRate)
{
	auto calculusBase = std::make_shared<bigInteger>(2 * mod->size + 1);
	
	std::fill(&calculusBase->value[1], &calculusBase->value[calculusBase->size], 0);
	calculusBase->value[0] = 1;

	toHexConverting(calculusBase, bitRate);

	auto bigMu = LongDiv(calculusBase, mod, bitRate, true)->first;

	return bigMu;
}

std::shared_ptr<bigInteger> BarrettReduction(std::shared_ptr<bigInteger> number, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate)
{
	auto wholePart = std::make_shared<bigInteger>(2 * mod->size);

	std::fill(&wholePart->value[0], &wholePart->value[wholePart->size - number->size], 0);
	std::copy(number->value, number->value + number->size, wholePart->value + wholePart->size - number->size);

	wholePart = LongShiftBits(wholePart, 1 - mod->size);

	wholePart = LongMul(wholePart, bigMu, bitRate, false);

	wholePart = LongShiftBits(wholePart, -1 - mod->size);

	auto subtractor = LongMul(wholePart, mod, bitRate, false);

	auto remainder = LongSub(number, subtractor, bitRate, false);

	while (LongComp(remainder, mod, false))
	{
		remainder = LongSub(remainder, mod, bitRate, false);
	}

	return remainder;
}

std::shared_ptr<bigInteger> ModAdd(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate)
{
	auto numberC = LongAdd(numberA, numberB, bitRate, false);

	auto modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

std::shared_ptr<bigInteger> ModSub(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate)
{
	auto numberC = LongSub(numberA, numberB, bitRate, false);

	auto modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

std::shared_ptr<bigInteger> ModMul(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate)
{
	auto numberC = LongMul(numberA, numberB, bitRate, false);

	auto modRemainder = BarrettReduction(numberC, mod, bigMu, bitRate);

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

std::shared_ptr<bigInteger> ModPow(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> mod, std::shared_ptr<bigInteger> bigMu, int bitRate)
{
	auto bitNumberB = toBigIntConverting(numberB->hexString, 1);

	auto modRemainder = toBigIntConverting("1", bitRate);

	auto changedNumberA = numberA;

	for (long long i = bitNumberB->size - 1; i >= 0; i--)
	{
		if (bitNumberB->value[i] == 1)
		{
			modRemainder = BarrettReduction(LongMul(modRemainder, changedNumberA, bitRate, false), mod, bigMu, bitRate);
		}

		auto tempA = LongMul(changedNumberA, changedNumberA, bitRate);

		changedNumberA = BarrettReduction(tempA, mod, bigMu, bitRate);
	}

	toHexConverting(modRemainder, bitRate);

	return modRemainder;
}

std::shared_ptr<bigInteger> GreatCommonDivisor(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, int bitRate)
{
	auto bitGreatCommonDivisor = toBigIntConverting("1", bitRate);

	auto tempA = toBigIntConverting(numberA->hexString, 1);
	ZeroEraser(tempA);

	auto tempB = toBigIntConverting(numberB->hexString, 1);
	ZeroEraser(tempB);

	int count = 0;

	for (int i = 0; true; i++)
	{
		if ((tempA->size != 1) && (tempB->size != 1) && (tempA->value[tempA->size - i - 1] == 0) && (tempB->value[tempB->size - i - 1] == 0))
		{
			count++;
		}
		else
		{
			break;
		}
	}
	
	if (count != 0)
	{
		tempA = LongShiftBits(tempA, -count);
		tempB = LongShiftBits(tempB, -count);

		bitGreatCommonDivisor = LongShiftBits(bitGreatCommonDivisor, count);

		SmallFix(bitGreatCommonDivisor);
		toHexConverting(bitGreatCommonDivisor, 1);

		count = 0;
	}

	for (int i = 0; true; i++)
	{
		if ((tempA->size != 1) && (tempA->value[tempA->size - i - 1] == 0))
		{
			count++;
		}
		else
		{
			break;
		}
	}

	if (count != 0)
	{
		tempB = LongShiftBits(tempB, -count);

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
			{
				break;
			}
		}

		if (count != 0)
		{
			tempB = LongShiftBits(tempB, -count);

			count = 0;
		}

		auto difference = LongSub(tempA, tempB, 1, false);

		if (difference->size == 1 && difference->value[0] == 0)
		{
			difference = LongSub(tempB, tempA, 1, false);
		}

		std::shared_ptr<bigInteger> minimum;

		if (LongComp(tempA, tempB, false))
		{
			minimum = tempB;
		}
		else
		{
			minimum = tempA;
		}

		ZeroEraser(difference);

		tempA = minimum;
		tempB = difference;
	}

	SmallFix(tempA);
	toHexConverting(tempA, 1);
	
	auto multiplier = toBigIntConverting(tempA->hexString, bitRate);
	
	auto greatCommonDivisor = toBigIntConverting(bitGreatCommonDivisor->hexString, bitRate);

	greatCommonDivisor = LongMul(greatCommonDivisor, multiplier, bitRate, true);

	return greatCommonDivisor;
}

std::shared_ptr<bigInteger> LeastCommonMultiple(std::shared_ptr<bigInteger> numberA, std::shared_ptr<bigInteger> numberB, std::shared_ptr<bigInteger> greatCommonDivisor, int bitRate)
{
	auto multiplication = LongMul(numberA, numberB, bitRate);

	auto leastCommonMultiple = LongDiv(multiplication, greatCommonDivisor, bitRate, true)->first;

	return leastCommonMultiple;
}
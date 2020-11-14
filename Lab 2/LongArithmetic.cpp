#include <iostream>
#include <climits>
#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include "LongArithmetic.h"

bigInteger::bigInteger()
{
	size = 1;
	value = new unsigned int[1]{ 0 };
	hexString = "0";
}

bigInteger::bigInteger(const long long& size)
{
	this->size = size;
	hexString = "";
	value = new unsigned int[size];
}

bigInteger::bigInteger(const long long& size, const std::string& hexString)
{
	this->size = size;
	this->hexString = hexString;
	value = new unsigned int[size];
}

bigInteger::~bigInteger()
{
	delete[] value;
	value = nullptr;
}

// For debugging
void showBigInteger(bigInteger* number, std::string numberName)
{
	std::cout << numberName << ": " << std::endl;

	std::cout << "|";

	for (int i = 0; i < number->size; i++)
	{
		std::cout << number->value[i] << "|";
	}

	std::cout << std::endl;
}

void freeMemory(bigInteger* number, bool selfReculc)
{
	if (selfReculc)
	{
		delete number;
		number = nullptr;
	}
}

void ZeroEraser(bigInteger* number)
{
	unsigned int zeroCount = 0;

	for (int i = 0; i < number->size; i++)
	{
		if (number->value[i] == 0)
		{
			zeroCount++;
		}
		else
		{
			break;
		}
	}

	if (number->size - zeroCount == 0)
	{
		zeroCount--;
	}

	if (zeroCount != 0)
	{
		long long newSize = number->size - zeroCount;

		auto* optimizedNumberValue = new unsigned int[newSize];
		std::fill(&optimizedNumberValue[0], &optimizedNumberValue[newSize], 0);
		std::copy(number->value + zeroCount, number->value + number->size, optimizedNumberValue);
		
		delete[] number->value;
		number->value = nullptr;

		number->size = newSize;
		number->value = optimizedNumberValue;
	}
}

bigInteger* toBigIntConverting(std::string number, const int& bitRate)
{
	long long numberSize = number.length();

	bigInteger* bigNumber = new bigInteger();

	if (bitRate >= 4)
	{
		std::string fixedNumber = number;
		int hexBitCount = (bitRate / 4);

		if (numberSize % hexBitCount != 0)
		{
			std::string nullptrStr;

			for (int i = hexBitCount - (numberSize % hexBitCount); i > 0; i--)
			{
				nullptrStr += "0";
				numberSize++;
			}

			fixedNumber = nullptrStr + number;
		}

		bigNumber = new bigInteger(numberSize / hexBitCount, number);

		for (long long i = bigNumber->size - 1; i >= 0; i--)
		{
			bigNumber->value[i] = strtoul(fixedNumber.substr(i * hexBitCount, hexBitCount).c_str(), nullptr, 16);
		}
	}
	else
	{
		//count of big bits for one hex cipher
		int bitForHexCount = (4 >> (bitRate - 1));

		bigNumber = new bigInteger(numberSize * bitForHexCount, number);

		for (int i = numberSize - 1; i >= 0; i--)
		{
			int numberHexBit = strtoul(number.substr(i, 1).c_str(), nullptr, 16);

			for (int j = bitForHexCount - 1; j >= 0; j--)
			{
				bigNumber->value[i * bitForHexCount + j] = (numberHexBit >> (3 - j)) & 1;
			}
		}

		ZeroEraser(bigNumber);
	}

	return bigNumber;
}

void toHexConverting(bigInteger* bigNumber, int bitRate)
{
	for (long long i = 0; i < bigNumber->size; i++)
	{
		int binSum = 0;
		std::vector<int> smallNumber;

		if (bitRate >= 4)
		{
			for (int j = 0; j < bitRate; j += 4)
			{
				smallNumber.push_back((bigNumber->value[i] >> ((bitRate - 4) - j)) & 15);
			}
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				binSum += bigNumber->value[i + j] << (3 - j);
			}


			// Перескочити 4 значення масиву, але добавляємо 3, оскільки в ітераторі вже є i++
			i += 3;

			smallNumber.push_back(binSum);
		}

		for (int j = 0; j < smallNumber.size(); j++)
		{
			int cipher = smallNumber[j];

			if (cipher > 9)
			{
				cipher += 55;
			}
			else
			{
				cipher += 48;
			}

			bigNumber->hexString += static_cast<char>(cipher);
		}

		smallNumber.clear();
	}

	short zeroCount = 0;

	for (short i = 0; i < bitRate / 4; i++)
	{
		if (bigNumber->hexString[i] == '0')
		{
			zeroCount++;
		}
		else
		{
			break;
		}
	}

	bigNumber->hexString.erase(0, zeroCount);

	if (bigNumber->hexString == "")
	{
		bigNumber->hexString = "0";
	}
}

bool LongComp(bigInteger* numberA, bigInteger* numberB, bool severe)
{
	if (numberA->size < numberB->size) return false;
	if (numberA->size > numberB->size) return true;

	for (long long i = 0; i < numberA->size; i++)
	{
		if (numberA->value[i] > numberB->value[i])
		{
			return true;
		}
		else if (numberA->value[i] < numberB->value[i])
		{
			return false;
		}
		else
		{
			continue;
		}
	}

	switch (severe)
	{
	case false: return true;

	case true: return false;
	}
}

bigInteger* LongAdd(bigInteger* numberA, bigInteger* numberB, int bitRate, bool text, bool selfReculc)
{
	bigInteger* smallerNumber;
	bigInteger* biggerNumber;

	bigInteger* numberC;

	if (numberA->size >= numberB->size)
	{
		numberC = new bigInteger(numberA->size + 1);

		biggerNumber = numberA;
		smallerNumber = numberB;
	}
	else
	{
		numberC = new bigInteger(numberB->size + 1);

		biggerNumber = numberB;
		smallerNumber = numberA;
	}

	unsigned long long module = ULLONG_MAX >> (64 - bitRate);

	unsigned int carry = 0;

	long long difference = abs(numberA->size - numberB->size);

	for (long long i = smallerNumber->size - 1; i >= 0; i--)
	{
		unsigned long long sum = static_cast<unsigned long long>(biggerNumber->value[i + difference]) + static_cast<unsigned long long>(smallerNumber->value[i]) + carry;
		numberC->value[i + difference + 1] = sum & module;
		carry = sum >> bitRate;
	}
	for (long long i = difference - 1; i >= 0; i--)
	{
		unsigned long long sum = static_cast<unsigned long long>(biggerNumber->value[i]) + carry;
		numberC->value[i + 1] = sum & module;
		carry = sum >> bitRate;
	}

	numberC->value[0] = carry;

	ZeroEraser(numberC);

	freeMemory(numberA, selfReculc);

	if (text)
	{
		toHexConverting(numberC, bitRate);
	}

	return numberC;
}

bigInteger* LongSub(bigInteger* numberA, bigInteger* numberB, int bitRate, bool text, bool selfReculc)
{
	unsigned long long module = static_cast<long long>(1) << bitRate;

	bigInteger* numberC;

	if (numberA->size < numberB->size)
	{
		numberC = new bigInteger();

		return numberC;
	}

	numberC = new bigInteger(numberA->size);

	long long borrow = 0;

	long long difference = numberA->size - numberB->size;

	for (long long i = numberB->size - 1; i >= 0; i--)
	{
		long long subtraction = static_cast<long long>(numberA->value[i + difference]) - static_cast<long long>(numberB->value[i]) - borrow;

		if (subtraction >= 0)
		{
			numberC->value[i + difference] = subtraction;
			borrow = 0;
		}
		else
		{
			numberC->value[i + difference] = module + subtraction;
			borrow = 1;
		}
	}
	for (long long i = difference - 1; i >= 0; i--)
	{
		long long subtraction = static_cast<long long>(numberA->value[i]) - borrow;

		if (subtraction >= 0)
		{
			numberC->value[i] = subtraction;
			borrow = 0;
		}
		else
		{
			numberC->value[i] = module + subtraction;
			borrow = 1;
		}
	}

	if (borrow != 0)
	{
		numberC = new bigInteger();

		return numberC;
	}

	if (bitRate >= 4)
	{
		ZeroEraser(numberC);
	}

	freeMemory(numberA, selfReculc);

	if (text)
	{
		toHexConverting(numberC, bitRate);
	}

	return numberC;
}

bigInteger* LongMul(bigInteger* numberA, bigInteger* numberB, int bitRate, bool text, bool selfReculc)
{
	unsigned long long module = ULLONG_MAX >> (64 - bitRate);

	auto* numberC = new bigInteger(numberA->size +	 numberB->size);
	std::fill(&numberC->value[0], &numberC->value[numberC->size], 0);

	for (long long i = numberB->size - 1; i >= 0; i--)
	{
		unsigned long long carry = 0;
		
		auto* intermediateMul = new bigInteger(numberA->size + (numberB->size - 1 - i) + 1);
		std::fill(&intermediateMul->value[0], &intermediateMul->value[intermediateMul->size], 0);

		for (long long j = numberA->size - 1; j >= 0; j--)
		{
			unsigned long long temp = static_cast<unsigned long long>(numberA->value[j]) * static_cast<unsigned long long>(numberB->value[i]) + carry;
			intermediateMul->value[j + 1] = temp & module;

			carry = temp >> bitRate;

			if (j == 0)
			{
				intermediateMul->value[j] = carry;
			}
		}

		numberC = LongAdd(numberC, intermediateMul, bitRate, false, 1);

		freeMemory(intermediateMul);
	}

	freeMemory(numberA, selfReculc);

	if (text)
	{
		toHexConverting(numberC, bitRate);
	}

	return numberC;
}

bigInteger* LongShiftBitsToHigh(bigInteger* number, unsigned long long shift, bool selfReculc)
{
	auto* highNumber = new bigInteger(number->size + shift);

	std::copy(number->value, number->value + number->size, highNumber->value);
	std::fill(&highNumber->value[number->size], &highNumber->value[highNumber->size], 0);
	
	freeMemory(number, selfReculc);

	return highNumber;
}

void SmallFix(bigInteger* number)
{
	int fix = 4 - (number->size % 4);

	long long newSize = number->size + fix;
	auto* fixNumberValue = new unsigned int[newSize];

	std::fill(&fixNumberValue[0], &fixNumberValue[fix], 0);
	std::copy(number->value, number->value + number->size, fixNumberValue + fix);

	delete[] number->value;
	number->value = nullptr;

	number->size = newSize;
	number->value = fixNumberValue;
}

std::unique_ptr<std::pair<bigInteger*, bigInteger*>> LongDiv(bigInteger* dividend, bigInteger* divisor, int bitRate, bool onlyWhole, bool selfReculc)
{
	auto* bitDividend = toBigIntConverting(dividend->hexString, 1);
	auto* bitDivisor = toBigIntConverting(divisor->hexString, 1);

	auto* bitRemainder = new bigInteger(bitDividend->size);
	std::copy(bitDividend->value, bitDividend->value + bitDividend->size, bitRemainder->value);

	auto* bitWholePart = new bigInteger(bitDividend->size);
	std::fill(&bitWholePart->value[0], &bitWholePart->value[bitDividend->size], 0);

	while (LongComp(bitRemainder, bitDivisor, false))
	{
		long long tempLength = bitRemainder->size;

		auto* maxBitDivisor = LongShiftBitsToHigh(bitDivisor, (tempLength - bitDivisor->size));

		if (LongComp(maxBitDivisor, bitRemainder, true))
		{
			freeMemory(maxBitDivisor);

			tempLength--;

			maxBitDivisor = LongShiftBitsToHigh(bitDivisor, (tempLength - bitDivisor->size));
			LongShiftBitsToHigh(maxBitDivisor, (tempLength - bitDivisor->size));
		}

		bitRemainder = LongSub(bitRemainder, maxBitDivisor, 1, false, 1);

		freeMemory(maxBitDivisor);

		ZeroEraser(bitRemainder);

		bitWholePart->value[(bitWholePart->size - 1) - (tempLength - bitDivisor->size)] = 1;
	}

	ZeroEraser(bitWholePart);

	if (bitRemainder->size % 4 != 0)
	{
		SmallFix(bitRemainder);
	}
	
	if (bitWholePart->size % 4 != 0)
	{
		SmallFix(bitWholePart);
	}

	toHexConverting(bitWholePart, 1);
	auto* wholePart = toBigIntConverting(bitWholePart->hexString, bitRate);
	freeMemory(bitWholePart);

	bigInteger* remainder = nullptr;

	if (!onlyWhole)
	{
		toHexConverting(bitRemainder, 1);
		remainder = toBigIntConverting(bitRemainder->hexString, bitRate);
		freeMemory(bitRemainder);
	}

	freeMemory(dividend, selfReculc);
	freeMemory(bitDividend);
	freeMemory(bitDivisor);

	return std::make_unique<std::pair<bigInteger*, bigInteger*>>(std::make_pair(wholePart, remainder));
}

bigInteger* LongPower(bigInteger* numberA, bigInteger* numberB, int bitRate)
{
	auto* bitNumberB = toBigIntConverting(numberB->hexString, 1);

	auto* numberC = new bigInteger();
	numberC->value[0] = static_cast<unsigned int>(1);

	for (long long i = 0; i < bitNumberB->size; i++)
	{
		if (bitNumberB->value[i] == 1)
		{
			numberC = LongMul(numberC, numberA, bitRate, false, 1);
		}

		if (i != bitNumberB->size - 1)
		{
			numberC = LongMul(numberC, numberC, bitRate, false, 1);
		}
	}

	toHexConverting(numberC, bitRate);

	freeMemory(bitNumberB);

	return numberC;
}
#include <iostream>
#include <string>

#include "ModularArithmetic.h"

int main()
{
	int bitRate;
	std::string number;

	std::cout << "Input numbers bit rate: ";
	std::cin >> bitRate;

	std::cout << "Input number A: ";
	std::cin >> number;
	long long numberASize;
	std::string numberAStr(number);

	unsigned int* numberA = toBigIntConverting(number, bitRate, numberASize);

	std::cout << "Input number B: ";
	std::cin >> number;
	long long numberBSize;
	std::string numberBStr(number);

	unsigned int* numberB = toBigIntConverting(number, bitRate, numberBSize);

	std::cout << "Input module: ";
	std::cin >> number;
	long long modSize;
	std::string modStr(number);

	unsigned int* mod = toBigIntConverting(number, bitRate, modSize);
	
	long long muSize;
	unsigned int* bigMu = MuCalculus(modStr, bitRate, modSize, muSize);

	std::cout << "Modular addition: ";
	long long additionSize;
	unsigned int* modAddition = ModAdd(numberA, numberB, mod, bigMu, bitRate, numberASize, numberBSize, modSize, muSize, additionSize);

	std::cout << *toHexConverting(modAddition, bitRate, additionSize) << std::endl;

	std::cout << "Modular subtraction: ";
	long long subtractionSize;

	unsigned int* modSubstraction = ModSub(numberA, numberB, mod, bigMu, bitRate, numberASize, numberBSize, modSize, muSize, subtractionSize);

	std::cout << *toHexConverting(modSubstraction, bitRate, subtractionSize) << std::endl;

	std::cout << "Modular multiplication: ";
	long long multiplicationSize;

	unsigned int* modMultiplication = ModMul(numberA, numberB, mod, bigMu, bitRate, numberASize, numberBSize, modSize, muSize, multiplicationSize);

	std::cout << *toHexConverting(modMultiplication, bitRate, multiplicationSize) << std::endl;

}
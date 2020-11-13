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
	auto* numberA = toBigIntConverting(number, bitRate);

	std::cout << "Input number B: ";
	std::cin >> number;
	auto* numberB = toBigIntConverting(number, bitRate);

	std::cout << "Input module: ";
	std::cin >> number;
	auto* mod = toBigIntConverting(number, bitRate);

	auto* mu = MuCalculus(mod, bitRate);

	std::cout << "Modular addition: ";
	auto* modAddition = ModAdd(numberA, numberB, mod, mu, bitRate);
	std::cout << modAddition->hexString << std::endl;

	std::cout << "Modular subtraction: ";
	auto* modSubtraction = ModSub(numberA, numberB, mod, mu, bitRate);
	std::cout << modSubtraction->hexString << std::endl;

	std::cout << "Modular multiplication: ";
	auto* modMultiplication = ModMul(numberA, numberB, mod, mu, bitRate);
	std::cout << modMultiplication->hexString << std::endl;

	std::cout << "Modular pow: ";
	auto* modPow = ModPow(numberA, numberB, mod, mu, bitRate);
	std::cout << modPow->hexString << std::endl;
}
#include <ctime>
#include <iostream>
#include <string>

#include "ModularArithmetic.h"

int main()
{
	srand(time(NULL));

	int bitRate;
	std::string number;

	std::cout << "Input numbers bit rate: ";
	std::cin >> bitRate;

	std::cout << "Input number A: ";
	std::cin >> number;
	auto numberA = toBigIntConverting(number, bitRate);

	std::cout << "Input number B: ";
	std::cin >> number;
	auto numberB = toBigIntConverting(number, bitRate);

	std::cout << "Input module: ";
	std::cin >> number;
	auto mod = toBigIntConverting(number, bitRate);

	auto mu = MuCalculus(mod, bitRate);

	std::cout << "Modular addition: ";
	auto modAddition = ModAdd(numberA, numberB, mod, mu, bitRate);
	std::cout << modAddition->hexString << std::endl;

	std::cout << "Modular subtraction: ";
	auto modSubtraction = ModSub(numberA, numberB, mod, mu, bitRate);
	std::cout << modSubtraction->hexString << std::endl;

	std::cout << "Modular multiplication: ";
	auto modMultiplication = ModMul(numberA, numberB, mod, mu, bitRate);
	std::cout << modMultiplication->hexString << std::endl;

	std::cout << "Modular pow: ";
	auto modPow = ModPow(numberA, numberB, mod, mu, bitRate);
	std::cout << modPow->hexString << std::endl;

	std::cout << "Great common divisor: ";
	auto gcd = GreatCommonDivisor(numberA, numberB, bitRate);
	std::cout << gcd->hexString << std::endl;

	std::cout << "Least common multiple: ";
	auto lcm = LeastCommonMultiple(numberA, numberB, gcd, bitRate);
	std::cout << lcm->hexString << std::endl;

	std::cout << "-------TESTS------" << std::endl;

	std::cout << "1. Distributivity" << std::endl;

	std::cout << "Input number C: ";
	std::cin >> number;
	auto numberC = toBigIntConverting(number, bitRate);

	std::cout << "1.1. ((A + B) * C) mod N = ";
	auto firstPropertie = ModMul(ModAdd(numberA, numberB, mod, mu, bitRate), numberC, mod, mu, bitRate);
	std::cout << firstPropertie->hexString << std::endl;

	std::cout << "1.2. (C * (A + B)) mod N = ";
	auto secondPropertie = ModMul(numberC, ModAdd(numberA, numberB, mod, mu, bitRate), mod, mu, bitRate);
	std::cout << secondPropertie->hexString << std::endl;

	std::cout << "1.3. (A * C + B * C) mod N = ";
	auto thirdPropertie = ModAdd(ModMul(numberA, numberC, mod, mu, bitRate), ModMul(numberB, numberC, mod, mu, bitRate), mod, mu, bitRate);
	std::cout << thirdPropertie->hexString << std::endl;

	std::cout << "2. Equivalence of multiplication by addition" << std::endl;

	int randomN = rand() % 1000 + 100;
	std::cout << "n = " << randomN << std::endl;
	std::string randomNString = std::to_string(randomN);

	auto bigRandomN = toBigIntConverting(randomNString, bitRate);

	std::cout << "2.1. n * A = ";
	auto equivMultiplication = ModMul(numberA, bigRandomN, mod, mu, bitRate);
	std::cout << equivMultiplication->hexString << std::endl;

	auto equivAddition = numberA;

	for (int i = 1; i <= randomN - 1; i++)
	{
		equivAddition = ModAdd(equivAddition, numberA, mod, mu, bitRate);
	}

	toHexConverting(equivAddition, bitRate);

	std::cout << "2.2. A + A + ... + A = ";
	std::cout << equivAddition->hexString << std::endl;

	std::cout << "3. Fermat's little theorem" << std::endl;

	int randomPower = rand() % 500 + 100;
	std::cout << "k = " << randomPower << std::endl;

	auto bigRandomPower = toBigIntConverting(std::to_string(randomPower), bitRate);

	auto powerMod = LongPow(toBigIntConverting("3", bitRate), bigRandomPower, bitRate);
	std::cout << "3^k = " << powerMod->hexString << std::endl;

	auto fermatPower = LongMul(toBigIntConverting("2", bitRate), LongPow(toBigIntConverting("3", bitRate), LongSub(bigRandomPower, toBigIntConverting("1", bitRate), bitRate), bitRate), bitRate);
	std::cout << "fi(3^k) = " << fermatPower->hexString << std::endl;

	auto fermatMu = MuCalculus(powerMod, bitRate);

	auto uno = ModPow(numberA, fermatPower, powerMod, fermatMu, bitRate);
	std::cout << "numberA^fi(3^k) mod 3^k = " << uno->hexString << std::endl;

	return 0;
}
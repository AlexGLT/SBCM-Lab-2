#include <iostream>
#include <string>

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
}
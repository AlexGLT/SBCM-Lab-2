#include <iostream>
#include <memory>

struct bigInteger
{
	long long size;
	std::string hexString;

	unsigned int* value;
	
	bigInteger();

	bigInteger(const long long& size);

	bigInteger(const long long& size, const std::string& hexString);

	~bigInteger();
};

void showBigInteger(bigInteger* number, std::string numberName);

void freeMemory(bigInteger* number, bool selfReculc = true);
void ZeroEraser(bigInteger* number);
void SmallFix(bigInteger* number);

bigInteger* toBigIntConverting(std::string number, const int& bitRate);
void toHexConverting(bigInteger* bigNumber, int bitRate);

bool LongComp(bigInteger* numberA, bigInteger* numberB, bool severe);
bigInteger* LongShiftBitsToHigh(bigInteger* number, unsigned long long shift, bool selfReculc = false);

bigInteger* LongAdd(bigInteger* numberA, bigInteger* numberB, int bitRate, bool text = true, bool selfReculc = false);
bigInteger* LongSub(bigInteger* numberA, bigInteger* numberB, int bitRate, bool text = true, bool selfReculc = false);
bigInteger* LongMul(bigInteger* numberA, bigInteger* numberB, int bitRate, bool text = true, bool selfReculc = false);
std::unique_ptr<std::pair<bigInteger*, bigInteger*>> LongDiv(bigInteger* dividend, bigInteger* divisor, int bitRate, bool onlyWhole = false, bool selfReculc = false);
bigInteger* LongPower(bigInteger* numberA, bigInteger* numberB, int bitRate);
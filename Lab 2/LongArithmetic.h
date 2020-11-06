#include <iostream>

unsigned int* ZeroEraser(unsigned int* number, long long& numberSize);
unsigned int* toBigIntConverting(std::string& number, const int& bitRate, long long& bigNumSize);
std::string* toHexConverting(unsigned int* bigNumber, int bitRate, long long& bigNumSize);

bool LongComp(const unsigned int* numberA, const unsigned int* numberB, const long long& numberASize, const long long& numberBSize, bool severe);

unsigned int* LongAdd(const unsigned int* numberA, const unsigned int* numberB, int bitRate, long long numberASize, long long numberBSize, long long& numberCSize, bool mul = false);

unsigned int* LongSub(const unsigned int* numberA, const unsigned int* numberB, int bitRate, long long numberASize, long long numberBSize, long long& numberCSize, bool div = false);
unsigned int* LongMul(const unsigned int* numberA, const unsigned int* numberB, int bitRate, long long numberASize, long long numberBSize, long long& numberCSize);
unsigned int* LongShiftBitsToHigh(const unsigned int* number, unsigned long long shift, const long long& numberSize, long long& shiftedNumberSize);
unsigned int* SmallFix(const unsigned int* number, long long& numberSize);

unsigned int** LongDiv(std::string& dividend, std::string& divisor, int bitRate, long long& wholePartBitLength, long long& remainderBitLength);
unsigned int* LongPower(const unsigned int* numberA, const unsigned int* numberB, int bitRate, long long numberASize, long long numberBBitSize, long long& numberCSize);

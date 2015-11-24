#include "LongReal.h"
#include <memory.h>

LongReal::LongReal()
{
	_isPositive = 1;
	_posDigits = new SBYTE[MAX_DIGIT_COUNT];
	_negDigits = new SBYTE[MAX_ACCURACY];

	memset(_posDigits, 0, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memset(_negDigits, 0, sizeof(SBYTE)*MAX_ACCURACY);
}

LongReal::~LongReal()
{
	delete[] _posDigits;
	delete[] _negDigits;
}

const LongReal LongReal::operator- ()
{
	_isPositive = !_isPositive;
	return *this;
}

const LongReal LongReal::operator= (LongReal& second)
{
	this->_isPositive = second._isPositive;
	memcpy(this->_posDigits, second._posDigits, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memcpy(this->_negDigits, second._negDigits, sizeof(SBYTE)*MAX_ACCURACY);
	return *this;
}

const bool LongReal::operator == (const LongReal second)
{
	if (this->_isPositive != second._isPositive)
		return 0;

	for (char i = 0; i < MAX_DIGIT_COUNT; i++)
		if (this->_posDigits[i] != second._posDigits[i])
			return 0;

	for (char i = 0; i < MAX_ACCURACY; i++)
		if (this->_negDigits[i] != second._negDigits[i])
			return 0;

	return 1;
}

const bool LongReal::operator != (const LongReal second)
{
	return !(*this == second);
}

const bool LongReal::operator > (const LongReal second)
{
	if (this->_isPositive && !second._isPositive)
		return 1;

	for (char i = MAX_DIGIT_COUNT - 1; i >= 0; i--)
		if (this->_posDigits[i] > second._posDigits[i])
			return 1;

	for (char i = 0; i < MAX_ACCURACY; i++)
		if (this->_negDigits[i] > second._negDigits[i])
			return 1;

	return 0;
}

const bool LongReal::operator < (const LongReal second)
{
	if (!this->_isPositive && second._isPositive)
		return 1;

	for (char i = MAX_DIGIT_COUNT - 1; i >= 0; i--)
		if (this->_posDigits[i] < second._posDigits[i])
			return 1;

	for (char i = 0; i < MAX_ACCURACY; i++)
		if (this->_negDigits[i] < second._negDigits[i])
			return 1;

	return 0;
}

const bool LongReal::operator >= (const LongReal second)
{
	return !(*this < second);
}

const bool LongReal::operator <= (const LongReal second)
{
	return !(*this > second);
}
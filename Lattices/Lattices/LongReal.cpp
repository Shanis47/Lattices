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

const LongReal LongReal::operator- () const
{
	//_isPositive = !_isPositive;
	LongReal result = *this;
	result._isPositive = !this->_isPositive;
	return result;
}

const LongReal LongReal::operator= (LongReal& second)
{
	this->_isPositive = second._isPositive;
	memcpy(this->_posDigits, second._posDigits, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memcpy(this->_negDigits, second._negDigits, sizeof(SBYTE)*MAX_ACCURACY);
	return *this;
}

const bool LongReal::operator == (const LongReal second) const
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

const bool LongReal::operator != (const LongReal second) const
{
	return !(*this == second);
}

const bool LongReal::operator > (const LongReal second) const
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

const bool LongReal::operator < (const LongReal second) const
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

const bool LongReal::operator >= (const LongReal second) const
{
	return !(*this < second);
}

const bool LongReal::operator <= (const LongReal second) const
{
	return !(*this > second);
}

//Arithmetical operators
const LongReal LongReal::operator + (const LongReal& second) const
{
	if (this->_isPositive && !second._isPositive)
		return (*this - (-second));
	if (!this->_isPositive && second._isPositive)
		return (second - (-*this));

	LongReal result = *this;
	
	for (int i = MAX_ACCURACY -1; i >= 0; i--)
	{
		result._negDigits[i] += second._negDigits[i];
		if (result._negDigits[i] >= RADIX)
		{
			result._negDigits[i] %= RADIX;
			if (i)
				result._negDigits[i-1]++;
			else
				result._posDigits[0]++;
		}
	}

	for (int i = 0; i < MAX_DIGIT_COUNT; i++)
	{
		result._posDigits[i] += second._posDigits[i];
		if (result._posDigits[i] >= RADIX)
		{
			result._posDigits[i] %= RADIX;
			if (i < MAX_DIGIT_COUNT - 1)
				result._posDigits[i+1]++;
		}
	}

	return result;
}

const LongReal LongReal::operator - (const LongReal& second) const
{
	if (this->_isPositive && !second._isPositive)
		return (*this + (-second));
	if (!this->_isPositive && second._isPositive)
		return -(second + (-*this));
	if (*this < second)
		return -(second - *this);

	LongReal result = *this;

	for (int i = MAX_ACCURACY -1; i >= 0; i--)
	{
		result._negDigits[i] -= second._negDigits[i];
		if (result._negDigits[i] < 0)
		{
			result._negDigits[i] += RADIX;
			if (i)
				result._negDigits[i-1]--;
			else
				result._posDigits[0]--;
		}
	}

	for (int i = 0; i < MAX_DIGIT_COUNT; i++)
	{
		result._posDigits[i] -= second._posDigits[i];
		if (result._posDigits[i] < 0)
		{
			if (i < MAX_DIGIT_COUNT - 1)
				result._posDigits[i+1]--;
		}
	}

	return result;
}

const LongReal LongReal::operator * (const LongReal& second) const
{
	if (this->_isPositive && !second._isPositive)
		return -(*this * (-second));
	if (!this->_isPositive && second._isPositive)
		return -(second * (-*this));

	SBYTE* resultDigits = new SBYTE[2*(MAX_DIGIT_COUNT + MAX_ACCURACY)];
	memset(resultDigits, 0, 2*sizeof(SBYTE)*(MAX_DIGIT_COUNT + MAX_ACCURACY));

	SBYTE* mul1Digits = new SBYTE[MAX_DIGIT_COUNT + MAX_ACCURACY];
	SBYTE* mul2Digits = new SBYTE[MAX_DIGIT_COUNT + MAX_ACCURACY];

	memcpy(mul1Digits, this->_posDigits, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memcpy(mul1Digits + sizeof(SBYTE)*MAX_DIGIT_COUNT, this->_negDigits, sizeof(SBYTE)*MAX_ACCURACY);
	memcpy(mul2Digits, second._posDigits, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memcpy(mul2Digits + sizeof(SBYTE)*MAX_DIGIT_COUNT, second._negDigits, sizeof(SBYTE)*MAX_ACCURACY);

	for (int i = MAX_DIGIT_COUNT + MAX_ACCURACY - 1; i >= 0; i--)
	{
		SBYTE pred = 0;
		for (int j = j < MAX_DIGIT_COUNT + MAX_ACCURACY - 1; j >= 0; j--)
		{
			SBYTE mul = mul1Digits[j] * mul2Digits[i];
			resultDigits[i + j +1] += pred + mul % RADIX;
			if (resultDigits[i + j +1] > RADIX)
			{
				resultDigits[i+j+1] %= RADIX;
				resultDigits[i+j]++;
			}

			pred = mul / RADIX;
		}
	}

	LongReal result = *this;

	memcpy(result._posDigits, resultDigits + sizeof(SBYTE)*MAX_DIGIT_COUNT, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memcpy(result._negDigits, resultDigits + 2*sizeof(SBYTE)*MAX_DIGIT_COUNT, sizeof(SBYTE)*MAX_ACCURACY);

	delete[] mul2Digits;
	delete[] mul1Digits;
	delete[] resultDigits;
	return result;
}
//	const LongReal operator / (const LongReal& second);
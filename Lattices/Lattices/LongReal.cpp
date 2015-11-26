#include "LongReal.h"
#include <memory.h>
#include <math.h>

LongReal::LongReal()
{
	_isPositive = 1;
	_posDigits = new SBYTE[MAX_DIGIT_COUNT];
	_negDigits = new SBYTE[MAX_ACCURACY];

	memset(_posDigits, 0, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memset(_negDigits, 0, sizeof(SBYTE)*MAX_ACCURACY);
}

LongReal::LongReal(const LongReal& r)
{
	_isPositive = r._isPositive;
	_posDigits = new SBYTE[MAX_DIGIT_COUNT];
	_negDigits = new SBYTE[MAX_ACCURACY];

	memcpy(_posDigits, r._posDigits, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memcpy(_negDigits, r._negDigits, sizeof(SBYTE)*MAX_ACCURACY);
}

LongReal::~LongReal()
{
	delete[] _posDigits;
	delete[] _negDigits;
}

const LongReal LongReal::operator- () const
{
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

const LongReal LongReal::operator= (const double& r)
{
	this->_isPositive = r >= 0;

	for (int i = 0; i < MAX_DIGIT_COUNT; i++)
		this->_posDigits[i] = ((int)(r / pow(RADIX, MAX_DIGIT_COUNT-i)) % RADIX);

	for (int i = 0; i < MAX_ACCURACY; i++)
		this->_negDigits[i] = ((int)(r * pow(RADIX, i+1)) % RADIX);

	return *this;
}

const LongReal LongReal::operator += (LongReal& second)
{
	LongReal result = *this + second;
	*this = result;
	return result;
}

const LongReal LongReal::operator -= (LongReal& second)
{
	LongReal result = *this - second;
	*this = result;
	return result;
}
	
const LongReal LongReal::operator *= (LongReal& second)
{
	LongReal result = *this * second;
	*this = result;
	return result;
}
	
const LongReal LongReal::operator /= (LongReal& second)
{
	LongReal result = *this / second;
	*this = result;
	return result;
}

const bool LongReal::operator == (const LongReal& second) const
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

const bool LongReal::operator != (const LongReal& second) const
{
	return !(*this == second);
}

const bool LongReal::operator > (const LongReal& second) const
{
	if (this->_isPositive && !second._isPositive)
		return 1;

	for (char i = 0; i < MAX_DIGIT_COUNT; i++)
		if (this->_posDigits[i] != second._posDigits[i])
			return this->_posDigits[i] > second._posDigits[i];

	for (char i = 0; i < MAX_ACCURACY; i++)
		if (this->_negDigits[i] > second._negDigits[i])
			return this->_negDigits[i] > second._negDigits[i];

	return 0;
}

const bool LongReal::operator < (const LongReal& second) const
{
	if (!this->_isPositive && second._isPositive)
		return 1;

	for (char i = 0; i < MAX_DIGIT_COUNT; i++)
		if (this->_posDigits[i] != second._posDigits[i])
			return this->_posDigits[i] < second._posDigits[i];

	for (char i = 0; i < MAX_ACCURACY; i++)
		if (this->_negDigits[i] != second._negDigits[i])
			return this->_posDigits[i] < second._posDigits[i];

	return 0;
}

const bool LongReal::operator >= (const LongReal& second) const
{
	return !(*this < second);
}

const bool LongReal::operator <= (const LongReal& second) const
{
	return !(*this > second);
}

//Arithmetical operators
LongReal LongReal::operator + (const LongReal& second) const
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

	for (int i = MAX_DIGIT_COUNT - 1; i >= 0; i--)
	{
		result._posDigits[i] += second._posDigits[i];
		if (result._posDigits[i] >= RADIX)
		{
			result._posDigits[i] %= RADIX;
			if (i > 0)
				result._posDigits[i-1]++;
		}
	}

	return result;
}

LongReal LongReal::operator - (const LongReal& second) const
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
				result._posDigits[MAX_DIGIT_COUNT - 1]--;
		}
	}

	for (int i = MAX_DIGIT_COUNT - 1; i >= 0; i--)
	{
		result._posDigits[i] -= second._posDigits[i];
		if (result._posDigits[i] < 0)
		{
			result._posDigits[i] += RADIX;
			if (i > 0)
				result._posDigits[i-1]--;
		}
	}

	return result;
}

LongReal LongReal::operator * (const LongReal& second) const
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
		for (int j = MAX_DIGIT_COUNT + MAX_ACCURACY - 1; j >= 0; j--)
		{
			SBYTE mul = mul1Digits[j] * mul2Digits[i];
			resultDigits[i + j +1] += pred + mul % RADIX;
			if (resultDigits[i + j +1] >= RADIX)
			{
				resultDigits[i+j+1] %= RADIX;
				resultDigits[i+j]++;
			}

			pred = mul / RADIX;
		}
	}

	LongReal result;

	memcpy(result._posDigits, resultDigits + sizeof(SBYTE)*MAX_DIGIT_COUNT, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memcpy(result._negDigits, resultDigits + 2*sizeof(SBYTE)*MAX_DIGIT_COUNT, sizeof(SBYTE)*MAX_ACCURACY);

	delete[] mul2Digits;
	delete[] mul1Digits;
	delete[] resultDigits;
	return result;
}

LongReal LongReal::operator / (const LongReal& second) const
{
	if (this->_isPositive && !second._isPositive)
		return -(*this / (-second));
	if (!this->_isPositive && second._isPositive)
		return -((-*this) / second);
	LongReal result;
	LongReal reminder = *this;

	//�� ��� ������ �����, ������� �����... ������
	for (int i = 0; i < MAX_DIGIT_COUNT; i++)
	{
		while (result*second < reminder && result._posDigits[i] < RADIX) //������ ���������� �� ������
			result._posDigits[i]++;
		if (result*second > reminder)
			result._posDigits[i]--;
	}

	for (int i = 0; i < MAX_ACCURACY; i++)
	{
		while (result*second < reminder && result._posDigits[i] < RADIX) //������ ���������� �� ������
			result._negDigits[i]++;
		if (result*second > reminder)
			result._negDigits[i]--;
	}

	return result;
}

ostream& operator << (ostream& out, const LongReal& r)
{
	int i;
	for (i = 0; i < MAX_DIGIT_COUNT && r._posDigits[i] == 0; i++);
	if (!r._isPositive)
		out << '-';
	if (i == MAX_DIGIT_COUNT)
		out << '0';
	for (; i < MAX_DIGIT_COUNT; i++)
		out << char(r._posDigits[i]+'0');

	out << ".";

	for (i = 0; i < MAX_ACCURACY; i++)
		out << char(r._negDigits[i]+'0');

	return out;
}

istream& operator >> (istream& in, LongReal& r)
{
	memset(r._posDigits, 0, sizeof(SBYTE)*MAX_DIGIT_COUNT);
	memset(r._negDigits, 0, sizeof(SBYTE)*MAX_ACCURACY);
	r._isPositive = 1;
	SBYTE* digits = new SBYTE[MAX_DIGIT_COUNT + MAX_ACCURACY];
	memset(digits, 0, sizeof(SBYTE)*(MAX_DIGIT_COUNT + MAX_ACCURACY));

	char pointPosition = 0, currentPosition = 0;
	char currentChar = 0;

	in.clear();
	while (!(isdigit(currentChar) || currentChar == '.' || currentChar=='-'))
		in.get(currentChar);
	while (!in.eof() && (isdigit(currentChar) || currentChar == '.' || currentChar=='-'))
	{
		if (currentPosition == 0 && currentChar == '-')
		{
			r._isPositive = 0;
			in.get(currentChar);
		}
		if (isdigit(currentChar))
			digits[currentPosition++] = currentChar - '0';
		else
			if (currentChar == '.')
				pointPosition = currentPosition;
		in.get(currentChar);
	}

	if (pointPosition != 0)
	{
		memcpy(r._posDigits + sizeof(SBYTE)*(MAX_ACCURACY-pointPosition), digits, sizeof(SBYTE)*pointPosition);
		memcpy(r._negDigits, digits + sizeof(SBYTE)*pointPosition, sizeof(SBYTE)*MAX_ACCURACY);
	}
	else
		memcpy(r._posDigits + sizeof(SBYTE)*(MAX_ACCURACY-currentPosition), digits, sizeof(SBYTE)*currentPosition);

	delete[] digits;
	return in;
}

LongReal abs(const LongReal& r)
{
	LongReal result = r;
	result._isPositive = 1;
	return result;
}
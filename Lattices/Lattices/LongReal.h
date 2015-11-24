#pragma once

#define MAX_DIGIT_COUNT 50
#define MAX_ACCURACY 50
#define SBYTE signed char

class LongReal
{
private:
	SBYTE* _posDigits;
	SBYTE* _negDigits;
	bool _isPositive;

public:
	LongReal();
	~LongReal();

	//Unar
	friend const LongReal operator - (const LongReal& second);

	//Arithmetical operators
	friend const LongReal operator + (const LongReal& first, LongReal& second);
	friend const LongReal operator - (const LongReal& first, const LongReal& second);
	friend const LongReal operator * (const LongReal& first, const LongReal& second);
	friend const LongReal operator / (const LongReal& first, const LongReal& second);

	//Logical operators
	friend const bool operator == (const LongReal first, const LongReal second);
	friend const bool operator != (const LongReal first, const LongReal second);
	friend const bool operator > (const LongReal first, const LongReal second);
	friend const bool operator < (const LongReal first, const LongReal second);
	friend const bool operator >= (const LongReal first, const LongReal second);
	friend const bool operator <= (const LongReal first, const LongReal second);
};
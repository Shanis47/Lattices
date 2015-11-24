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
	const LongReal operator - ();

	//Binary
	const LongReal operator = (LongReal& second);

	//Arithmetical operators
	const LongReal operator + (LongReal& second);
	const LongReal operator - (const LongReal& second);
	const LongReal operator * (const LongReal& second);
	const LongReal operator / (const LongReal& second);

	//Logical operators
	const bool operator == (const LongReal second);
	const bool operator != (const LongReal second);
	const bool operator > (const LongReal second);
	const bool operator < (const LongReal second);
	const bool operator >= (const LongReal second);
	const bool operator <= (const LongReal second);
};

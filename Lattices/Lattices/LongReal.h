#pragma once

#define MAX_DIGIT_COUNT 50
#define MAX_ACCURACY 50
#define RADIX 10
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
	const LongReal operator - () const;

	//Binary
	const LongReal operator = (LongReal& second);

	//Arithmetical operators
	const LongReal operator + (const LongReal& second) const;
	const LongReal operator - (const LongReal& second) const;
	const LongReal operator * (const LongReal& second) const;
	const LongReal operator / (const LongReal& second) const;

	//Logical operators
	const bool operator == (const LongReal second) const;
	const bool operator != (const LongReal second) const;
	const bool operator > (const LongReal second) const;
	const bool operator < (const LongReal second) const;
	const bool operator >= (const LongReal second) const;
	const bool operator <= (const LongReal second) const;
};

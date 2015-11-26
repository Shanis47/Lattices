#pragma once
#include <iostream>
using namespace std;

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
	LongReal(const LongReal& r);
	~LongReal();

	//Unar
	const LongReal operator - () const;

	//Binary
	const LongReal operator = (LongReal& second);
	const LongReal operator += (LongReal& second);
	const LongReal operator -= (LongReal& second);
	const LongReal operator *= (LongReal& second);
	const LongReal operator /= (LongReal& second);
	const LongReal operator = (const double& r);

	//Arithmetical operators
	LongReal operator + (const LongReal& second) const;
	LongReal operator - (const LongReal& second) const;
	LongReal operator * (const LongReal& second) const;
	LongReal operator / (const LongReal& second) const;

	//Logical operators
	const bool operator == (const LongReal& second) const;
	const bool operator != (const LongReal& second) const;
	const bool operator > (const LongReal& second) const;
	const bool operator < (const LongReal& second) const;
	const bool operator >= (const LongReal& second) const;
	const bool operator <= (const LongReal& second) const;
	
	//I/O operators
	friend ostream& operator << (ostream& out, const LongReal& r);
	friend istream& operator >> (istream& in, LongReal& r);

	friend LongReal abs(const LongReal& r);
};
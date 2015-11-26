#pragma once
#include "LongReal.h"

#define uint unsigned int

class Lattice
{
private:
	uint _size;
	LongReal** _basis;
public:
	Lattice(void);
	Lattice(uint size, LongReal** basis);
	~Lattice(void);

	LongReal** GramSchmidt();
	void SetBasis(uint, LongReal** );
	uint GetSize();
	LongReal** GetBasis();
};


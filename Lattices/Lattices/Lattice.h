#pragma once
#include <iostream>

#define uint unsigned int

class Lattice
{
private:
	uint _size;
	double** _basis;
public:
	Lattice(void);
	Lattice(int size, double** basis);
	~Lattice(void);

	void SetBasis(uint, double** );
	uint GetSize();
	double** GetBasis();
};


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
	Lattice(uint size, double** basis);
	~Lattice(void);

	double** GramSchmidt(double** basis, uint size);
	double* Proj (double* a, double* b, uint size);
	void SetBasis(uint, double** );
	uint GetSize();
	double** GetBasis();
};


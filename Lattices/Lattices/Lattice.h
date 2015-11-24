#pragma once

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

	void SetBasis(uint, double** );
	uint GetSize();
	double** GetBasis();
};


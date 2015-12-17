#pragma once

class Lattice
{
private:
	int _size;
	double** _basis;
	double** GramSchmidt(double** &mu, double* &B);
public:
	Lattice(void);
	Lattice(int size, double** basis);
	~Lattice(void);

	double** GramSchmidt();
	void LLLalgorithm();

	void SetBasis(int, double** );
	int GetSize();
	double** GetBasis();
};


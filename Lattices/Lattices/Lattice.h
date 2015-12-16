#pragma once

class Lattice
{
private:
	int _size;
	double** _basis;
public:
	Lattice(void);
	Lattice(int size, double** basis);
	~Lattice(void);

	void GramSchmidt();
	void LLLalgorithm();
	bool CheckLLLConditions();

	void SetBasis(int, double** );
	int GetSize();
	double** GetBasis();
};


#include "Lattice.h"

Lattice::Lattice(int size, double** basis)
{
	_size = size;
	_basis = new double*[_size];
	for (int i = 0; i < _size; i++)
	{
		_basis[i] = new double[_size];
		std::memcpy(_basis[i], basis[i], sizeof(double)*_size);
	}
}

Lattice::Lattice(void)
{
	_size = 0;
	_basis = new double*[0];
}

Lattice::~Lattice(void)
{
	delete[] _basis;
}

uint Lattice::GetSize()
{
	return _size;
}

double** Lattice::GetBasis()
{
	double** result = new double*[_size];
	for (int i = 0; i < _size; i++)
	{
		result[i] = new double[_size];
		std::memcpy(result[i], _basis[i], sizeof(double)*_size);
	}

	return result;
}

void Lattice::SetBasis(uint size, double** basis)
{
	_size = size;
	_basis = new double*[_size];
	for (int i = 0; i < _size; i++)
	{
		_basis[i] = new double[_size];
		std::memcpy(_basis[i], basis[i], sizeof(double)*_size);
	}
}
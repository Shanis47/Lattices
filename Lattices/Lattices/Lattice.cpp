#include "Lattice.h"
#include <exception>

bool ChechkLinearIdependence(uint size, double** basis)
{
	uint rank = size;
	double eps = 1e-9;

	double** work = new double*[size];
	for (uint i = 0; i < size; i++)
	{
		work[i] = new double[size];
		std::memcpy(work[i], basis[i], sizeof(double)*size);
	}

	bool *line_used = new bool[size];
	memset(line_used, 0, sizeof(bool)*size);
	for (int i=0; i<size; ++i) 
	{
		int j;
		for (j = 0; j < size; j++)
			if (!line_used[j] && abs(work[j][i]) > eps)
				break;

		if (j == size)
			return 0;
		else {
			line_used[j] = true;
			for (int p = i+1; p < size; p++)
				work[j][p] /= work[j][i];
			for (int k = 0; k < size; k++)
				if (k != j && abs (work[k][i]) > eps)
					for (int p= i + 1; p < size; p++)
						work[k][p] -= work[j][p] * work[k][i];
		}
	}

	for (int i =0; i< size; i++)
		delete[] work[i];
	delete[] work;

	return rank == size;
}

Lattice::Lattice(uint size, double** basis)
{
	if (!ChechkLinearIdependence(size, basis))
		throw std::exception("Not linear independ");

	_size = size;
	_basis = new double*[_size];
	for (uint i = 0; i < _size; i++)
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
	for (uint i =0; i< _size; i++)
		delete[] _basis[i];

	delete[] _basis;
}

uint Lattice::GetSize()
{
	return _size;
}

double** Lattice::GetBasis()
{
	double** result = new double*[_size];
	for (uint i = 0; i < _size; i++)
	{
		result[i] = new double[_size];
		std::memcpy(result[i], _basis[i], sizeof(double)*_size);
	}

	return result;
}

void Lattice::SetBasis(uint size, double** basis)
{
	if (!ChechkLinearIdependence(size, basis))
		throw std::exception("Not linear independ");

	_size = size;
	_basis = new double*[_size];
	for (uint i = 0; i < _size; i++)
	{
		_basis[i] = new double[_size];
		std::memcpy(_basis[i], basis[i], sizeof(double)*_size);
	}
}
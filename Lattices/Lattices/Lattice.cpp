#include "Lattice.h"
#include <memory.h>
#include <math.h>
#include <exception>

LongReal* Proj(LongReal* a, LongReal* b, int size);
bool ChechkLinearIdependence(uint size, LongReal** basis)
{
	uint rank = size;
	LongReal eps;
	eps = 1e-9;

	LongReal** work = new LongReal*[size];
	for (uint i = 0; i < size; i++)
	{
		work[i] = new LongReal[size];
		for (uint j = 0; j < size; j++)
			work[i][j] = basis[i][j];
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

Lattice::Lattice(uint size, LongReal** basis)
{
	if (!ChechkLinearIdependence(size, basis))
		throw std::exception("Not linear independ");

	_size = size;
	_basis = new LongReal*[_size];
	for (uint i = 0; i < _size; i++)
	{
		_basis[i] = new LongReal[_size];
		for (uint j = 0; j < _size; j++)
			_basis[i][j] = basis[i][j];
	}
}

Lattice::Lattice(void)
{
	_size = 0;
	_basis = new LongReal*[0];
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

LongReal** Lattice::GetBasis()
{
	LongReal** result = new LongReal*[_size];
	for (uint i = 0; i < _size; i++)
	{
		result[i] = new LongReal[_size];
		for (uint j = 0; j < _size; j++)
			result[i][j] = _basis[i][j];
	}

	return result;
}

void Lattice::SetBasis(uint size, LongReal** basis)
{
	if (!ChechkLinearIdependence(size, basis))
		throw std::exception("Not linear independ");

	_size = size;
	_basis = new LongReal*[_size];
	for (uint i = 0; i < _size; i++)
	{
		_basis[i] = new LongReal[_size];
		for (uint j = 0; j < _size; j++)
			_basis[i][j] = basis[i][j];
	}
}

LongReal* Proj (LongReal* a, LongReal* b,int size)
{
	LongReal scala_b;
	LongReal scalb_b;
	scala_b = 0.0; 
	scalb_b = 0.0;

	for (int i = 0; i < size; i++)
	{
		scala_b += a[i] * b[i];
		scalb_b += b[i] * b[i];
	}
	LongReal scal_na_scal = scala_b / scalb_b;
	LongReal* proj = new LongReal[size];
	for(int j = 0; j < size; j++)
	{
		proj[j] = scal_na_scal * b[j];
	}
	return proj;
}

LongReal** Lattice::GramSchmidt()
{
	LongReal** ort_vectors=new LongReal*[_size];
	for (int i = 0; i < _size; i++)
	{
		ort_vectors[i]=new LongReal[_size];
		if (!i)
		{
			for (int j = 0; j < _size; j++)
			{
				ort_vectors[i][j] = _basis[i][j];
			}
			continue;
		}

		for (int m = 0; m < _size; m++)
			ort_vectors[i][m] = _basis[i][m];

		for (int k = 0; k < i; k++)
		{
			LongReal* proj = Proj(_basis[i], ort_vectors[k], _size);
			for (int p = 0;p < _size; p++)
			{
				ort_vectors[i][p] -= proj[p];
			}
			delete[] proj;
		}
	}
	return ort_vectors;
}
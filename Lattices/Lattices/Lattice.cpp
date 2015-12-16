#include "Lattice.h"
#include <memory.h>
#include <math.h>
#include <exception>

 double* Proj(double* a, double* b, int size);
bool ChechkLinearIdependence(uint size, double** basis)
{
	uint rank = size;
	double eps = 1e-15;

	double** work = new double*[size];
	for (uint i = 0; i < size; i++)
	{
		work[i] = new double[size];
		memcpy(work[i], basis[i], sizeof(double)*size);
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
		memcpy(_basis[i], basis[i], sizeof(double)*_size);
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
		memcpy(result[i], _basis[i], sizeof(double)*_size);
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
		memcpy(_basis[i], basis[i], sizeof(double)*_size);
	}
}

double CalculateMu(double* a, double* b,int size)
{
	double scal_a_b = 0;
	double scal_b_b = 0;
	for (int i = 0; i < size; i++)
	{
		scal_a_b += a[i] * b[i];
		scal_b_b += b[i] * b[i];
	}
	return scal_a_b / scal_b_b;
}

double* Proj (double* a, double* b,int size)
{
	double mu = CalculateMu(a, b,size);
	double* proj = new double[size];
	for(int j = 0; j < size; j++)
	{
		proj[j] = mu * b[j];
	}
	return proj;
}

void Lattice::GramSchmidt()
{
	double** ort_vectors=new double*[_size];
	for (int i = 0; i < _size; i++)
	{
		ort_vectors[i]=new double[_size];
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
			double* proj = Proj(_basis[i], ort_vectors[k], _size);
			for (int p = 0;p < _size; p++)
			{
				ort_vectors[i][p] -= proj[p];
			}
			delete[] proj;
		}
	}

	this->SetBasis(_size, ort_vectors);
	
	for (uint i = 0; i < _size; i++)
		delete[] ort_vectors[i];
	delete[] ort_vectors;
}

double LenQuad(double* v, uint size)
{
	double result = 0;

	for (uint i = 0; i < size; i++) 
		result += v[i]*v[i];

	return result;
}

void Lattice::LLLalgorithm()
{
	this->GramSchmidt();
	//��� �����
}
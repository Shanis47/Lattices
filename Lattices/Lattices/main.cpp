#include "Lattice.h"
#include <iostream>
using namespace std;

int Menu();
Lattice* InputFromKeyboard();
Lattice* InputFromFile();
void PrintLattice(Lattice* );

int main()
{
	Lattice* lattice = new Lattice();

	while (int menuResult = Menu())
	{
		switch (menuResult)
		{
		case 1:
			delete lattice;
			lattice = InputFromKeyboard();
			break;
		case 2:
			delete lattice;
			lattice = InputFromFile();
			break;
		case 3:
			PrintLattice(lattice);
			break;
		default:
			cout << "Incorrect command" << endl;
		}
	}

	delete lattice;
	return 0;
}

int Menu()
{
	cout << "1. Input from keyboard" << endl;
	cout << "2. Input from file" << endl;
	cout << "3. Print lattice basis" << endl;
	cout << "0. Exit" << endl;
	int result;
	cin >> result;

	return result;
}

Lattice* InputFromKeyboard()
{
	int size;
	double** basis;
	cout << "size = ";
	cin >> size;
	basis = new double*[size];
	
	for (int i = 0; i < size; i++)
	{
		basis[i] = new double[size];
		for (int j = 0; j < size; j++)
			cin >> basis[i][j];
	}

	Lattice* result = new Lattice(size, basis);
	for (int i =0; i< size; i++)
		delete[] basis[i];
	delete[] basis;

	return result;
}

Lattice* InputFromFile()
{
	cout << "Sorry. It not works now :((" << endl;
	return NULL;
}

void PrintLattice(Lattice* lattice)
{
	int size = lattice->GetSize();
	double** basis = lattice->GetBasis();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << basis[i][j] << "\t";
		cout << endl;
	}

	for (int i =0; i< size; i++)
		delete[] basis[i];
	delete[] basis;
}
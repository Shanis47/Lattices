#include "Lattice.h"
#include <iostream>
using namespace std;

int Menu();

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
		case 4:
			{
				Lattice* ort_vect = new Lattice(lattice->GetSize(), lattice->GramSchmidt());
				PrintLattice(ort_vect);
				delete ort_vect;
				break;
			}
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
	cout << "4. Do GramSchmidt" << endl;
	cout << "0. Exit" << endl;
	int result;
	cin >> result;

	return result;
}

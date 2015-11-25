#include "LongReal.h"
#include <iostream>
using namespace std;

int Menu();

int main()
{
	LongReal a;
	while (int menuResult = Menu())
	{
		switch (menuResult)
		{
		case 1:
			cout << "enter LongReal" << endl;
			cin >> a;
			cout << a << endl;
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			cout << "Incorrect command" << endl;
		}
	}

	return 0;
}

int Menu()
{
	cout << "1. I/O test" << endl;
	cout << "2. Logical test" << endl;
	cout << "3. Arithmetic test" << endl;
	cout << "0. Exit" << endl;
	int result;
	cin >> result;

	return result;
}

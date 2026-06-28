#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

bool sadrziCifru5(int broj)
{
	while (broj > 0)
	{
		if (broj % 10 == 5)
		{
			return true;
		}
		broj /= 10;
	}
	return false;
}

bool sadrziCifru3(int broj)
{
	while (broj > 0)
	{
		if (broj % 10 == 3)
		{
			return true;
		}
		broj /= 10;
	}
	return false;
}

int getPrvaCifra(int broj)
{
	while (broj >= 10)
	{
		broj /= 10;
	}
	return broj;
}

int main()
{
	srand(time(0));

	int broj = 0;
	int sumaPrvihCifara = 0;
	int brojacValidnih = 0;

	while (true)
	{
		broj = rand() % 10000 + 1;

		cout << "Generisani broj: " << broj << endl;

		if (sadrziCifru5(broj))
		{
			cout << "Broj sadrzi cifru 5. Kraj programa!" << endl;
			break;
		}

		if (sadrziCifru3(broj))
		{
			cout << "Generisani broj se ne racuna ( sadrzi cifru 3 )." << endl;
			continue;
		}

		int prvaCifra = getPrvaCifra(broj);
		cout << "Prva cifra unesenog broja je: " << prvaCifra << endl;

		sumaPrvihCifara += prvaCifra;
		brojacValidnih++;
	}

	if (brojacValidnih > 0)
	{
		float prosjek = sumaPrvihCifara / brojacValidnih;
		cout << "Ukupni prosjek svih prvih cifri je: " << prosjek << endl;
	}
	else
	{
		cout << "Nije generisan nijedan validan broj prije pojave cifre 5." << endl;
	}

	return 0;
}
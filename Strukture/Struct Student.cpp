#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

char* unesiText(char* tekst)
{
	char temp[1000];
	cin.getline(temp, 1000);
	int duzinaTexta = strlen(temp) + 1;
	char* noviText = new char[duzinaTexta];
	strcpy_s(noviText, duzinaTexta, temp);
	return noviText;
}

struct Student {
	char* ime = nullptr;
	char* prezime = nullptr;
	int brojIndeksa = 0;
	char skola[40] = "";
	int brojSemestra = 0; // oznacava broj redova u dinamickoj matrici
	int brojUplata = 0; // oznacava broj kolona u dinamickoj matrici
	int** uplate = nullptr; // matrica dimenzija (brojSemestra x brojUplata)

	void unos()
	{
		cout << "Unesi ime studenta: ";
		ime = unesiText(ime);

		cout << "Unesi prezime studenta: ";
		prezime = unesiText(prezime);

		cout << "Unesi broj indexa: ";
		cin >> brojIndeksa;
		cin.ignore();

		cout << "Unesi skolu studenta: ";
		cin.getline(skola, size(skola));

		cout << "Unesi broj semestara: ";
		cin >> brojSemestra;

		cout << "Unesi broj uplata: ";
		cin >> brojUplata;

		uplate = new int* [brojSemestra];
		for (int i = 0; i < brojSemestra; i++)
		{
			*(uplate + i) = new int[brojUplata];

			for (int j = 0; j < brojUplata; j++)
			{
				*(*(uplate + i) + j) = rand() % 901 + 100;
			}
		}

	}

	void ispis()
	{
		cout << "Ime studenta: " << ime << endl;
		cout << "Prezime studenta: " << prezime << endl;
		cout << "Broj indeksa studenta: " << brojIndeksa << endl;
		cout << "Skola studenta: " << skola << endl;
		cout << "Broj semestra studenta: " << brojSemestra << endl;
		cout << "Broj uplata studenta: " << brojUplata << endl;

		cout << "==================" << endl;
		for (int i = 0; i < brojSemestra; i++)
		{
			for (int j = 0; j < brojUplata; j++)
			{
				cout << *(*(uplate + i) + j) << " KM ";
			}
			cout << endl;
		}
	}

	void dealokacija()
	{
		delete[] ime;
		ime = nullptr;
		delete[] prezime;
		prezime = nullptr;

		for (int i = 0; i < brojSemestra; i++)
		{
			delete[] *(uplate + i);
		}
		delete[] uplate;
		uplate = nullptr;


	}

	float* izracunajProsjekPoSemestrima()
	{
		float* prosjeci = new float[brojSemestra] {0.0f};

		for (int i = 0; i < brojSemestra; i++)
		{
			for (int j = 0; j < brojUplata; j++)
			{
				*(prosjeci + i) += *(*(uplate + i) + j);
			}
			*(prosjeci + i) /= brojUplata;
		}

		/*for (int i = 0; i < brojSemestra; i++)
		{
			cout << "Prosjek za " << i + 1 << ". semestar je " << *(prosjeci + i) << endl;
		}*/

		return prosjeci;
	}

};



int main()
{
	srand(time(0));
	Student* imeStudenta = new Student;
	imeStudenta->unos();
	imeStudenta->ispis();

	float* prosjek = imeStudenta->izracunajProsjekPoSemestrima();

	for (int i = 0; i < imeStudenta->brojSemestra; i++)
	{
		cout << "Prosjek za " << i + 1 << ". semestar je " << *(prosjek + i) << endl;
	}
	cout << endl;

	delete[] prosjek;
	prosjek = nullptr;

	imeStudenta->dealokacija();

	delete imeStudenta;
	imeStudenta = nullptr;

	return 0;
}

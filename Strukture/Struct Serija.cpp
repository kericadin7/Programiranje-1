#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

char* unesiText(char* tekst)
{
	char temp[200];
	cin.getline(temp, 200);
	int duzina = strlen(temp) + 1;
	char* text = new char[duzina];
	strcpy_s(text, duzina, temp);
	return text;
}

bool isGenreRight(const char* text)
{
	if ((strcmp("Crime", text)==0) || (strcmp("Romance", text) == 0) || (strcmp("Comedy", text) == 0))
	{
		return true;
	}
	return false;
}

struct Serija {
	char* imeSerije = nullptr;
	char* zanrSerije = nullptr; // dozvoliti unos samo "Crime", "Romance", "Comedy"
	char drzavaSnimanja[40] = "";
	int brojEpizoda = 0;
	int brojSezona = 0;
	int** ocjene = nullptr; // matrica dimenzija (brojSezona x brojEpizoda)

	void unos() {
		char temp[20];

		cout << "Unesi ime serije: ";
		imeSerije = unesiText(imeSerije);

		cout << "Unesi zanr serije: ";
		do
		{
			cin.getline(temp, 20);
			if (!isGenreRight(temp))
			{
				cout << "Pogresna kategorija serije! Kategorija moze biti samo Crime, Romance, Comedy!" << endl;
			}

		} while (!isGenreRight(temp));

		int duzinaZanra = strlen(temp) + 1;
		zanrSerije = new char[duzinaZanra];
		strcpy_s(zanrSerije, duzinaZanra, temp);

		cout << "Unesite drzavu snimanja: ";
		cin.getline(drzavaSnimanja, 40);

		cout << "Unesi broj epizoda: ";
		cin >> brojEpizoda;
		cout << "Unesi broj sezona: ";
		cin >> brojSezona;
		cin.ignore();

		ocjene = new int* [brojSezona];

		for (int i = 0; i < brojSezona; i++)
		{
			*(ocjene + i) = new int[brojEpizoda];
			for (int j = 0; j < brojEpizoda; j++)
			{
				*(*(ocjene + i) + j) = rand() % 10 + 1;
			}
		}

	}
	void ispis()
	{
		cout << "Ime serije: " << imeSerije << endl;
		cout << "Zanr serije: " << zanrSerije << endl;
		cout << "Drzava snimanja serije: " << drzavaSnimanja << endl;
		cout << "Broj epizoda serije: " << brojEpizoda << endl;
		cout << "Broj sezona serije: " << brojSezona << endl;
		cout << "------OCJENE------" << endl;

		for (int i = 0; i < brojSezona; i++)
		{
			for (int j = 0; j < brojEpizoda; j++)
			{
				cout << *(*(ocjene + i) + j) << " ";
			}
			cout << endl;
		}
		cout << "------------------" << endl;
		cout << endl;
	}

	void dealokacija() {
		delete[] imeSerije;
		imeSerije = nullptr;
		delete[] zanrSerije;
		zanrSerije = nullptr;

		for (int i = 0; i < brojSezona; i++)
		{
			delete[] * (ocjene + i);
		}
		delete[] ocjene;
		ocjene = nullptr;
	}
};

float* getAveragesBySeasons(Serija* niz, int velicina)
{
	float* prosjeci = new float[3]{ 0 };
	int brojac[3]{ 0 };

	for (int i = 0; i < velicina; i++)
	{
		for (int j = 0; j < (niz + i)->brojSezona; j++)
		{
			for (int k = 0; k < (niz + i)->brojEpizoda; k++)
			{
				if ((strcmp((niz + i)->zanrSerije, "Crime") == 0))
				{
					*prosjeci += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 0));
				}
				if ((strcmp((niz + i)->zanrSerije, "Romance") == 0))
				{
					*(prosjeci + 1) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 1));
				}
				if ((strcmp((niz + i)->zanrSerije, "Comedy") == 0))
				{
					*(prosjeci + 2) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 2));
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (*(brojac + i) > 0)
		{
			*(prosjeci + i) /= *(brojac + i);
		}
		else
		{
			*(prosjeci + i) = 0;
		}
	}

	return prosjeci;
}

int main()
{
	srand(time(0));

	int brojSerija = 0;
	do
	{
		cout << "Unesite broj serija: ";
		cin >> brojSerija;
	} while (brojSerija < 1);
	cin.ignore();

	Serija* niz = new Serija[brojSerija];
	for (int i = 0; i < brojSerija; i++)
	{
		(niz + i)->unos();
	}
	for (int i = 0; i < brojSerija; i++)
	{
		(niz + i)->ispis();
	}

	float* prosjeci = getAveragesBySeasons(niz, brojSerija);
	cout << "Prosjeci po zanrovima: " << endl;
	cout << "Prosjeci za Crime: " << *(prosjeci) << endl;
	cout << "Prosjeci za Romance: " << *(prosjeci + 1) << endl;
	cout << "Prosjeci za Comedy: " << *(prosjeci + 2) << endl;

	for (int i = 0; i < brojSerija; i++)
	{
		(niz + i)->dealokacija();
	}
	delete[] prosjeci;
	prosjeci = nullptr;

	delete[] niz;
	niz = nullptr;

	return 0;
}
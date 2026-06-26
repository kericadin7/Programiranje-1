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
	if ((strcmp("War", text)==0) || (strcmp("Strategy", text) == 0) || (strcmp("Open World", text) == 0))
	{
		return true;
	}
	return false;
}

struct Igrica {
	char* imeIgrice = nullptr;
	char* zanrIgrice = nullptr; // dozvoli unos samo "War", "Strategy", "Open World"
	char izdavac[40] = "";
	int brojDijelova = 0;
	int brojKriticara = 0;
	int** ocjene = nullptr;

	void unos()
	{
		char temp[20];
		cout << "Unesi ime igrice: ";
		imeIgrice = unesiText(imeIgrice);

		cout << "Unesi zanr igrice: ";
		do
		{
			cin.getline(temp, 20);
			if (!isGenreRight(temp))
			{
				cout << "Pogresna kategorija! Kategorija moze biti samo War, Strategy, Open World!" << endl;
			}
		} while (!isGenreRight(temp));
		
		int duzinaZanra = strlen(temp) + 1;
		zanrIgrice = new char[duzinaZanra];
		strcpy_s(zanrIgrice, duzinaZanra, temp);

		cout << "Unesite izdavaca: ";
		cin.getline(izdavac, 40);

		cout << "Unesi broj dijelova: ";
		cin >> brojDijelova;
		cout << "Unesi broj kriticara: ";
		cin >> brojKriticara;
		cin.ignore();

		ocjene = new int* [brojDijelova];

		for (int i = 0; i < brojDijelova; i++)
		{
			*(ocjene + i) = new int[brojKriticara];
			for (int j = 0; j < brojKriticara; j++)
			{
				*(*(ocjene + i) + j) = rand() % 10 + 1;
			}
		}
	}

	void ispis()
	{
		cout << "Ime igrice: " << imeIgrice << endl;
		cout << "Zanr igrice: " << zanrIgrice << endl;
		cout << "Izdavac igrice: " << izdavac << endl;
		cout << "Broj djelova igrice: " << brojDijelova << endl;
		cout << "Broj kriticara igrice: " << brojKriticara << endl;
		cout << "------OCJENE------" << endl;

		for (int i = 0; i < brojDijelova; i++)
		{
			for (int j = 0; j < brojKriticara; j++)
			{
				cout << *(*(ocjene + i) + j) << " ";
			}
			cout << endl;
		}
		cout << "------------------" << endl;
		cout << endl;
	}

	void dealokacija()
	{
		delete[] imeIgrice;
		imeIgrice = nullptr;
		delete[] zanrIgrice;
		zanrIgrice = nullptr;

		for (int i = 0; i < brojDijelova; i++)
		{
			delete[] * (ocjene + i);
		}
		delete[] ocjene;
		ocjene = nullptr;
	}
};

float* getAverageByGenre(Igrica* niz, int velicina)
{
	float* prosjeci = new float[3] {0};
	int brojac[3]{ 0 };

	for (int i = 0; i < velicina; i++)
	{
		for (int j = 0; j < (niz + i)->brojDijelova; j++)
		{
			for (int k = 0; k < (niz + i)->brojKriticara; k++)
			{
				if (strcmp((niz + i)->zanrIgrice, "War") == 0) {
					*prosjeci += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 0));
				}
				else if (strcmp((niz + i)->zanrIgrice, "Strategy") == 0) {
					*(prosjeci + 1) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 1));
				}
				else if (strcmp((niz + i)->zanrIgrice, "Open World") == 0) {
					*(prosjeci + 2) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 2));
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (*(brojac + i) > 0) {
			*(prosjeci + i) /= *(brojac + i);
		}
		else {
			*(prosjeci + i) = 0;
		}
	}

	return prosjeci;
};

int main()
{
	srand(time(0));

	int brojIgrica = 0;
	do
	{
		cout << "Unesite broj igrica: ";
		cin >> brojIgrica;
	} while (brojIgrica <1);
	cin.ignore();

	Igrica* niz = new Igrica[brojIgrica];
	for (int i = 0; i < brojIgrica; i++)
	{
		(niz + i)->unos();
	}
	for (int i = 0; i < brojIgrica; i++)
	{
		(niz + i)->ispis();
	}

	float* prosjeci = getAverageByGenre(niz, brojIgrica);
	cout << "Prosjeci po zanrovima: " << endl;
	cout << "Prosjek za War: " << *(prosjeci) << endl;
	cout << "Prosjek za Strategy: " << *(prosjeci + 1) << endl;
	cout << "Prosjek za Open World: " << *(prosjeci + 2) << endl;

	for (int i = 0; i < brojIgrica; i++)
	{
		(niz + i)->dealokacija();
	}
	delete[] prosjeci;
	prosjeci = nullptr;

	delete[] niz;
	niz = nullptr;

	return 0;
}
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

char* unesiText(char* tekst)
{
	char temp[200];
	cin.getline(temp, 200);
	int duzinaTexta = strlen(temp) + 1;
	char* noviText = new char[duzinaTexta];
	strcpy_s(noviText, duzinaTexta, temp);
	return noviText;
}

bool isCategoryRight(const char* noviText)
{
	if ((strcmp("Tjestenina", noviText) == 0) || (strcmp("Tradicionalno", noviText) == 0) || (strcmp("Fast Food", noviText) == 0))
	{
		return true;
	}
	return false;
}

struct Jelo {
	char* imeJela = nullptr;
	char* kategorijaJela = nullptr; // Kategorija moze biti samo Tjestenina, Tradicionalno, Fast Food
	char imeKuhara[40] = "";
	int brojVarijacija = 0;
	int brojKriticara = 0;
	int** ocjene = nullptr;

	void unos()
	{
		char temp[20];

		cout << "Unesi ime jela: ";
		imeJela = unesiText(imeJela);

		cout << "Unesi kategoriju jela: ";
		do
		{
			cin.getline(temp, 20);
			if (!isCategoryRight(temp))
			{
				cout << "Pogresna kategorija! Kategorija moze biti samo Tjestenina, Tradicionalno, Fast Food!" << endl;
			}
		} while (!isCategoryRight(temp));

		int duzinaKategorije = strlen(temp) + 1;
		kategorijaJela = new char[duzinaKategorije];
		strcpy_s(kategorijaJela, duzinaKategorije, temp);

		cout << "Unesi ime kuhara: ";
		cin.getline(imeKuhara, size(imeKuhara));

		cout << "Unesi broj varijacija jela: ";
		cin >> brojVarijacija;
		cin.ignore();

		cout << "Unesi broj kriticara: ";
		cin >> brojKriticara;
		cin.ignore();

		ocjene = new int* [brojVarijacija];

		for (int i = 0; i < brojVarijacija; i++)
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
		cout << "Ime jela: " << imeJela << endl;
		cout << "Kategorija jela: " << kategorijaJela << endl;
		cout << "Ime kuhara: " << imeKuhara << endl;
		cout << "Broj varijacija jela: " << brojVarijacija << endl;
		cout << "Broj kriticara: " << brojKriticara << endl;
		cout << "======OCJENE======" << endl;

		for (int i = 0; i < brojVarijacija; i++)
		{
			for (int j = 0; j < brojKriticara; j++)
			{
				cout << *(*(ocjene + i) + j) << " ";
			}
			cout << endl;
		}
		cout << "==================" << endl;
		cout << endl;
	}

	void dealokacija()
	{
		delete[] imeJela;
		imeJela = nullptr;
		delete[] kategorijaJela;
		kategorijaJela = nullptr;

		for (int i = 0; i < brojVarijacija; i++)
		{
			delete[] * (ocjene + i);
		}

		delete[] ocjene;
		ocjene = nullptr;
	}
};

float* getAverageByCategory(Jelo* niz, int velicina)
{
	float* prosjek = new float[3] {0};
	int brojac[3]{ 0 };

	for (int i = 0; i < velicina; i++)
	{
		for (int j = 0; j < (niz + i)->brojVarijacija; j++)
		{
			for (int k	 = 0; k < (niz + i)->brojKriticara; k++)
			{
				if ((strcmp((niz + i)->kategorijaJela, "Tjestenina") == 0))
				{
					*prosjek += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 0));
				}
				else if ((strcmp((niz + i)->kategorijaJela, "Tradicionalno") == 0))
				{
					*(prosjek + 1) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 1));
				}
				else if ((strcmp((niz + i)->kategorijaJela, "Fast Food") == 0))
				{
					*(prosjek + 2) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 2));
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (*(brojac + i) > 0)
		{
			*(prosjek + i) /= *(brojac + i);
		}
		else
		{
			*(prosjek + i) = 0;
		}
	}

	return prosjek;
}

int main()
{
	srand(time(0));

	int brojJela = 0;
	do
	{
		cout << "Unesite broj jela: ";
		cin >> brojJela;
	} while (brojJela < 1);
	cin.ignore();

	Jelo* izborJela = new Jelo[brojJela];

	for (int i = 0; i < brojJela; i++)
	{
		(izborJela + i)->unos();
	}

	for (int i = 0; i < brojJela; i++)
	{
		(izborJela + i)->ispis();
	}

	float* prosjek = getAverageByCategory(izborJela, brojJela);
	cout << "=== Prosjeci po kategoriji === " << endl;
	cout << "Prosjeci za Tjesteninu: " << *(prosjek) << endl;
	cout << "Prosjeci za Tradicionalno: " << *(prosjek + 1) << endl;
	cout << "Prosjeci za Fast Food: " << *(prosjek + 2) << endl;

	for (int i = 0; i < brojJela; i++)
	{
		(izborJela + i)->dealokacija();
	}

	delete[] prosjek;
	prosjek = nullptr;

	delete[] izborJela;
	izborJela = nullptr;

	return 0;
}
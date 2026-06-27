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

bool isGenreRight(const char* noviText)
{
	if ((strcmp(noviText, "Komedija") == 0) || (strcmp(noviText, "Tragedija") == 0) || (strcmp(noviText, "Tragikomedija") == 0))
	{
		return true;
	}
	return false;
}

struct Predstava {
	char* imePredstave = nullptr;
	char* kategorijaPredstave = nullptr; // dozvoliti unos samo "Komedija", "Tragedija", "Tragikomedija"
	char imeRezisera[40] = "";
	int brojVarijacija = 0;
	int brojKriticara = 0;
	int** ocjene = nullptr; // matrica brojVarijacija * brojKriticara

	void unos() 
	{
		char temp[20];

		cout << "Unesi ime predstave: ";
		imePredstave = unesiText(imePredstave);

		cout << "Unesi kategoriju predstave: ";
		do
		{
			cin.getline(temp, 20);
			if (!isGenreRight(temp))
			{
				cout << "Pogresna kategorija predstave! Kategorija moze biti samo Komedija, Tragedija, Tragikomedija" << endl;
			}
		} while (!isGenreRight(temp));

		int duzinaKategorije = strlen(temp) + 1;
		kategorijaPredstave = new char[duzinaKategorije];
		strcpy_s(kategorijaPredstave, duzinaKategorije, temp);

		cout << "Unesi ime rezisera: ";
		cin.getline(imeRezisera, size(imeRezisera));

		cout << "Unesi broj varijacija predstave: ";
		cin >> brojVarijacija;
		cin.ignore();

		cout << "Unesi broj kriticara: ";
		cin >> brojKriticara;
		cin.ignore();

		ocjene = new int* [brojVarijacija];

		for (int i = 0; i < brojVarijacija; i++)
		{
			*(ocjene + i) = new int [brojKriticara];
			for (int j = 0; j < brojKriticara; j++)
			{
				*(*(ocjene + i) + j) = rand() % 10 + 1;
			}
		}
	}

	void ispis()
	{
		cout << "Ime predstave: " << imePredstave << endl;
		cout << "Kategorija predstave: " << kategorijaPredstave << endl;
		cout << "Ime rezisera: " << imeRezisera << endl;
		cout << "Broj varijacija predstave: " << brojVarijacija << endl;
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
		delete[] imePredstave;
		imePredstave = nullptr;

		delete[] kategorijaPredstave;
		kategorijaPredstave = nullptr;

		for (int i = 0; i < brojVarijacija; i++)
		{
			delete[] * (ocjene + i);
		}

		delete[] ocjene;
		ocjene = nullptr;
	}

};

float* getAverageByCategory(Predstava* niz, int velNiza)
{
	float* prosjek = new float[3] {0};
	int brojac[3]{ 0 };

	for (int i = 0; i < velNiza; i++)
	{
		for (int j = 0; j < (niz + i)->brojVarijacija; j++)
		{
			for (int k = 0; k < (niz + i)->brojKriticara; k++)
			{
				if ((strcmp((niz + i)->kategorijaPredstave, "Komedija") == 0))
				{
					*(prosjek) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 0));
				}
				else if ((strcmp((niz + i)->kategorijaPredstave, "Tragedija") == 0))
				{
					*(prosjek + 1) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 1));
				}
				else if ((strcmp((niz + i)->kategorijaPredstave, "Tragikomedija") == 0))
				{
					*(prosjek + 2) += *(*((niz + i)->ocjene + j) + k);
					++(*(brojac + 2));
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (*(brojac+i) > 0)
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

	int brojPredstava = 0;
	do
	{
		cout << "Unesite broj predstava: ";
		cin >> brojPredstava;
	} while (brojPredstava < 1);
	cin.ignore();

	Predstava* izborPredstave = new Predstava[brojPredstava];

	for (int i = 0; i < brojPredstava; i++)
	{
		(izborPredstave + i)->unos();
	}
	for (int i = 0; i < brojPredstava; i++)
	{
		(izborPredstave + i)->ispis();
	}

	float* prosjek = getAverageByCategory(izborPredstave, brojPredstava);
	cout << "=== Prosjeci po kategoriji === " << endl;
	cout << "Prosjeci za Komediju: " << *(prosjek) << endl;
	cout << "Prosjeci za Tragediju: " << *(prosjek + 1) << endl;
	cout << "Prosjeci za Tragikomediju: " << *(prosjek + 2) << endl;

	for (int i = 0; i < brojPredstava; i++)
	{
		(izborPredstave + i)->dealokacija();
	}

	delete[] izborPredstave;
	izborPredstave = nullptr;

	delete prosjek;
	prosjek = nullptr;

	return 0;
}
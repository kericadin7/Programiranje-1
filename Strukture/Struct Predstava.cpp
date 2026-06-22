#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

char* createText(int size)
{
	return new char[size];
}

char* createTextFrom(const char* source)
{
	if (source == nullptr)
		return nullptr;

	int size = strlen(source) + 1;
	char* text = createText(size);
	strcpy_s(text, size, source);

	return text;
}

int** createMatrix(int rows, int columns)
{
	int** m = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		m[i] = new int[columns];
	}
	return m;
}

void deleteMatrix(int** m, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] m[i];
		m[i] = nullptr;
	}
	delete[] m;
	m = nullptr;
}

bool isGenreRight(const char* text)
{
	if ((strcmp("Komedija", text) == 0) || (strcmp("Tragedija", text) == 0) || (strcmp("Tragikomedija", text) == 0))
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
	int** ocjene = nullptr; // matrica brojVarijacija* brojKriticara

	void unos()
	{
		char temp[250];

		cin.ignore();

		cout << "Unesite ime predstave: " << endl;
		cin.getline(temp, size(temp));

		imePredstave = createTextFrom(temp);

		cout << "Unesite kategoriju predstave: " << endl;
		do
		{
			cin.getline(temp, size(temp));
			if (!isGenreRight(temp))
			{
				cout << "Pogresna kategorija! Kategorija moze biti samo Komedija, Tragedija, Tragikomedija!" << endl;
			}
		} while (!isGenreRight(temp));
		kategorijaPredstave = createTextFrom(temp);

		cout << "Unesite ime rezisera: " << endl;
		cin.getline(imeRezisera, size(imeRezisera));

		do
		{
			cout << "Unesite broj varijacija predstave: " << endl;
			cin >> brojVarijacija;
		} while (brojVarijacija < 1);

		do
		{
			cout << "Unesite broj kriticara predstave: " << endl;
			cin >> brojKriticara;
		} while (brojKriticara < 1);

		ocjene = createMatrix(brojVarijacija, brojKriticara);

		for (int i = 0; i < brojVarijacija; i++)
		{
			for (int j = 0; j < brojKriticara; j++)
			{
				*(*(ocjene + i) + j) = rand() % 10 + 1; // obavezno pointere
			}
		}
	}

	void ispis()
	{
		cout << "=====================================" << endl;
		cout << "Ime predstave: " << imePredstave << endl;
		cout << "Kategorija predstave: " << kategorijaPredstave << endl;
		cout << "Ime rezisera predstave: " << imeRezisera << endl;
		cout << "Broj varijacija predstave: " << brojVarijacija << endl;
		cout << "Broj kriticara predstave: " << brojKriticara << endl;
		cout << "Ocjene: " << endl;
		cout << "-------------------------------------" << endl;
		for (int i = 0; i < brojVarijacija; i++)
		{
			cout << "Predstava broj: " << i + 1 << " -> ";
			for (int j = 0; j < brojKriticara; j++)
			{
				cout << "Kriticar " << j + 1 << " ocjena:";
				cout << setw(3) << *(*(ocjene + i) + j) << " | "; // obavezno pointere
			}
			cout << endl;
		}
		cout << "-------------------------------------" << endl;
		cout << "=====================================" << endl;
	}

	void dealokacija()
	{
		delete[] imePredstave;
		imePredstave = nullptr;

		delete[] kategorijaPredstave;
		kategorijaPredstave = nullptr;

		deleteMatrix(ocjene, brojVarijacija);
	}

};

float* getAverageByCategory(Predstava* niz, int velNiza)
{
	float* prosjeciZanrova = new float[3] {0.0f};

	int brojPredstava[3] = { 0 }; // ovdje spremam broj predstava po kategoriji

	for (int i = 0; i < velNiza; i++) // velNiza je ukupan broj predstava koje imam
	{
		float ukupniProsjek = 0.0f; // ukupan prosjek za svaku predstavu pojedinacno

		for (int j = 0; j < niz[i].brojVarijacija; j++) // trebam za svaku pojedinacnu predstavu da vidim ocjene, zato koristim niz[i]
		{
			float suma = 0.0f; // spremam sumu ocjena za jednu predstavu
			for (int k = 0; k < niz[i].brojKriticara; k++)
			{
				suma += niz[i].ocjene[j][k]; // sve ocjene za jednu predstavu od raznih kriticara spremile su se u ovu sumu
			}
			ukupniProsjek += suma / niz[i].brojKriticara; // ukupan prosjek za pojedinacnu trenutnu predstavu je suma ocjena koju su dali svi kriticari kroz broj kriticara
		}

		ukupniProsjek /= niz[i].brojVarijacija; // trebamo dijeliti sa brojem redova da dobijemo konacni prosjek koji ce se dodavati na kraju

		if (strcmp(niz[i].kategorijaPredstave, "Komedija") == 0)
		{
			prosjeciZanrova[0] += ukupniProsjek;
			brojPredstava[0]++;
		}

		else if (strcmp(niz[i].kategorijaPredstave, "Tragedija") == 0)
		{
			prosjeciZanrova[1] += ukupniProsjek;
			brojPredstava[1]++;
		}

		else if (strcmp(niz[i].kategorijaPredstave, "Tragikomedija") == 0)
		{
			prosjeciZanrova[2] += ukupniProsjek;
			brojPredstava[2]++;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (brojPredstava[i] > 0)
		{
			prosjeciZanrova[i] /= brojPredstava[i];
		}
	}
	return prosjeciZanrova;

}

int main()
{
	srand(time(0));

	int brojPredstava = 0;

	do
	{
		cout << "Unesite broj predstava: " << endl;
		cin >> brojPredstava;
	} while (brojPredstava < 1);

	Predstava* predstave = new Predstava[brojPredstava];

	for (int i = 0; i < brojPredstava; i++)
	{
		(predstave + i)->unos();
	}

	for (int i = 0; i < brojPredstava; i++)
	{
		(predstave + i)->ispis();
	}

	float* prosjeciZanrova = getAverageByCategory(predstave, brojPredstava);
	cout << "Prosjecne ocjene po kategoriji predstave su: " << endl;
	cout << "Komedija: " << *prosjeciZanrova << endl;
	cout << "Tragedija: " << *(prosjeciZanrova + 1) << endl;
	cout << "Tragikomedija: " << *(prosjeciZanrova + 2) << endl;

	delete[] prosjeciZanrova;
	prosjeciZanrova = nullptr;

	for (int i = 0; i < brojPredstava; i++)
	{
		(predstave + i)->dealokacija();
	}

	delete[] predstave;
	predstave = nullptr;


	return 0;
}

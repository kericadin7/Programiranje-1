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

void deleteMatrix(int** m,int rows)
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
	if ( (strcmp("Komedija", text)==0) || (strcmp("Tragedija", text)==0) || (strcmp("Tragikomedija", text)==0))
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
				cout << "Pogresna kategorija ! Kategorija moze biti samo Komedija, Tragedija ili Tragikomedija !" << endl;
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
				*(*(ocjene + i) + j) = rand() % 10 + 1;
			}
		}
	}

	void ispis()
	{
		cout << "========================================" << endl;
		cout << "Ime predstave: "<< imePredstave << endl;
		cout << "Kategorija predstave: " << kategorijaPredstave << endl;
		cout << "Ime rezisera predstave: " << imeRezisera << endl;
		cout << "Broj varijacija predstave: " << brojVarijacija << endl;
		cout << "Broj kriticara predstave: " << brojKriticara << endl;
		cout << "Ocjene: " << endl;
		cout << "========================================" << endl;

		for (int i = 0; i < brojVarijacija; i++)
		{
			cout << "Predstava broj: " << i + 1 << endl;
			for (int j = 0; j < brojKriticara; j++)
			{
				cout << "Kriticar: " << j + 1 << "Ocjena: " << setw(3) << *(*(ocjene + i) + j) << " | ";
			}
			cout << endl;
		}
		cout << "========================================" << endl;
		cout << "========================================" << endl;
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

}
//{
//	float* prosjeciZanrova = new float[3] {0.0f};
//
//	int brojPredstava[3] = { 0 };
//
//	for (int i = 0; i < velNiza; i++)
//	{
//		float ukupniProsjek = 0.0f;
//
//		for (int j = 0; j < niz[i].brojVarijacija; j++)
//		{
//			float suma = 0;
//			for (int k = 0; k < niz[i].brojKriticara; k++)
//			{
//				suma += niz[i].ocjene[j][k];
//			}
//			ukupniProsjek += suma / niz[i].brojKriticara;
//		}
//		ukupniProsjek /= niz[i].brojVarijacija;
//	}
//}

int main()
{
	srand(time(0));


	/*int brojPredstava = 0;

	do
	{
		cout << "Unesite broj predstava: " << endl;
		cin >> brojPredstava;
	} while (brojPredstava < 1);

	Predstava* nizPredstava = new Predstava[brojPredstava];

	for (int i = 0; i < brojPredstava; i++)
	{
		(nizPredstava + i)->unos();
	}

	for (int i = 0; i < brojPredstava; i++)
	{
		(nizPredstava + i)->ispis();
	}*/

	cout << "Prosjecne ocjene po kategorijama predstave: " << endl;
	/*cout << "Komedija: " << *getAverageByCategory << '\n';
	cout << "Tragedija: " << *(getAverageByCategory + 1) << '\n';
	cout << "Tragikomedija: " << *(getAverageByCategory + 2) << '\n';*/
	cout << "============================================================\n";


	return 0;
}
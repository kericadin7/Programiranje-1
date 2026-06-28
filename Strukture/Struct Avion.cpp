#include <iostream>
#include <iomanip>
#include <ctime>

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

bool isKategorijaRight(const char* noviText)
{
	if ((strcmp(noviText, "Borbeni Avion")==0) || (strcmp(noviText, "Putnicki Avion") == 0) || (strcmp(noviText, "Kargo Avion") == 0))
	{
		return true;
	}
	return false;
}

struct Avion {
	char* imeAviona = nullptr;
	char* kategorijaAviona = nullptr; // dozvoliti unos samo "Borbeni Avion", "Putnicki Avion", "Kargo Avion"
	char proizvodacAviona[40] = "";
	int brojSerija = 0;
	int brojPilota = 0;
	int** ocjene = nullptr; // matrica dimenzija (brojSerija * brojPilota)

	void unos() {
		char temp[50];

		cout << "Unesi ime aviona: ";
		imeAviona = unesiText(imeAviona);

		do
		{
			cout << "Unesi kategoriju Aviona: ";
			cin.getline(temp, size(temp));

			if (!isKategorijaRight(temp))
			{
				cout << "Pogresna kategorija! Kategorija moze biti samo Borbeni Avion, Putnicki Avion, Kargo Avion" << endl;
			}
		} while (!isKategorijaRight(temp));

		int duzinaKategorije = strlen(temp) + 1;
		kategorijaAviona = new char[duzinaKategorije];
		strcpy_s(kategorijaAviona, duzinaKategorije, temp);

		cout << "Unesi proizvodjaca aviona: ";
		cin.getline(proizvodacAviona, size(proizvodacAviona));

		cout << "Unesi broj serija: ";
		cin >> brojSerija;
		cin.ignore();


		cout << "Unesi broj pilota: ";
		cin >> brojPilota;
		cin.ignore();

		ocjene = new int* [brojSerija];

		for (int i = 0; i < brojSerija; i++)
		{
			*(ocjene + i) = new int[brojPilota];

			for (int j = 0; j < brojPilota; j++)
			{
				*(*(ocjene + i) + j) = rand() % 10 + 1;
			}
		}
	}

	void ispis()
	{
		cout << "Ime aviona: " << imeAviona << endl;
		cout << "Kategorija aviona: " << kategorijaAviona << endl;
		cout << "Proizvodjac aviona: " << proizvodacAviona << endl;
		cout << "Broj serija: " << brojSerija << endl;
		cout << "Broj pilota: " << brojPilota << endl;

		cout << "======OCJENE====== " << endl;

		for (int i = 0; i < brojSerija; i++)
		{
			for (int j = 0; j < brojPilota; j++)
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
		delete[] imeAviona;
		imeAviona = nullptr;

		delete[] kategorijaAviona;
		kategorijaAviona = nullptr;

		for (int i = 0; i < brojSerija; i++)
		{
			delete[] * (ocjene + i);
		}

		delete[] ocjene;
		ocjene = nullptr;
	}

	float* getAveragesBySeries()
	{
		float* prosjeciSerija = new float[brojSerija] {0};

		for (int i = 0; i < brojSerija; i++)
		{
			float suma = 0;
			for (int j = 0; j < brojPilota; j++)
			{
				suma += *(*(ocjene + i) + j);
			}
			*(prosjeciSerija + i) = suma / brojPilota;
		}
		return prosjeciSerija;
	}

	float* getAveragesByDiagonal()
	{
		float* prosjeciDijagonala = new float[2] {0};
		float sumaGlavna = 0;
		float sumaSporedna = 0;

		for (int i = 0; i < brojSerija; i++)
		{
			sumaGlavna += *(*(ocjene + i) + i);
			sumaSporedna += *(*(ocjene + i) + (brojSerija - 1 - i));
		}
		
		*(prosjeciDijagonala + 0) = sumaGlavna / brojSerija;
		*(prosjeciDijagonala + 1) = sumaSporedna / brojSerija;

		return prosjeciDijagonala;
	}

};

int main()
{
	srand(time(0));

	int brojAviona = 0;
	do
	{
		cout << "Unesite broj aviona u nizu: " << " ";
		cin >> brojAviona;
	} while (brojAviona < 1);
	
	cin.ignore();

	Avion* noviAvion = new Avion[brojAviona];

	for (int i = 0; i < brojAviona; i++)
	{
		cout << "Unos podataka za avion " << i + 1;
		(noviAvion + i)->unos();
	}

	for (int i = 0; i < brojAviona; i++)
	{
		cout << "Unos podataka za avion " << i + 1;
		(noviAvion + i)->ispis();
	}

	for (int i = 0; i < brojAviona; i++)
	{
		Avion* trenutni = (noviAvion + i);
		cout << "Avion: " << trenutni->imeAviona << endl;

		// Zahtjev 1: Ako je broj serija RAZLIČIT od broja pilota -> prosjek po svakoj seriji
		if (trenutni->brojSerija != trenutni->brojPilota)
		{
			float* prosjeciSerija = trenutni->getAveragesBySeries();
			if (prosjeciSerija != nullptr)
			{
				cout << "-> Prosjeci ocjena po serijama (redovima): " << endl;
				for (int s = 0; s < trenutni->brojSerija; s++)
				{
					cout << "   Serija " << s + 1 << ": " << *(prosjeciSerija + s) << endl;
				}
				delete[] prosjeciSerija;
			}
		}
		// Zahtjev 2: Ako je broj serija JEDNAK broju pilota -> prosjek po glavnoj i sporednoj dijagonali
		else
		{
			float* prosjeciDijagonala = trenutni->getAveragesByDiagonal();
			if (prosjeciDijagonala != nullptr)
			{
				cout << "-> Matrica je kvadratna (" << trenutni->brojSerija << "x" << trenutni->brojPilota << ")" << endl;
				cout << "   Prosjek glavne dijagonale: " << *(prosjeciDijagonala + 0) << endl;
				cout << "   Prosjek sporedne dijagonale: " << *(prosjeciDijagonala + 1) << endl;
				delete[] prosjeciDijagonala;
			}
		}
		cout << "------------------------------------------" << endl;
	}

	for (int i = 0; i < brojAviona; i++)
	{
		cout << "Unos podataka za avion " << i + 1;
		(noviAvion + i)->dealokacija();
	}

	delete[] noviAvion;
	noviAvion = nullptr;

	return 0;
}
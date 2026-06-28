#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

char* unesiText(char* tekst)
{
	char temp[250];
	cin.getline(temp, 250);
	int duzinaTexta = strlen(temp) + 1;
	char* noviText = new char[duzinaTexta];
	strcpy_s(noviText, duzinaTexta, temp);
	return noviText;
}

bool isKategorijaRight(const char* noviText)
{
	if ( (strcmp(noviText, "Fiction")==0) || (strcmp(noviText, "Non-Fiction") == 0) || (strcmp(noviText, "Mystery") == 0))
	{
		return true;
	}
	return false;
}

struct Knjiga {
	char* imeKnjige = nullptr;
	char* kategorijaKnjige = nullptr; // dozvoliti unos samo "Fiction", "Non-Fiction", "Mystery"
	char izdavac[40] = "";
	int brojDijelova = 0;
	int brojCitatelja = 0;
	int** ocjene = nullptr; // matrica dimenzija (brojDijelova x brojCitatelja)

	void unos()
	{
		char temp[50];

		cout << "Unesi ime knjige: ";
		imeKnjige = unesiText(imeKnjige);

		cout << "Unesi kategoriju knjige: ";
		do
		{
			cin.getline(temp, 50);
			if (!isKategorijaRight(temp))
			{
				cout << "Pogresna kategorija! Kategorija moze biti samo Fiction, Non-Fiction, Mystery" << endl;
			}
		} while (!isKategorijaRight(temp));

		int duzinaKategorije = strlen(temp) + 1;
		kategorijaKnjige = new char[duzinaKategorije];
		strcpy_s(kategorijaKnjige, duzinaKategorije, temp);

		cout << "Unesi izdavaca: ";
		cin.getline(izdavac, size(izdavac));

		cout << "Unesi broj dijelova: ";
		cin >> brojDijelova;
		cin.ignore();

		cout << "Unesi broj citatelja: ";
		cin >> brojCitatelja;
		cin.ignore();

		ocjene = new int* [brojDijelova];
		for (int i = 0; i < brojDijelova; i++)
		{
			*(ocjene + i) = new int[brojCitatelja];
			for (int j = 0; j < brojCitatelja; j++)
			{
				*(*(ocjene + i) + j) = rand() % 5 + 1;
			}
		}
	}

	void ispis()
	{
		cout << "Ime knjige: " << imeKnjige << endl;
		cout << "Kategorija knjige: " << kategorijaKnjige << endl;
		cout << "Izdavac knjige: " << izdavac << endl;
		cout << "Broj dijelova knjige: " << brojDijelova << endl;
		cout << "Broj citatelja knjige: " << brojCitatelja << endl;
		cout << "======OCJENE======" << endl;

		for (int i = 0; i < brojDijelova; i++)
		{
			for (int j = 0; j < brojCitatelja; j++)
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
		delete[] imeKnjige;
		imeKnjige = nullptr;

		delete[] kategorijaKnjige;
		kategorijaKnjige = nullptr;

		for (int i = 0; i < brojDijelova; i++)
		{
			delete[] * (ocjene + i);
		}

		delete[] ocjene;
		ocjene = nullptr; 
	}

};

float* getAverageByCategory(Knjiga* niz, int velNiza)
{
	float* prosjeci = new float[3] {0};
	int brojac[3]{ 0 };

	for (int i = 0; i < velNiza; i++)
	{
		float ukupniProsjek = 0;
		for (int j = 0; j < (niz + i)->brojDijelova; j++)
		{
			float suma = 0.0f;
			for (int k = 0; k < (niz+i)->brojCitatelja; k++)
			{
				suma += *(*((niz + i)->ocjene + j) + k);
			}
			ukupniProsjek += suma / (niz + i)->brojCitatelja;
		}
		ukupniProsjek /= (niz + i)->brojDijelova;

		if ((strcmp((niz+i)->kategorijaKnjige, "Fiction") == 0))
		{
			*(prosjeci + 0) += ukupniProsjek;
			++(*(brojac + 0));
		}
		else if ((strcmp((niz + i)->kategorijaKnjige, "Non-Fiction") == 0))
		{
			*(prosjeci + 1) += ukupniProsjek;
			++(*(brojac + 1));
		}
		else if ((strcmp((niz + i)->kategorijaKnjige, "Mystery") == 0))
		{
			*(prosjeci + 2) += ukupniProsjek;
			++(*(brojac + 2));
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (*(brojac + i) > 0)
		{
			*(prosjeci + i) /= *(brojac + i);
		}
		return prosjeci;
	}
	
}

int main()
{
	srand(time(0));

	int brojKnjiga = 0;
	do
	{
		cout << "Unesi broj knjiga: ";
		cin >> brojKnjiga;
	} while (brojKnjiga < 1);
	cin.ignore();

	Knjiga* knjiga = new Knjiga;

	for (int i = 0; i < brojKnjiga; i++)
	{
		(knjiga + i)->unos();
	}

	for (int i = 0; i < brojKnjiga; i++)
	{
		(knjiga + i)->ispis();
	}

	float* prosjek = getAverageByCategory(knjiga, brojKnjiga);
	cout << "====== Prosjeci po kategoriji ======" << endl;
	cout << "Prosjeci za Fiction: " << *(prosjek) << endl;
	cout << "Prosjeci za Non-Fiction: " << *(prosjek + 1) << endl;
	cout << "Prosjeci za Mystery: " << *(prosjek + 2) << endl;

	for (int i = 0; i < brojKnjiga; i++)
	{
		(knjiga + i)->dealokacija();
	}

	delete[] knjiga;
	knjiga = nullptr;

	delete prosjek;
	prosjek = nullptr;

	return 0;
}
#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>

using namespace std;

char* getTextCopy(const char* const src) {
	if (src == nullptr) {
		return nullptr;
	}

	const size_t size = strlen(src) + 1;
	char* const copy = new char[size];
	strcpy_s(copy, size, src);

	return copy;
}

bool daLiJeKategorijaValidna(const char* const zanrSerije) {
	return strcmp(zanrSerije, "Tjestenina") == 0
		|| strcmp(zanrSerije, "Tradicionalna") == 0
		|| strcmp(zanrSerije, "Fast Food") == 0;
}

struct Jelo {
	char* imeJela = nullptr;
	char* kategorijaJela = nullptr;
	char imeKuhara[40] = "";
	int brojVarijacija = 0;
	int brojKriticara = 0;
	int** ocjene = nullptr;

	void unos() {
		char temp[200];

		cout << "Unesite ime Jela:\n";
		cin.getline(temp, 200);
		imeJela = getTextCopy(temp);

		cout << "Unesite kategoriju Jela:\n";
		bool repeatLoop;
		do {
			repeatLoop = false;
			cin.getline(temp, 200);

			if (repeatLoop = !daLiJeKategorijaValidna(temp)) {
				cout << "Pogresna kategorija! Kategorija moze biti samo Tjestenina, Tradicionalna ili Fast Food\n";
			}
		} while (repeatLoop);
		kategorijaJela = getTextCopy(temp);

		cout << "Unesite ime kuhara:\n";
		cin.getline(imeKuhara, 40);

		cout << "Unesite broj varijacija jela:\n";
		cin >> brojVarijacija;

		cout << "Unesite broj recenzenata za jelo:\n";
		cin >> brojKriticara;
		cin.ignore();

		ocjene = new int* [brojVarijacija];
		for (int i = 0; i < brojVarijacija; ++i)
		{
			*(ocjene + i) = new int[brojKriticara];

			for (int j = 0; j < brojKriticara; ++j)
			{
				*(*(ocjene + i) + j) = rand() % 10 + 1;
			}
		}
	}

	void ispis()
	{
		cout << "==============================================================================\n";
		cout << "Ime jela: " << imeJela << '\n';
		cout << "Kategorija jela: " << kategorijaJela << '\n';
		cout << "Ime kuhara: " << imeKuhara << '\n';
		cout << "Broj varijacija: " << brojVarijacija << '\n';
		cout << "Broj kriticara: " << brojKriticara << '\n';
		cout << "-----------------------------------------------------\n";
		for (int i = 0; i < brojVarijacija; ++i)
		{
			cout << "Varijacija " << i + 1 << " ->";
			for (int j = 0; j < brojKriticara; ++j)
			{
				cout << " Kriticar " << j + 1 << " ocjena: " << setw(3) << *(*(ocjene + i) + j) << " |";
			}
			cout << '\n';
		}
		cout << "-----------------------------------------------------\n";
		cout << "==============================================================================\n";
	}

	void dealokacije()
	{
		delete[] imeJela;
		imeJela = nullptr;

		delete[] kategorijaJela;
		kategorijaJela = nullptr;

		for (int i = 0; i < brojVarijacija; ++i)
		{
			delete[] * (ocjene + i);
		}
		delete[] ocjene;
		ocjene = nullptr;
	}
};

float getAverageForVarijacija(Jelo* const jelo, int varijacijaIndex) {
	float averageForVarijacija{ 0.0f };

	for (int k = 0; k < jelo->brojKriticara; ++k)
	{
		averageForVarijacija += *(*(jelo->ocjene + varijacijaIndex) + k);
	}

	return averageForVarijacija / jelo->brojKriticara;
}

float getAverageForJelo(Jelo* const jelo) {
	float averageForJelo{ 0.0f };

	for (int j = 0; j < jelo->brojVarijacija; ++j)
	{
		averageForJelo += getAverageForVarijacija(jelo, j);
	}

	return averageForJelo / jelo->brojVarijacija;
}

float* getAverageByCategory(Jelo* niz, int velNiza) {
	float* averagesByCategory = new float[3];
	*(averagesByCategory + 0) = 0.0f;
	*(averagesByCategory + 1) = 0.0f;
	*(averagesByCategory + 2) = 0.0f;

	int* counters = new int[3];
	*(counters + 0) = 0;
	*(counters + 1) = 0;
	*(counters + 2) = 0;

	for (int i = 0; i < velNiza; ++i)
	{
		const char* const zanrJela = (niz + i)->kategorijaJela;
		float averageForJelo = getAverageForJelo(niz + i);

		if (strcmp(zanrJela, "Tjestenina") == 0)
		{
			*(averagesByCategory + 0) += averageForJelo;
			*(counters + 0) += 1;
		}
		else if (strcmp(zanrJela, "Tradicionalna") == 0)
		{
			*(averagesByCategory + 1) += averageForJelo;
			*(counters + 1) += 1;
		}
		else if (strcmp(zanrJela, "Fast Food") == 0)
		{
			*(averagesByCategory + 2) += averageForJelo;
			*(counters + 2) += 1;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (*(counters + i) != 0)
		{
			*(averagesByCategory + i) /= *(counters + i);
		}
	}

	delete[] counters;

	return averagesByCategory;
}

int main() {
	srand(time(nullptr));

	int brojJela;
	cout << "Unesite broj jela: ";
	cin >> brojJela;
	cin.ignore();

	Jelo* jela = new Jelo[brojJela];

	for (int i = 0; i < brojJela; ++i) {
		(jela + i)->unos();
	}

	for (int i = 0; i < brojJela; ++i) {
		(jela + i)->ispis();
	}

	float* averagesByCategory = getAverageByCategory(jela, brojJela);

	cout << "============================================================\n";
	cout << "Prosjecne ocjene po kategorijama jela:\n";
	cout << "Tjestenina: " << *(averagesByCategory + 0) << '\n';
	cout << "Tradicionalna: " << *(averagesByCategory + 1) << '\n';
	cout << "Fast Food: " << *(averagesByCategory + 2) << '\n';
	cout << "============================================================\n";

	delete[] averagesByCategory;
	averagesByCategory = nullptr;

	for (int i = 0; i < brojJela; ++i) {
		(jela + i)->dealokacije();
	}

	delete[] jela;
	jela = nullptr;

	return 0;
}
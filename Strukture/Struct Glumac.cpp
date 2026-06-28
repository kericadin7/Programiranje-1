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

struct Glumac
{
    char* ime = nullptr;
    char* prezime = nullptr;
    char drzava[40] = "";
    int brojFilmova = 0;
    int brojKorisnika = 0;
    int** ocjene = nullptr;

    void unos()
    {
        char temp[50];

        cout << "Unesi ime glumca: ";
        ime = unesiText(ime);

        cout << "Unesi prezime glumca: ";
        prezime = unesiText(prezime);

        cout << "Unesi drzavu: ";
        cin.getline(drzava, size(drzava));

        cout << "Unesi broj filmova: ";
        cin >> brojFilmova;
        cin.ignore();

        cout << "Unesi broj korisnika: ";
        cin >> brojKorisnika;
        cin.ignore();

        ocjene = new int* [brojFilmova];

        for (int i = 0; i < brojFilmova; i++)
        {
            *(ocjene + i) = new int[brojKorisnika];
            for (int j = 0; j < brojKorisnika; j++)
            {
                cout << "Unesite ocjenu glumca za ulogu u filmu " << i + 1 << " od strane korisnika " << j + 1 << " (1 - 10): ";
                cin >> *(*(ocjene + i) + j);
            }
        }
    }

    void ispis()
    {
        cout << "Ime glumca: " << ime << endl;
        cout << "Prezime glumca: " << prezime << endl;
        cout << "Drzava: " << drzava << endl;
        cout << "Broj filmova: " << brojFilmova << endl;
        cout << "Broj korisnika: " << brojKorisnika << endl;
        cout << "======OCJENE======" << endl;

        for (int i = 0; i < brojFilmova; i++)
        {
            for (int j = 0; j < brojKorisnika; j++)
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
        delete[] ime;
        ime = nullptr;

        delete[] prezime;
        prezime = nullptr;

        for (int i = 0; i < brojFilmova; i++)
        {
            delete[] * (ocjene + i);
        }

        delete[] ocjene;
        ocjene = nullptr;
    }

    float* getAveragesByUsers()
    {
        float* prosjeci = new float[brojKorisnika] {0};

        for (int j = 0; j < brojFilmova; j++)
        {
            float suma = 0;
            for (int i = 0; i < brojKorisnika; i++)
            {
                suma += *(*(ocjene + i) + j);
            }
            *(prosjeci + j) = suma / brojFilmova;
        }
        return prosjeci;
    }
};



int main()
{
    Glumac *glumac = new Glumac;

    glumac->unos();
    glumac->ispis();

    float* prosjeci = glumac->getAveragesByUsers();
    for (int i = 0; i < glumac->brojKorisnika; i++)
    {
        cout << *(prosjeci + i) << " ";
    }
    cout << endl;

    delete[] prosjeci;
    prosjeci = nullptr;

    glumac->dealokacija();

    delete glumac;
    glumac = nullptr;

	return 0;
}
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	srand(time(0));

	int kockice[7];
	int ukupanBrojBacanja = 0;
	bool uslovIspunjen = false;

	while (!uslovIspunjen)
	{
		ukupanBrojBacanja++;
		for (int i = 0; i < 7; i++)
		{
			kockice[i] = rand() % 6 + 1;
		}

		cout << "Bacanje #" << ukupanBrojBacanja << " ";
		for (int i = 0; i < 7; i++)
		{
			cout << kockice[i] << " ";
		}
		cout << endl;

		int brojacPonavljanja[7] = { 0 };
		for (int i = 0; i < 7; i++)
		{
			int trenutnaVrijednost = kockice[i];
			brojacPonavljanja[trenutnaVrijednost]++;
		}

		bool imaCetiri = false;
		bool imaTri = false;

		for (int i = 0; i <= 6; i++)
		{
			if (brojacPonavljanja[i] == 4)
			{
				imaCetiri = true;
			}if (brojacPonavljanja[i] == 3)
			{
				imaTri = true;
			}
		}

		if (imaCetiri && imaTri)
		{
			uslovIspunjen = true;
		}
	}

	cout << "==============================================" << endl;
	cout << "Kraj simulacije! Uslov ispunjen." << endl;
	cout << "Ukupan broj bacanja: " << ukupanBrojBacanja << endl;
	cout << "Posljednje izvucene vrijednost kockica: ";
	for (int i = 0; i < 7; i++)
	{
		cout << kockice[i] << " ";
	}
	cout << endl;
	cout << "==============================================" << endl;

	return 0;
}
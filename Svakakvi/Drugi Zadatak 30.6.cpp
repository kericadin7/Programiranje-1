#include <iostream>

using namespace std;

bool isProst(int broj)
{
	if (broj <= 1)
		return false;

	for (int i = 2; i * i < broj; i++)
	{
		if (broj % i == 0 )
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int n = 0;
	int k = 0;

	do
	{
		cout << "Unesite broj n (10 - 1000, NE SMIJE BITI PROST): ";
		cin >> n;
	} while (n < 10 || n > 1000 || isProst(n));

	do
	{
		cout << "Unesite broj k ( k < n): ";
		cin >> k;
	} while (k <= 0 || k >= n);

	cout << endl;

	cout << k << " najblizih prostih brojeva manjih od " << n << ": ";
	int brojacManjih = 0;
	int trenutniManji = n - 1;

	while (brojacManjih < k && trenutniManji > 1)
	{
		if (isProst(trenutniManji))
		{
			cout << trenutniManji << " ";
			brojacManjih++;
		}
		trenutniManji--;
	}
	cout << endl;

	cout << "Broj n: " << n << endl;

	cout << k << " najblizih prostih vecih od " << n << ": ";
	int brojacVecih = 0;
	int trenutniVeci = n + 1;

	while (brojacVecih < k)
	{
		if (isProst(trenutniVeci))
		{
			cout << trenutniVeci << " ";
			brojacVecih++;
		}
		trenutniVeci++;
	}
	cout << endl;

	return 0;
}

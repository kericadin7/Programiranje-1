#include <iostream>
#include <ctime>

using namespace std;

int stepen(int baza, int eksponent)
{
	if (eksponent == 0)
		return 1;

	return baza * stepen(baza, eksponent - 1);
}

int main()
{
	srand(time(0));

	int baza = rand() % 8 + 1;

	int eksponent = rand() % 10 + 1;

	cout << "Baza: " << baza << ", " << "Eksponent: " << eksponent << endl;

	int rezultat = stepen(baza, eksponent);

	cout << baza << "^" << eksponent << " = " << rezultat << endl;

	return 0;
}
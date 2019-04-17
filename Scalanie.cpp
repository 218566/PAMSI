#include<iostream>
#include<fstream>
#include<cmath>
#include<time.h>
#include<Windows.h>
#include<stdint.h>

using namespace std;

/**FUNKCJA SCALAJACA TABLICE**/
void scal(int *tablica, int start, int srodek, int koniec) {
	int i, j, k;   //indeksy pomocnicze
	int *tmp = new int[koniec - start + 1]; //tablica pomocnicza

	i = start;
	k = 0;
	j = srodek + 1;

	while (i <= srodek && j <= koniec)
	{
		if (tablica[j]<tablica[i])
		{
			tmp[k] = tablica[j];
			j++;
		}
		else
		{
			tmp[k] = tablica[i];
			i++;
		}
		k++;
	}
	if (i <= srodek)
		while (i <= srodek)
		{
			tmp[k] = tablica[i];
			i++;
			k++;
		}
	else
		while (j <= koniec)
		{
			tmp[k] = tablica[j];
			j++;
			k++;
		}
	for (i = 0; i <= (koniec - start); i++)
		tablica[start + i] = tmp[i];
}

void scalSort(int *tablica, int start, int koniec) {
	int srodek;

	if (start != koniec)
	{
		srodek = (start + koniec) / 2;
		scalSort(tablica, start, srodek);
		scalSort(tablica, srodek + 1, koniec);
		scal(tablica, start, srodek, koniec);
	}
}

/****SPRAWDZENIE POPRAWNOSCI SORTOWANIA******/
void Spr(int *tablica, int rozmiar) {
	int posortowane = 1;
	for (int i = 0; i<rozmiar - 1; ++i)
	{
		if (tablica[i]>tablica[i + 1])
			posortowane = 0;
	}
	if (posortowane == 1)
		cout << "Tablica posortowana" << endl;
	else
		cout << "Tablica nieposortowana" << endl;
}
/*********MAIN********/
int main() {
	cout << "Dzia³am" << endl;
	long long nowaDana;
	const int zakres = 150;
	int* tablica = new int[zakres];
	int poczatek, koniec, czas, srczas = 0;

	LARGE_INTEGER czestotliwosc, t1, t2;
	QueryPerformanceFrequency(&czestotliwosc);
	double elapsedTime;
	double czass = 0;


	cout << "Dzia³am" << endl;
	for (int j = 0; j<100; j++)
	{
		ifstream Plik("dane25proc.txt");
		for (int i = 0; i<zakres; i++)
		{
			Plik >> nowaDana;
			tablica[i] = nowaDana;
		}

		QueryPerformanceCounter(&t1);
		poczatek = GetTickCount();
		scalSort(tablica, 0, zakres);

		QueryPerformanceCounter(&t2);

		elapsedTime = ((t2.QuadPart - t1.QuadPart) * 1000.0) / czestotliwosc.QuadPart; ///przelicza czas
		czass = czass + elapsedTime;
		
		koniec = GetTickCount();
		czas = koniec - poczatek;
		srczas = srczas + czas;
		cout << "Sortowanie " << j << " wykonano w czasie :" << elapsedTime << "ms." << endl;
		Spr(tablica, zakres);
	}
	cout << "0 % Srednia czasow to : " << czass / 100 << "ms." << endl;
	system("pause");
	delete [zakres] tablica;
	return 0;
}

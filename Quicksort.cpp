#include<iostream>
#include<fstream>
#include<cmath>
#include<time.h>
#include <Windows.h>
#include <stdint.h>

using namespace std;

/**FUNKCJA ZAMIENIAJACA MIEJSCAMI WARTOSCI**/
void zamien(int &a, int &b) {
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
	return;
}
/**FUNKCJA DZIELACA TABLICE**/
int Podziel(int *tablica, int l, int r) { //l - lewa strona, p - prawa strona
	int indeks; //indeks elementu nie bioracego udzialu w sortowaniu (pivot)
	int wartosc;//wartosc pivota
	int pozycja;//aktualna pozycja

	indeks = l + (r - l) / 2; //wybranie pivota z polowy tablicy
	wartosc = tablica[indeks];
	zamien(tablica[indeks], tablica[r]); //przeniesienie pivota na koniec

	pozycja = l;
	for (int i = l; i <= r - 1; i++)
	{
		if (tablica[i]<wartosc) //jesli element jest mniejszy
		{                    //zostaje przeniesiony na lewo
			zamien(tablica[i], tablica[pozycja]);
			pozycja = pozycja + 1;
		}
	}
	zamien(tablica[pozycja], tablica[r]); //przywrocenie pivota w odpowiednie
	return pozycja;                       //miejsce
}
/****QUICKSORT****/
void quicksort(int *tablica, int l, int r) {
	int i;
	if (l<r)
	{
		i = Podziel(tablica, l, r);  //podzial tablicy na 2 czesci
		quicksort(tablica, l, i - 1);//sortowanie lewej strony
		quicksort(tablica, i + 1, r);//sortowanie prawej strony
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

/**************MAIN******************/
int main() {

	int nowaDana;
	const int zakres = 100000;
	int* tablica = new int[zakres];

	LARGE_INTEGER czest, t1, t2; 

	double elapsedTime;
	double czass = 0;

	QueryPerformanceFrequency(&czest);


	for (int j = 0; j<100; j++)
	{
		ifstream Plik("daneodwr.txt");
		for (int i = 0; i<zakres; i++)
		{
			Plik >> nowaDana;         //wczytywanie tablicy
			tablica[i] = nowaDana;
		}

		QueryPerformanceCounter(&t1);

		quicksort(tablica, 0, zakres); //sortowanie

		QueryPerformanceCounter(&t2);

		elapsedTime = ((t2.QuadPart - t1.QuadPart) * 1000.0) / czest.QuadPart; ///przelicza czas
		czass = czass + elapsedTime;
	
		cout << "Sortowanie " << j << " wykonano w czasie :" << elapsedTime << "ms." << endl;
		Spr(tablica, zakres);
	}
	cout << "Srednia czasow to : " << czass/100 << "ms." << endl; //liczenie sredniej
	system("pause");
	return 0;
}

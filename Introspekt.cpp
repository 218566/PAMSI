#include<iostream>
#include<fstream>
#include<cmath>
#include<time.h>
#include<Windows.h>
#include<stdint.h>

using namespace std;
/******FUNKCJA ZAMIENIAJACA WARTOSCI MIEJSCAMI*******/
void zamien(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
	return;
}

void Kopiec(int *tab, int i, int N) {
	int j;
	while (i <= N / 2)
	{          //utworzenie kopca
		j = 2 * i;
		if (j + 1 <= N && tab[j + 1]>tab[j])
			j++;
		if (tab[i]<tab[j])
			zamien(tab[i], tab[j]);
		else break;
		i = j;
	}
}

void kopcowanie(int *tab, int N) {
	int i;
	for (i = N / 2; i>0; i--)
		Kopiec(tab - 1, i, N);
	for (i = N - 1; i>0; i--)
	{
		zamien(tab[0], tab[i]); //sortowanie kopca
		Kopiec(tab - 1, 1, i);
	}
}
/**FUNKCJA DZIELACA TABLICE**/
int Podziel(int *tablica, int l, int r) {
	int indeks; //indeks elementu nie bioracego udzialu w sortowaniu (pivot)
	int wartosc; //wartosc pivota
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

/******INTROSORT******/
void introsort(int *tab, int M, int rozm) {
	int n = rozm;
	int p;
	if (n <= 1)
		return;
	else if (M == 0)           //dzialanie introsorta uzaleznione jest od
		kopcowanie(tab, rozm); //wartosci liczby M
	else
	{
		p = Podziel(tab, 0, rozm);
		introsort(tab, M - 1, p);
		introsort(tab + p + 1, M - 1, rozm - p);
	}
}
/***************************/
void wstawianie(int *tab, int rozm) {
	int i, j;
	int tmp;
	for (i = 1; i<rozm; ++i)
	{
		tmp = tab[i];
		for (j = i; j>0 && tmp<tab[j - 1]; --j)
			tab[j] = tab[j - 1];
		tab[j] = tmp;
	}
}

/***********************************/
void Sort(int *tab, int rozm) {
	int M = 2 * log(rozm);
	introsort(tab, M, rozm);
	wstawianie(tab, rozm);    //poprawianie prawie posortowanej tablicy
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

int main() {

	int nowaDana;
	const int zakres = 100000;
	int tablica[zakres];
	LARGE_INTEGER czest, t1, t2;
	double elapsedTime;
	double czass = 0;
	
	QueryPerformanceFrequency(&czest);

	for (int j = 0; j<100; j++)
	{
		ifstream Plik("dane25proc.txt");
		for (int i = 0; i<zakres; i++)
		{
			Plik >> nowaDana;        //wczytywanie danych
			tablica[i] = nowaDana;
		}
		
		QueryPerformanceCounter(&t1);

		Sort(tablica, zakres);          //sortowanie

		QueryPerformanceCounter(&t2);
		
		elapsedTime = ((t2.QuadPart - t1.QuadPart) * 1000.0) / czest.QuadPart; ///przelicza czas
		czass = czass + elapsedTime;

		
		cout << "Sortowanie " << j << " wykonano w czasie :" << elapsedTime << "ms." << endl;
		Spr(tablica, zakres);
	}
	cout << "Srednia czasow to : " << czass/100 << "ms." << endl;
	system("pause");
	return 0;

}

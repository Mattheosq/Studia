// WCY21IY4S1 Grabowski Mateusz Zad3 Algorytm Quick Sort

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void list_tab(int n, int tab[]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void gen_los(int n, int tab[], int a, int b) {
    srand(time(0));

    for (int i = 0; i < n; i++) {
        tab[i] = rand() % (b - a + 1) + a;
    }
}


int Partition(int arr[], int s, int e){ // funkcja przyjmuje tablice do podzielenia i jej rozpatrywany zakres (s-e)
 	int pivot = arr[e]; // wybieramy element na ko�cu cz�ci tablicy jako punkt piwotu
 	int pIndex = s; // inicjujemy zmienn� pIndex przypisuj�c do niej indeks pocz�tkowy
 
	for(int i = s;i<e;i++){ // iteruje przez rozwa�an� cz�� tablicy, zaczynaj�c od indeksu pocz�tkowego i ko�cz�c na przedostatnim elemencie, poniewa� ostatni element to piwot
		if(arr[i]<pivot){ // sprawdzane jest czy element jest mniejszy od piwotu
			// zamieniamy element z elementem na pozycji pIndex i zwi�ksza pIndex. Zapewnia to, �e wszystkie elementy mniejsze od piwotu znajduj� si� po jego lewej stronie, a wi�ksze po prawej
			int temp = arr[i];
			arr[i] = arr[pIndex];
			arr[pIndex] = temp;
			pIndex++;
		}
	}
	// na ko�cu zamieniamy element w punkcie piwotu na element w pozycji pIndex, dziel�c tablic� wzgl�dem tego punktu
	int temp = arr[e];
    arr[e] = arr[pIndex];
	arr[pIndex] = temp;
	 
	return pIndex; // zwracamy indeks piwotu
}
// s to indeks poczatkowy(==0), e to indeks ko�cowy
void QuickSort(int arr[], int s, int e){ // dzia�a poprzez podzielenie tablicy wok� punktu piwotu, a nast�pnie rekurencyjne sortuje podtablice po obu stronach tego punktu
	 if(s < e){  // je�li indeks pocz�tkowy jest mniejszy ni� indeks ko�cowy, oznacza to, �e w rozwa�anej cz�ci tablicy (s-e) jest wi�cej ni� jeden element...
		 int p = Partition(arr,s, e); // ...w takim wypadku funkcja Partition dzieli tablic� wok� punktu piwotu i zwraca jego indeks
		 QuickSort(arr, s, (p-1));  // rekurencyjnie dla lewej strony od punktu piwotu(p)
		 QuickSort(arr, (p+1), e);  // rekurencyjnie dla prawej strony od punktu piwotu
	 }
	 // je�li indeks pocz�tkowy jest wi�kszy lub r�wny indeksowi ko�cowemu, to rozwa�ana cz�� tablicy jest ju� posortowana
}
 
int main()
{
 	int n;
	printf("Podaj ilosc elementow ");
	scanf("%d",&n);
	int arr[n];
	
	int a,b;
	printf("Podaj zakres a(>=0) i b(>=0) dla generatora liczb pseudolosowych dodatnich\n");
	printf("a: ");
	scanf("%d",&a);
	printf("\nb: ");
	scanf("%d",&b);
	
	gen_los(n, arr, a, b);
	
	
	/* awaryjne manualne podawanie liczb
	int i;
	for(i = 0; i < n; i++){
		
		printf("Podaj %d wartosc: ", i+1);
		int val;
		scanf("%d",&val);
		arr[i] = val;
	}*/
	printf("\nPrzed sortowaniem: \n");
	list_tab(n, arr);
	QuickSort(arr,0, n-1);
	printf("\nPo sortowaniu:\n");
	list_tab(n, arr);
	
	 
	return 0;
}

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
 	int pivot = arr[e]; // wybieramy element na koñcu czêœci tablicy jako punkt piwotu
 	int pIndex = s; // inicjujemy zmienn¹ pIndex przypisuj¹c do niej indeks pocz¹tkowy
 
	for(int i = s;i<e;i++){ // iteruje przez rozwa¿an¹ czêœæ tablicy, zaczynaj¹c od indeksu pocz¹tkowego i koñcz¹c na przedostatnim elemencie, poniewa¿ ostatni element to piwot
		if(arr[i]<pivot){ // sprawdzane jest czy element jest mniejszy od piwotu
			// zamieniamy element z elementem na pozycji pIndex i zwiêksza pIndex. Zapewnia to, ¿e wszystkie elementy mniejsze od piwotu znajduj¹ siê po jego lewej stronie, a wiêksze po prawej
			int temp = arr[i];
			arr[i] = arr[pIndex];
			arr[pIndex] = temp;
			pIndex++;
		}
	}
	// na koñcu zamieniamy element w punkcie piwotu na element w pozycji pIndex, dziel¹c tablicê wzglêdem tego punktu
	int temp = arr[e];
    arr[e] = arr[pIndex];
	arr[pIndex] = temp;
	 
	return pIndex; // zwracamy indeks piwotu
}
// s to indeks poczatkowy(==0), e to indeks koñcowy
void QuickSort(int arr[], int s, int e){ // dzia³a poprzez podzielenie tablicy wokó³ punktu piwotu, a nastêpnie rekurencyjne sortuje podtablice po obu stronach tego punktu
	 if(s < e){  // jeœli indeks pocz¹tkowy jest mniejszy ni¿ indeks koñcowy, oznacza to, ¿e w rozwa¿anej czêœci tablicy (s-e) jest wiêcej ni¿ jeden element...
		 int p = Partition(arr,s, e); // ...w takim wypadku funkcja Partition dzieli tablicê wokó³ punktu piwotu i zwraca jego indeks
		 QuickSort(arr, s, (p-1));  // rekurencyjnie dla lewej strony od punktu piwotu(p)
		 QuickSort(arr, (p+1), e);  // rekurencyjnie dla prawej strony od punktu piwotu
	 }
	 // jeœli indeks pocz¹tkowy jest wiêkszy lub równy indeksowi koñcowemu, to rozwa¿ana czêœæ tablicy jest ju¿ posortowana
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

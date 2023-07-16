//WCY21IY4S1 Grabowski Mateusz Zad2 (Counting Sort)
//
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

void counting_sort(int* arr, int n, int k) {
  
  int* counts = (int*)malloc(k * sizeof(int)); // tworzenie tablicy o indeksach 0 - (k-1) , gdzie k-1 to prawy koniec przedzialu wylosowanych liczb
	// kazdy indeks oznacza liczbe, ktora znajduje sie w przekazanej tablicy do posortowania, wartosci tablicy counts oznaczaja laczna liczbe wystepowania kazdej z tych liczb
  
  for (int i = 0; i < k; i++) { // zapelniamy tablice zerami
    counts[i] = 0;
  }

  // store the count of each element in the count array
  for (int i = 0; i < n; i++) {
    counts[arr[i]]++; // wynik zliczania zapisanywany jest w tablicy
  }

 
  int j = 0;
  for (int i = 0; i < k; i++) { // iteracja przez cala tablice counts
    while (counts[i] > 0) { // warunek dla kilku tych samych liczb
      arr[j] = i; // zapelnienie wynikowej tablicy indeksem reprezentujacym rzeczywista liczbe, ktora nalezalo posortowac
      j++;
      counts[i]--;
    }
  }

  
  free(counts); // zwalniamy pamiec
}

int main() {
 
  	unsigned int n;
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
	counting_sort(arr, n, b+1); 
	printf("\nPo sortowaniu:\n");
	list_tab(n, arr);

  return 0;
}

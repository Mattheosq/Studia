//WCY21IY4S1 Grabowski Mateusz Zad3 (Comb Sort)
//
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

void list_tab(int n, int tab[]) {
    for (int i = 0; i < n; i++) {
        printf("%d \t", tab[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void comb_sort(int *array, int size) {
  
  int gap = size;
  int swapped = 1; // ustawianie swapped na 1 aby wejsc do petli sortowania

  // petla trwa do momentu az zmienna gap wynosi 1 nie doszlo do zadnych zamian liczb
  while (gap > 1 || swapped) {
    // zmieniamy wartosc gap dla nastepnego "grzebienia"
    gap = gap * 10 / 13;
    // naprawiamy wartosci gap ktore sa za male lub za duze
    if (gap == 9 || gap == 10) {
      gap = 11;
    }
    if (gap < 1) {
      gap = 1;
    }

    
    swapped = 0; // resetujemy swapped
    // iterujemy po tablicy i porownujemy elementy z gap
    for (int i = 0; i < size - gap; i++) {
      //jezeli elementy sa w zlej kolejnosci, zamienieniamy je
      if (array[i] > array[i + gap]) {
        int temp = array[i];
        array[i] = array[i + gap];
        array[i + gap] = temp;
        // zmieniamy zmienna swapped spowrotem na 1 by dac znac, ze nastapila zamiana liczb
        swapped = 1;
      }
    }
  }
}

void gen_los(int n, int tab[], int a, int b) {
    srand(time(0));

    for (int i = 0; i < n; i++) {
        tab[i] = rand() % (b - a + 1) + a;
    }
}

int main(int argc, char *argv[]) {
  /*int array[MAX_SIZE];
  int size = 0;

  FILE *fp = fopen("comb_sort.txt", "r");
  if (fp == NULL) {
    printf("Blad otwarcia pliku\n");
    return 1;
  }

  // zapelnianie tablicy liczbami z pliku
  while (fscanf(fp, "%d", &array[size]) == 1) {
    size++;
  }

  fclose(fp);*/
  
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
	
  printf("Przed posortowaniem: \n");
  list_tab(n,arr);
  comb_sort(arr, n);
  printf("Po sortowaniu: \n");
  list_tab(n,arr);

  return 0;
}


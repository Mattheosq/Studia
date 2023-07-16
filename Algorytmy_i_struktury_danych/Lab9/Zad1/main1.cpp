// WCY21IY4S1 Grabowski Mateusz Zad1 Algorytm Shell Sort

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


void ShellSort(int arr[], int n) // iteracyjnie, korzystanie z bubble sort
{
	for(int gap=n/2; gap>0; gap /= 2) // iterujemy po zmiennej gap(odstepie)
	{ // wartoœci odstêpów s¹ obliczane jako po³owa d³ugoœci tablicy podzielona przez 2 w ka¿dej iteracji. Pêtla bêdzie kontynuowana, dopóki wartoœæ przerwy nie bêdzie równa 0
		for(int j = gap;j<n;j+=1) // pêtla, która iteruje elementy tablicy, zaczynaj¹c od wartoœci gap i zwiêkszaj¹c go o 1 przy ka¿dej iteracji
		{
			int temp = arr[j]; // temp przechowuje element arr[j], ¿eby póŸniej porównaæ element z elementami, które s¹ "gap" pozycji przed nim w tablicy
			int i=0;
			
			for(i=j;(i>=gap)&&(arr[i-gap]>temp);i-=gap) // jeœli porównywany element temp jest mniejszy ni¿ element "gap" pozycji przed nim...
			{
				arr[i] = arr[i-gap]; //... element jest przesuwany w lewo o pozycje przerw i pêtla jest kontynuowana
			}
			arr[i] = temp; // gdy temp nie jest ju¿ mniejszy ni¿ element, który znajduje siê "gap" pozycji przed nim w tablicy lub gdy pêtla osi¹gnie pocz¹tek tablicy, wstawiamy element przechowywany w zmiennej temp do tablicy w pozycji 'i'
		}
	}
	
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
	ShellSort(arr, n);
	printf("\nPo sortowaniu:\n");
	list_tab(n, arr);
	
   return 0; 
}

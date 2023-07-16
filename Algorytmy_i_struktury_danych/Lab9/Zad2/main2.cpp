// WCY21IY4S1 Grabowski Mateusz Zad2 Algorytm Library Sort

#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000
#define MAX2 2000
 

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

// funkcja wyszukiwanie binarnego
/*
	Do funkcji przekazujemy szukana pozycje, tablice S oraz jej koncowa pozycje
	Wyszukiwanie przebiega miedzy first i last, gdzie middle onzacza srodek zakresu miedzy first i last
	

*/ 
int BinarySearch(int position, int sorted[MAX2], int last) { 
    int first = 0; // lewy skrajny indeks, prawy skrajny to parametr last
    int middle; // srodkowa pozycja
 	
 	// dwie petle sluza do pomijania pozycji ujemnych(pustych) na poczatku i na koncu zakresu wyszukiwania
    while(last >= 0 && sorted[last] < 0) 
		last--; 
    while(first <= last && sorted[first] < 0) 
		first++;
    while(first <= last) {
        middle = (first+last)/2;
        if(sorted[middle] < 0) { // jesli element o indeksie middle jest ujemny
            int tmp = middle + 1;
            
            while(tmp < last && sorted[tmp] < 0) // szukamy nastepnego nieujemnego elementu (niepustej pozycji) na prawo od srodkowego elementu
				tmp++; // inkrementujemy tmp, dopoki tmp nie stanie sie wieksze lub równe last lub dopóki sorted[tmp] nie bêdzie ujemne
            if(sorted[tmp] > position) { // porownujemy nieujemny element do position
                tmp = middle - 1;
                while(middle > first && sorted[middle] < 0) // szukamy nastepnego nieujemnego elementu po lewej stronie od obecnego srodkowego elementu
					middle --; // dekrementujemy middle dopoki albo middle nie stanie sie mniejszy lub równy first albo sorted[middle] nie bedzie ujemny
                //Sprawdz lewa strone
                if(sorted[middle] < position)// jesli znaleziono srodkowa pozycje
                    return middle;
                last = middle - 1;
            } 
			else 
				first = tmp + 1;
        } 
		else if(sorted[middle] < position) {// zakres szukania przechodzi na prawa strone od srodka tablicy
            first = middle + 1;
        } 
		else { // zakres szukania przechodzi na lewa strone od srodka tablicy
            last = middle - 1;
        }
    }
    //jesli wyszukiwanie zakonczy sie bez znalezienia wyniku, funkcja zwraca indeks ostatniego elementu w zakresie wyszukiwania lub -1, jesli taki element nie istnieje
    if(last>=0 && sorted[last] < 0) 
		last --;
    return last;
}
 
void LibrarySort(int A[MAX], int n) {
    int fixed_one = 1; // stala
    int S[MAX2]; // druga dwa razy dluzsza tablica, zeby pomiescic odstepy miedzy wartosciami
    int sLen = (fixed_one+1)*n; // wielkosc tablicy S
	int z;
    for(z=0; z<sLen;z++) 
		S[z] = -1; // -1 oznacza miejsce niezajate przez zadna wartosc;
    int j, k, step;
		
 		
	int target = 1; // zmienna opisujaca ile elementow chcemy, zeby poczatkowo weszlo do nowej tablicy S
	int pos = 1; // licznik elementow ile juz dodano
	 
	S[0] = A[0]; // ustawiamy pierwszy element wiekszej tablicy pierwszym elementem z mniejszej
	 
	
	int sLenInit = std::max((1+fixed_one), target + 1); // poczatkowa wielkosc tablicy S
	int signal = 0; // sygnal do oblsugi wyjscia z dwoch petli rownoczesnie
	
	while(pos<n) { // poki licznik jest mniejszy od ilosci elementow tablicy A, wykonuj petle
	    
	    //co kazda iteracje zmienna do zmiennej target bedzie przypisywana zdwojona liczba posortowanych elementow
	    for(j=0;j<target;j++) {
	        int insPos = BinarySearch(A[pos], S, sLenInit-1); // szukamy korzystajac z binary search gdzie wstawic A[pos]
	 
	        insPos++; // binary search zwraca nam lokacje z mniejsza wartoscia niz ta ktora szukamy, wiec inkrementujemy insPos
	        if(S[insPos] >= 0) {// jesli nie ma wolnego miejsca do wsadzenia elementu
	            int nextFree = insPos + 1;// szukamy wolnego miejsca na nastepnej pozycji
	            while(S[nextFree] >= 0) 
					nextFree++;
	            //jesli w nextFree jest miejsce, przeloz wszystkie elementy o jedna pozycje w prawo
	            if(nextFree >= sLenInit) {//jesli nextFree jest poza zakresem
	                insPos--;
	                if(S[insPos] >= 0) {
	                    
	                    nextFree = insPos - 1; // szukamy wstecz
	                    while(S[nextFree] >= 0) 
							nextFree--;
	                    
	                    while(nextFree<insPos) { // przestawiamy wszystkie elementy w lewo
	                        S[nextFree] = S[nextFree+1];
	                        nextFree++;
	                    }
	                }
	            } 
				else {
	                // przestawiamy wszystkie elementy w prawo
	                while(nextFree>insPos) {
	                    S[nextFree] = S[nextFree-1];
	                    nextFree--;
	                }
	            }
	            // zmienna insPos to teraz wolne miejsce
	        } 
			else if(insPos>=sLenInit) {//jesli insPos jest poza zakresem
	            //szukamy wolnego miejsca wstecz znajdujacego sie miedzy granicami
	            insPos--;
	            int nextFree = insPos - 1;
	            while(S[nextFree] >= 0) 
					nextFree--;
	            // przestawiamy wszystkie elementy w lewo
	            while(nextFree<insPos) {
	                S[nextFree] = S[nextFree+1];
	                nextFree++;
	            }
	            // zmienna insPos to teraz wolne miejsce
	        }
	 
	        S[insPos] = A[pos++]; //wstawiamy element do tablicy S i inkrementujemy pos
	 
	        if(pos >= n){ // jezeli jest to ostatni element, wyjdz z obu petli
	            signal++; // za pomoca signal == 1, po wyjsciu z tej petli, wyjdziemy tez z nastepnej
	        	break;
			}
	                
	}
	if(signal == 0){ // jezeli wewnetrzna petla sie zakonczyla nie przestawiajac sygnalu, dalsza czesc petli zewnetrznej zostanie obsluzona
	 			
	 	// rebalansujemy tablice rozprowadzajac wartosci po calej tablicy zachowujac puste miejsca
	    // rozprowadzamy elementy po calej
	    for(j=sLenInit-1, k=std::min(target*(2+2*fixed_one), (1+fixed_one)*n)-1, step=(k+1)/(j+1); j>=0; j--, k-=step) {
	        S[k] = S[j];
	        S[j] = -1; 
	    }
		// Co kazda iteracje wsadzamy podwójna liczbe elementow do posortowanej tablicy, poniewa¿ po ponownym zrównowa¿eniu zostanie podwójna liczba wolnych miejsc
		sLenInit = std::min(target*(2+2*fixed_one), n*(1+fixed_one));
		target = target << 1;// przesuwamy bity w lewo i spowrotem przypisujemy do zmiennej target, robiac tak dwukrotnie zwiekszamy jej wartosc
	 			
	}
	else
		break; // obsluga signal
	 		
	        
	}
	
    int x; // licznik wiekszej tablicy
    int y; // licznik mniejszej, pierwotnej tablicy
	for(x=0, y=0; x < sLen && y < n;x++)
        if(S[x] >= 0) 
			A[y++] = S[x];
			
}

int main(){
	
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
	LibrarySort(arr, n);
	printf("\nPo sortowaniu:\n");
	list_tab(n, arr);

	
}

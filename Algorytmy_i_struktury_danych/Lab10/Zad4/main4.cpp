//WCY21IY4S1 Grabowski Mateusz Zad4 (Radix Sort)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DIGITS 1000
#define RADIX 1000

typedef struct Node { // struktura listy jednokierunkowej
    int key;
    struct Node* next;
} Node;

void list_tab(int n, int tab[]) {
    for (int i = 0; i < n; i++) {
        printf("%d \t", tab[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

Node* queue[RADIX]; // tablica list, gdzie kazda liczba zawieraja cyfry znajdujace sie na tych samych miejscach znaczacych

int getMax(int* array, int n) { // zwraca maksymalna wartosc w tablicy liczb calkowitych
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

void radixSort(int* array, int n) {
    int d = 0;
    int max = getMax(array, n);

    for (int exp = 1; max / exp > 0; exp *= RADIX) { // iterujemy po tablicy queue, zaczynajac od cyfr na najmniej znaczacym miejscu
        for (int i = 0; i < RADIX; i++) // inicjalizujemy listy jednokierunkowe, kazda dla kazdej cyfry
            queue[i] = NULL;

        for (int i = 0; i < n; i++) {// dla kazdego elementu tablicy, tworzymy node i dodajemy go do listy odpowiadajacej cyfrze elementu
            Node* node = (Node*)malloc(sizeof(Node));
            node->key = array[i];
            node->next = queue[(array[i] / exp) % RADIX];
            queue[(array[i] / exp) % RADIX] = node;
        }
		
        int i = 0;
        for (int j = 0; j < RADIX; j++) { // iterujemy przez listy i dodajemy elementy spowrotem do tablicy
            while (queue[j] != NULL) {
                Node* node = queue[j];
                queue[j] = queue[j]->next;
                array[i++] = node->key;
                free(node);
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

int main() {
    /*FILE* file = fopen("radix_sort.txt", "r");
    if (file == NULL) {
        printf("Blad otwierania pliku\n");
        return 1;
    }

    int arr[MAX_DIGITS];
    int i = 0;
    while (fscanf(file, "%d", &arr[i]) == 1)
        i++;

    int n = i;*/
    
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
	
    printf("Przed sortowaniem: \n");
	list_tab(n,arr);
    radixSort(arr, n);

    printf("Po sortowaniu: \n");
	list_tab(n,arr);

    return 0;
}


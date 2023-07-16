//WCY21IY4S1 Grabowski Mateusz Zad1 (Heap Sort)
//
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

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

struct Node{ // struktura kopca maksymalnego
	
	int data;
	Node* left; // lewy nastepnik
	Node* right; // prawy nastepnik
	Node* parent;
};

struct Queue{ // 
	
	Node* qNode; // node fifo, ktory przechowuje struktury Node
	Queue* next;
};

Queue* front = NULL; // wskaznik na pierwszy element kolejki
Queue* rear = NULL; // wskaznik na ostatni element kolejki

// przy dodawaniu do kolejki przesuwamy rear
// przy usuwaniu z kolejki przesuwamy front

// Kolejka Queue  ///////////////////////
/////////////////////////////////////////
void Enqueue(Node* root) { // tworze kolejke struktur Node pochodzacych z kopca
    
    if (root == NULL) 
		return;
	Queue* temp = (Queue*)malloc(sizeof(Queue)); // nowo dodany element kolejki
	
	temp->qNode = root; // value kolejki, root to wskaznik na strukture Node, ale odgrywa tu role value
	temp->next = NULL; // wskaznik kolejki; wskaznik struktury Queue
	
    if(front == NULL && rear == NULL){ // dodanie pierwszego elementu
    	front = rear = temp;
    	return;
	}
    rear->next = temp;   // dolaczanie kolejnych elementow(struktur drzewa Node) do kolejki
	rear = temp;
}

void Dequeue(){
	
	Queue* temp = front;
	if(front == NULL) // kolejka struktur drzewa jest pusta
		return;
	if(front == rear){ // zostal jeden element kolejki
		front = rear = NULL;
	}
	else{
		front = front->next;
	}
	free(temp);
}

Node* CreateNode(int data){ // domyslne tworzenie nowych node'ow kopca
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void upHeapify(Node* temp){ // przeksztalcanie kopca uzyte w dodawaniu elementow
	if(temp->parent == NULL){
		return;
	}
	
	if(temp->parent->data < temp->data){
		
		std::swap(temp->parent->data, temp->data);
		upHeapify(temp->parent);
	}
}
void downHeapify(Node* temp){ // przeksztalcanie kopca przy usuwaniu korzenia (max value)
	
	Node* maxNode = temp;
	
	if(temp->left != NULL && temp->left->data > maxNode->data){
		
		maxNode = temp->left;
	}
	if(temp->right != NULL && temp->right->data > maxNode->data){
		maxNode = temp->right;
	}
	
	if(maxNode != temp){
		std::swap(maxNode->data, temp->data); // do roota trafia najwieksza wartosc
		downHeapify(maxNode); // reszta kopca jest naprawiana
	}
}
// Dodanie wezla //////////////////
Node* Insert(Node* root, int data){
	
	Node* newnode = CreateNode(data);
	if(root == NULL){
		root = newnode;
		return root;
	}
	
	Node* temp;
	Enqueue(root); // dodanie korzenia drzewa do kolejki
	
	while(front != NULL){ // dopoki kolejka nie jest pusta
		
		temp = front->qNode; // obecny node z drzewa zawierajacy: data,left,right
		Dequeue();
		if(temp->left != NULL && temp->right != NULL){ // sa obaj potomkowie
			Enqueue(temp->left);
			Enqueue(temp->right);
		}
		else{ // jest tylko jeden lub brak
			break;
		}
	}

	
	Node* lastparent = temp;
	
	if(lastparent->left == NULL){
		lastparent->left = newnode;
		newnode->parent = lastparent;
	}
	else{
		lastparent->right = newnode;
		newnode->parent = lastparent;
	}
	upHeapify(newnode);
	return root;
}

// Usuniecie wezla
Node* DeleteMax(Node* root){
	if(root == NULL)
		return root;
		
	Node* temp;
	Enqueue(root);
	
	while(front != NULL){
		
		temp = front->qNode;
		Dequeue();
		if(temp->left != NULL){
			Enqueue(temp->left);
		}
		if(temp->right != NULL){
			Enqueue(temp->right);
		}
	}
	
	
	Node* lastleaf = temp;
	
	if(lastleaf == root){
		free(root);
		root = NULL;
	}
	
	std::swap(root->data, lastleaf->data);
	Node* prev = lastleaf->parent; // teraz ostatnim lisciem jest root, ktory byl maksymalna wartoscia w kopcu
	if(prev->left == lastleaf){
		free(lastleaf);
		prev->left = NULL;
	}
	else{
		free(lastleaf);
		prev->right = NULL;
	}
	downHeapify(root);
	return root;
}

void swapTwoNum(int *a, int *b) // zamienia dwie liczby
{
	*a = (*a + *b) - (*b = *a);
}

void maxHeapify(int *arr, int size, int nodeIndex) // funckja przywracajaca wlasnosci max heap'a rekurencyjnie
{

	int left = (2 * nodeIndex) + 1;  // indeks lewego potomka
	int right = (2 * nodeIndex) + 2; // indeks prawego potomka
	int largest = nodeIndex;		 // inicjalizujemy largest jako root

	if (left < size && arr[left] > arr[largest])
		largest = left;
	if (right < size && arr[right] > arr[largest])
		largest = right;

	//sprawdzenie czy largerst nie ma indeksu root'a
	if (largest != nodeIndex)
	{
		// zamieniamy element oznaczony jako root z potomkiem majacym najwieksza wartosc
		swapTwoNum(&arr[nodeIndex], &arr[largest]);
		//rekurencyjnie naprawiamy poddrzewo utworzone po zamianie
		maxHeapify(arr, size, largest);
	}
}

void heapSortMaxHeap(int *arr, int n)
{
	int i;
	int y;
	for (y = (n / 2) - 1; y >= 0; y--) // tworzymy max Heap
		maxHeapify(arr, n, y);

	// Heap sort
	// w petli dla kazdego elementu od ostatniego do pierwszego (od lisci do korzenia) wymieniami ostatni element z root'em, po czym zwracamy wlasnosci maksymalnego heap funkcja maxHeapify
	for (i = n - 1; i >= 0; i--)
	{
		// przesuwamy obecny korzen na miejsce ostatniego elementu ktory byl lisciem
		swapTwoNum(&arr[0], &arr[i]);
		// usuwamy w ten sposob przesuniety korzen i naprawiamy funkcja maxHeapify heap'a
		maxHeapify(arr, i, 0);
	}
}

int main() 
{ 
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
	heapSortMaxHeap(arr, n);
	printf("\nPo sortowaniu:\n");
	list_tab(n, arr);
	
   return 0; 
}

// WCY21IY4S1 Grabowski Mateusz Zad2

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>

struct Node{
	
	int priority; // kod klienta Platinum, gold, silver
	int nr_klienta;
	int czas_rozmowy;
	
	Node* next;
};

struct Linia{
	
	int priority;
	int nr_klienta;
	int czas_rozmowy;
	bool zajete;
	
};

#define PLATINUM 2
#define GOLD 1
#define SILVER 0

// priority = 1 < priority = 2 itd.; priorytet w kolejce jest nierosnacy i.e. front: 8,4,2,1,1 : rear 
//const int MAXINT = -2147483647; // specjalna wartosc

Node* front = NULL; // wskazniki na poczatek i koniec kolejki
Node* rear = NULL;

bool isEmpty(){
	
	if(front == NULL){
		return 1;
	}
	return 0;
}

void Enqueue(char x, int y, int z){ // x - priority, y - nr klienta, z - czas rozmowy
	
	Node* temp = (Node*)malloc(sizeof(Node)); // nowy node
	//temp->priority = x;
	temp->nr_klienta = y;
	temp->czas_rozmowy = z;
	temp->next = NULL;
	
	switch(x){ // zamiana char na int
		
		case 'P':
			temp->priority = 2;
			break;
			
		case 'G':
			temp->priority = 1;
			break;
		case 'S':
			temp->priority = 0;
			break;
	}
	
	if(front == NULL && rear == NULL){ // warunek dla pustej kolejki
		front = rear = temp;
		return;
	}
	else if(front->priority < temp->priority){ // warunek przy pierwszym elemencie, gdy priorytet nowo dodanego elementu jest wyzszy, dodaj go na poczatek
		temp->next = front;
		front = temp; // front teraz pokazuje na pierwszy element, a rear na drugi(ostatni)
	}
	else{ // warunek przy pozostalych elementach, jezeli pierwszy element nie byl wyzszy priorytetem, to przejdz po kolejce az natrafisz mniejszy priorytet
		Node* check = front;
		while( check->next != NULL && check->next->priority >= temp->priority) // 8 4 2 1 1, np. dla 3 check zatrzyma sie na 4, bo check->next->priority = 2 nie jest wieksze rowne 3
			check = check->next;
		temp->next = check->next;
		check->next = temp;
		if(temp->next == NULL){
			rear = temp;
		}
		
	}
	
}

void Dequeue(){
	
	Node* temp = front; // temp do usuniecia
	if(isEmpty()){ // jesli kolejka jest pusta to nic nie rob
		std::cout << "Kolejka jest pusta" << std::endl;
		return;
	} 
		
	if(front == rear) // w kolejce jest jeden element
		front = rear = NULL;
	else // w kolejce jest wiecej elementow
		front = front->next; 
		
	free(temp); // na koncu funkcji, niezaleznie czy front == rear albo czy w kolejce jest wiecej elementow, free(temp) zawsze sie wykona(za wyjatkiem przypadku front==NULL, bo wtedy jest return)
	
		
		
}

void PrintLinia(Linia l, int nr_linii,FILE* zapis){
	
	std::cout << "Linia Nr " << nr_linii << std::endl;	
	int prior = l.priority;
	
	//FILE* zapis;
	//zapis =  fopen("wy.txt", "w");
		 switch(prior){
		 	
		 	case 0:
		 		std::cout << "Kod klienta: SILVER \nNr klienta: " << l.nr_klienta
		 		<< "\nCzas rozmowy: " << l.czas_rozmowy << std::endl;
				fprintf(zapis, "SILVER %d %d\n",l.nr_klienta, l.czas_rozmowy);
		 		break;
		 	case 1:
		 		std::cout << "Kod klienta: GOLD \nNr klienta: " << l.nr_klienta
		 		<< "\nCzas rozmowy: " << l.czas_rozmowy << std::endl;
		 		fprintf(zapis, "GOLD %d %d\n",l.nr_klienta, l.czas_rozmowy);
		 		break;
		 	case 2:
		 		std::cout << "Kod klienta: PLATINUM \nNr klienta: " << l.nr_klienta
		 		<< "\nCzas rozmowy: " << l.czas_rozmowy << std::endl;
		 		fprintf(zapis, "PLATINUM %d %d\n",l.nr_klienta, l.czas_rozmowy);
		 		break;
		 }
	std::cout << "--------------------------------------------------------------" << std::endl;
	//fclose(zapis);
}

int main(int argc, char** argv) {
	
	/*Enqueue(SILVER,1,20); 
	Enqueue(SILVER,2,25);
	Enqueue(PLATINUM,3,20); 
	Enqueue(GOLD,4,10); 
	Enqueue(SILVER,5,50);*/
	
	std::ifstream plik;
	
	plik.open("we.txt"); // otwieranie pliku we.txt
	if (!plik) {
        std::cout << "Nie mozna otworzyc pliku" << std::endl;
        return 1;
    }
    while (!plik.eof()) {

		char priority;
		int nr_klienta,czas_rozmowy;
		
        plik >> priority >> nr_klienta >> czas_rozmowy;
        
        Enqueue(priority,nr_klienta,czas_rozmowy);
      
    }
    
    plik.close();
	
	
	Linia l1,l2,l3;
	l1.zajete = false; // na poczatku linie sa puste
	l2.zajete = false;
	l3.zajete = false;
	
	FILE* zapis; // zapis do pliku.txt
	zapis =  fopen("wy.txt", "w");
	
	int i = 0;
	while(front != NULL){
		std::cout << "********************Iteracja " << ++i << "***************************" << std::endl;
		
		// odblokowywanie miejsc wzgledem dlugosci rozmow
		if(l1.zajete == true && l2.zajete == true && l2.zajete == true)	{ // jezeli wszystkie linie sa zajete
			// gdy pierwsza linia ma najkrotsza rozmowe
			if(l1.czas_rozmowy <= l2.czas_rozmowy && l1.czas_rozmowy <= l3.czas_rozmowy){
				l1.zajete = false;
			}	
			
			// gdy druga linia  ma najkrotsza rozmowe
			else if(l2.czas_rozmowy <= l1.czas_rozmowy && l2.czas_rozmowy <= l3.czas_rozmowy){
				l2.zajete = false;
			}	
			
			// gdy trzecia linia ma najkrotsza rozmowe
			else if(l3.czas_rozmowy <= l1.czas_rozmowy && l3.czas_rozmowy <= l2.czas_rozmowy ){
				l3.zajete = false;
			}	
			
		}
		// zajecie linii i rownoczesne zwolnienie miejsc z kolejki oczekujacej na zajecie linii
			
		if(l1.zajete == false){
			l1.zajete = true;
					
			l1.priority = front->priority;
			l1.nr_klienta = front->nr_klienta;
			l1.czas_rozmowy = front->czas_rozmowy;
			Dequeue();	
		}
				
		if(l2.zajete == false){
			l2.zajete = true;
				
			l2.priority = front->priority;
			l2.nr_klienta = front->nr_klienta;
			l2.czas_rozmowy = front->czas_rozmowy;
			Dequeue();	
		}
			
		if(l3.zajete == false){
			l3.zajete = true;
				
			l3.priority = front->priority;
			l3.nr_klienta = front->nr_klienta;
			l3.czas_rozmowy = front->czas_rozmowy;
			Dequeue();
		}
		
		fprintf(zapis, "********************Iteracja %d***************************\n",i);
		fprintf(zapis, "Linia 1: ");
		PrintLinia(l1,1,zapis);
		
		fprintf(zapis, "Linia 2: ");
		PrintLinia(l2,2,zapis);
		
		fprintf(zapis, "Linia 3: ");
		PrintLinia(l3,3,zapis);
	
		
		std::cout << "*********************************************************" << std::endl;
		std::cout << std::endl;
			
	}
	
	fclose(zapis);
			
	return 0;	
}	


#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
// WCY21IY4S1 Grabowski Mateusz Zad1

struct Node{
	int value;
	struct Node* next;
	
};

void Sito_Erasto(Node** head){ // usuwa nody z liczbami ktore nie sa pierwsze
	Node* temp1 = *head;
	Node* temp2 = *head; // wskazniki na pierwszy element listy
	Node* prev;
	while(temp1 != NULL){ // w tej petli wykonuje modulo isprime dla kazdej wartosci listy
		int isprime = temp1->value;
		if(isprime == 0) { // dla liczb ktore nie sa pierwsze (isprime==0), beda one usuwane
			
			prev->next = temp1->next;
			Node* usun = temp1;
			temp1 = temp1->next;
			temp2 = temp1;
			free(usun);
			continue;   // powtorz petle
		}
		while(temp2->next != NULL) { // w tej petli zamieniam liczby niepierwsze na 0
			if(temp2->next->value%isprime==0) 
				temp2->next->value = 0; // przypisanie zera dla liczb ktore nie sa pierwsze
			temp2=temp2->next;	
			
		}
		prev = temp1;
		temp1=temp1->next;
		temp2=temp1;
	}
}

void Insert_back(Node** ptr2head,int n){
    
    //Node* temp = new Node(); 
    
    Node* temp = (Node*)malloc(sizeof(Node));
   
    if(*ptr2head==0){
        temp->value = 2; // pierwsza wartosc listy
    	temp->next = NULL;
		*ptr2head = temp;
    }
    for(int i=3; i<=n;i++) {
		//Node* new_ptr = new Node(); // zapelniam kolejne elementy indeksami i
		Node* new_ptr = (Node*)malloc(sizeof(Node));
		new_ptr->value = i;
		new_ptr->next = NULL;
		
		temp->next = new_ptr;
		temp = new_ptr;
	}
	

}

void Zapisz(Node* head){
	
	std::ofstream outfile; // outfile bedzie dzialac jak std::cout
	
	outfile.open("wy.txt"); // proba otworzenia pliku
	
	if(outfile){  // sprawdza czy plik sie rzeczywiscie otworzyl, jezele plik wczesniej nie istnial, tworzy ten plik, jezeli plik juz istnial, nadpisuje go w calosci(nie dopisuje danych)
		
		int licznik = 0;
		
		while(head!=NULL){
        	licznik++;
        	outfile << "\t" << head->value;
        	if(licznik%10 == 0){
        		outfile << std::endl;
			}
        	head = head->next;
		}
			
		outfile.close();
		std::cout << "Wypisano dane do pliku wy.txt" << std::endl;
		std::cout << "Nacisnij enter, aby kontynuowac...";
		getch();
	}
	else{
	
		std::cout << "Nie udalo sie wypisac danych do pliku wy.txt" << std::endl;
		std::cout << "Nacisnij enter, aby kontynuowac...";
		getch();
	}	
}

void Print(Node* head){ // wypisuje po 10  w linii

    int licznik = 0;
	std::cout << "List: " << std::endl;
    while(head!=NULL){
        licznik++;
        std::cout <<"\t"<< head->value;
        if(licznik%10 == 0){
        	std::cout << std::endl;
		}
        if(head->next == NULL){
        	break;
		}
		head = head->next;
    }
    std::cout << std::endl;
}

int main(){
	
	Node* head = NULL;
	int n;
	std::cout << "Podaj zakres gorny przedzialu: " << std::endl;
	std::cin >> n;
	Insert_back(&head, n);
	Print(head);
	Sito_Erasto(&head);
	Print(head);
	Zapisz(head);
	
	return 0;
}

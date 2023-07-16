#include <iostream>
#include <fstream>
#include <iosfwd>
// WCY21IY4S1 Grabowski Mateusz 
// erastotenes dwukierunkowa funkcje , to samo juz co mam w erastotenes dwukierunkowa
struct Node{
	int value;
	struct Node* next;
	struct Node* prev;
	
};

/*void Sito_Erasto(Node** head){ // zapelnia zerami
	Node* temp1 = *head;
	Node* temp2 = *head; // wskazniki na pierwszy element listy
	
	while(temp1->next != NULL){ // w tej petli wykonuje modulo isprime dla kazdej wartosci listy
		int isprime = temp1->value;
		if(isprime == 0) { // dla liczb ktore nie sa pierwsze bedzie przypisywane zero, jezeli isprime==0 to oba wskazniki przesuwamy w prawo
			temp1=temp1->next;
			temp2=temp1;
			continue;   // powtorz petle
		}
		while(temp2->next != NULL) { // w tej petli zamieniam liczby niepierwsze na 0
			if(temp2->next->value%isprime==0) 
				temp2->next->value = 0; // przypisanie zera dla liczb ktore nie sa pierwsze
			temp2=temp2->next;	
			
		}
		
		temp1=temp1->next;
		temp2=temp1;
	}
}*/

void Sito_Erasto(Node** head){ // usuwa nody z liczbami ktore nie sa pierwsze
	Node* temp1 = *head;
	Node* temp2 = *head; // wskazniki na pierwszy element listy
	
	while(temp1 != NULL){ // w tej petli wykonuje modulo isprime dla kazdej wartosci listy
		int isprime = temp1->value;
		if(isprime == 0) { // dla liczb ktore nie sa pierwsze (isprime==0), beda one usuwane
			temp1->prev->next = temp1->next;
			if(temp1->next != 0)
				temp1->next->prev = temp1->prev;
			Node* usun = temp1;
			temp1 = temp1->next;
			temp2 = temp1;
			delete usun;
			continue;   // powtorz petle
		}
		while(temp2->next != NULL) { // w tej petli zamieniam liczby niepierwsze na 0
			if(temp2->next->value%isprime==0) 
				temp2->next->value = 0; // przypisanie zera dla liczb ktore nie sa pierwsze
			temp2=temp2->next;	
			
		}
		
		temp1=temp1->next;
		temp2=temp1;
	}
}

void Insert_back(Node** ptr2head,int n){
    
    Node* temp = new Node();
   
    if(*ptr2head==0){
        temp->value = 2; // pierwsza wartosc listy
    	temp->next = NULL;
    	temp->prev = NULL;
		*ptr2head = temp;
    }
    for(int i=3; i<=n;i++) {
		Node* new_ptr = new Node(); // zapelniam kolejne elementy indeksami i
		new_ptr->value = i;
		new_ptr->next = NULL;
		new_ptr->prev = temp;
		
		temp->next = new_ptr;
		temp = new_ptr;
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
	int zakres;
	std::cout << "Podaj zakres gorny przedzialu: " << std::endl;
	std::cin >> zakres;
	Insert_back(&head, zakres);
	Print(head);
	Sito_Erasto(&head);
	Print(head);
	
	return 0;
}

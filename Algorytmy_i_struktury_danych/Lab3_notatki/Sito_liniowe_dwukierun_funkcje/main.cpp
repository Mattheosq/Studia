#include <iostream>

// sito liniowe dwukierunkowe, funkcje
struct Node{
	
	int value;
	struct Node* next;
	struct Node* prev;
};

void Sito_liniowe(Node** ptr2head, int grna_granica){
	
	int p,q,x; // x= p^k * q k=1,2,3...
	
	p = 2; // przypisuje pierwsza wartosc rowna 2 do p, jest to pierwszy mnoznik
	while(p*p <= grna_granica){
		
		q = p; // drugi mnoznik
		while(p*q <= grna_granica){
			
			x = p * q;
			while(x <= grna_granica){ // usuwanie wyliczonego x'a z listy
				Node* temp2 = *ptr2head;		
				while(temp2 != 0){
					if(temp2->value == x){
						
						temp2->prev->next = temp2->next;
						if(temp2->next != 0){
							temp2->next->prev = temp2->prev;
						}
						
						Node* usun = temp2;
						temp2 = temp2->next;
						
						delete usun;
						break;
					}
					else{
						temp2 = temp2->next;	
					}
				}
				
				x = p * x;
			}
			//q nastepne
			q++;
		}
		// p nastepne	
		p++;
		
	}
	
}

void Insert_back(Node** ptr2head, int n){
	
	Node* temp = new Node(); // pierwszy node zawiera liczbe 2
	
	temp->value = 2;
	temp->prev = NULL;
	temp->next = NULL;
	*ptr2head = temp;
	
	for(int i=3; i <= n; i++){
		
		Node* new_ptr = new Node();
		new_ptr->value = i;
		new_ptr->next = NULL;
		new_ptr->prev = temp;
			
		temp->next = new_ptr;
		temp = temp->next;
		
	}
	
	
	
}

void Print(Node* head){

	int licznik = 0;
	std::cout << "List: " << std::endl;
    while(head!=NULL){
        licznik++;
        std::cout <<"\t"<< head->value;
        if(licznik%10 == 0){
        	std::cout << std::endl;
		}
        head = head->next;
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {
	
	Node* head = NULL;
	
	int grna_granica;
	std::cout << "Podaj gorna granice przedzialu: " << std::endl;
	std::cin >> grna_granica;
	
	Insert_back(&head, grna_granica);
	Print(head);
	Sito_liniowe(&head, grna_granica);
	Print(head);
	
	return 0;
}

#include <iostream>
#include <bits/stdc++.h>

// atkin jednokierunkowa funkcje

struct Node{
	
	int value;
	struct Node* next;
};

void Sito_Atkin(Node** ptr2head,int grna_granica){
	
	
	/* Liczba jest pierwsza gdy:
		1.W rownaniu 4x^2+y^2 = z, z jest nieparzyste oraz modulo 12 daje 1 lub 5
		2.W rownaniu 3x^2+y^2 = z, z jest nieparzyste oraz modulo 12 daje 7
		3.W rownaniu 3x^2-y^2 = z, z jest nieparzyste oraz modulo 12 daje 11 oraz x>y
		4.Nie jest kwadratem liczby, ktora w poprzednich krokach zostala okreslona jako pierwsza
	*/
	
	//************Sito*********************
	
	bool sito[grna_granica + 1]; // tworze tablice wartosci binarnych i zapelniam ja poczatkowo wartosciami 0(false)
	
	for(int i=0;i<=grna_granica;i++){
		sito[i] = false;
	}
	
	if(grna_granica > 2)
		sito[2] = true;
		
	if(grna_granica > 3)
		sito[3] = true;
	
	for(int x = 1; x*x <= grna_granica; x++){
		for(int y = 1; y*y <= grna_granica; y++){
			
			int z = (4*x*x) + (y*y);
			if(z <= grna_granica  && (z % 12 == 1 || z % 12 == 5))
				sito[z] = !sito[z];  // zamienia z false na true lub z true na false
				
			z = (3*x*x) + (y*y);
			if(z <= grna_granica && z % 12 == 7)
				sito[z] = !sito[z];
				
			z = (3*x*x) - (y*y);
			if(z <= grna_granica && z % 12 == 11 & x > y)
				sito[z] = !sito[z];
		}
	}
	
	for(int i = 5; i*i <= grna_granica; i++){  // sprawdzam czy kwadrat liczby 'i' miesci sie w przedziale
		if(sito[i] == true){
			for(int j = i*i; j<= grna_granica; j += i*i) // dla kazdej wielokrotnosci 'i^2' przypisywana jest wartosc false 
				sito[j] = false;
		}
	}
	
	
	//************Usuwanie z listy liczb, ktore nie sa pierwsze************************
    
    Node* prev = *ptr2head;
    Node* cur = prev->next; // wskazuje na nastepny node
	for(int i=3; i<=grna_granica;i++) { // indeks 'i' odpowiada liczbie ktora sprawdzamy czy dla sito[i] wynosi true, jesli tak to 'i' jest liczba pierwsza , dla i=2 cur wskazywalby na 5, po czym go usunal, co wywoluje blad
		if(sito[i] == false){
			prev->next = cur->next; // laczy poprzednik tego co usuwamy z jego nastepnikiem
			Node* temp = cur; // chwilowy wskaznik ktory bedziemy usuwac
			cur = cur->next; // przesuwam cur aby ponownie z niego skorzystac w petli
			delete temp;		
		}
		else{
			prev = cur;
			cur = cur->next;	
		}	
	
	}
	
	
}




void Insert_back(Node** ptr2head, int n){
	
	Node* temp = new Node(); // pierwszy node zawiera liczbe 2
	
	temp->value = 2;
	temp->next = NULL;
	*ptr2head = temp;
	
	for(int i=3; i <= n; i++){
		
		Node* new_ptr = new Node();
		new_ptr->value = i;
		new_ptr->next = NULL;
			
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
	Insert_back(&head,grna_granica);
	Print(head);
	Sito_Atkin(&head,grna_granica);
	std::cout << "Liczby pierwsze: " << std::endl;
	Print(head);
	
	
	return 0;
}

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <conio.h>
// WCY21IY4S1 Grabowski Mateusz Zad2 
struct Node{
	int value;
	Node* next;
	
};

void Push(int x, Node** top) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->value = x;
	temp->next = *top;
	*top = temp;
}

void Pop(Node** top){
	
	Node* temp;
	if(*top == NULL)
		return;
	temp = *top;
	*top = temp->next;
	free(temp);
}

Node* Dodawanie(Node* top1,Node* top2){
	
	Node* top3; // wskaznik na szczyt stosu wynikowego
	int suma = 0;
	int reszta = 0;
	
	while(top1 != 0 && top2 != 0){
		suma = (top1->value) + (top2->value) + reszta; // obliczam suma cyfr zaczynajac od cyfr jednosci
		Push(suma%10,&top3); // do stosu wynikowego przekazuje sume tych cyfr
		reszta = suma / 10; // reszta jest typu int, dlatego wyniki zmiennoprzecinkowe beda zaokraglane w dol
		Pop(&top1); // usuwam gorne elementy obu stosow, aby wskaznik na szczyt stosu wskazywal na kolejny element
		Pop(&top2);
	}
	
	while(top1 != 0){ // warunek dla top1 ktore sie jeszcze nie wyzerowalo
		
		suma = (top1->value) + reszta;
		Push(suma%10,&top3);
		reszta = suma / 10; // dla sumy < 10, pozbywam sie reszty
		Pop(&top1);
	}
	
	while(top2 != 0){ // warunek dla top2 ktore sie jeszcze nie wyzerowalo
		
		suma = (top2->value) + reszta;
		Push(suma%10,&top3);
		reszta = suma / 10;
		Pop(&top2);
		
	}
	
	while(reszta > 0){ // jezeli na koncu zostala jeszcze jakas reszta, dodaje ja do stosu
		
		Push(reszta,&top3);
		reszta = reszta / 10;
	}
	
	return top3; // top3 otrzymuje jako odwrocony stos (na dole sa jednosci, mimo ze wczesniej domyslnie byly na gorze)
	// jednak w tej formie otrzymujemy czytelny dla uzytkownika wynik dodawania, dlatego top3 nie trzeba ponownie odwracac(reverse)
	
}


void Print(Node* head){ // wypisuje po 10  w linii

	std::cout << "Wynik: " << std::endl;
    while(head!=NULL){
        std::cout << head->value;
		head = head->next;
    }
    std::cout << std::endl;
}

void Zapisz(Node* head){
	
	std::ofstream outfile; // outfile bedzie dzialac jak std::cout
	
	outfile.open("wy.txt"); // proba otworzenia pliku
	
	if(outfile){  // sprawdza czy plik sie rzeczywiscie otworzyl, jezele plik wczesniej nie istnial, tworzy ten plik, jezeli plik juz istnial, nadpisuje go w calosci(nie dopisuje danych)
		
		outfile << "Wynik: ";
		while(head!=NULL){
        	outfile << head->value;
        	head = head->next;
		}
			
		outfile.close();
		std::cout << "Wypisano dane do pliku wy.txt" << std::endl;
	}
	else{
	
		std::cout << "Nie udalo sie wypisac danych do pliku wy.txt" << std::endl;
	}	
}

/*void Odczyt(Node* top1,Node* top2){
	std::ifstream infile; // infile bedzie dzialac jak std::cout
	
	infile.open("we.txt"); // proba otworzenia pliku
	
	if(infile){  // sprawdza czy plik sie rzeczywiscie otworzyl, jezele plik wczesniej nie istnial, tworzy ten plik, jezeli plik juz istnial, nadpisuje go w calosci(nie dopisuje danych)
		
		int x;
		while(infile >> x){ // poki do input stream chce cos wejsc z pliku, wykonuj petle
			if(x == -1)
				break;
			Push(x,&top1);
		}
		int y;
		while(infile >> y){ // poki do input stream chce cos wejsc z pliku, wykonuj petle
			Push(x,&top2);
		}
		
		infile.close();
	}
	else{
	
		std::cout << "Nie udalo sie wczytac danych z pliku we.txt" << std::endl;
	}	
}*/

int main(int argc, char** argv) {
	
	//std::cout << "Czy chcesz odczytac dane z pliku we.txt? Tak(0), nie(1)" << std::endl;
	//int odpowiedz;
	//std::cin >> odpowiedz;
	//if(odpowiedz == 1){
		std::cout << "Podaj ilosc cyfr pierwszej liczby: " << std::endl;
		int ilosc1;
		std::cin >> ilosc1;
		Node* top1 = NULL; // wskaznik na szczyt pierwszego stosu
		std::cout << "Podaj kolejno cyfry pierwszej liczby" << std::endl;
		for(int i=0;i<ilosc1;i++){
			int x;
			std::cin >> x;
			Push(x,&top1);
		}
		
		std::cout << "Podaj ilosc cyfr drugiej liczby: " << std::endl;
		int ilosc2;
		std::cin >> ilosc2;
		Node* top2 = NULL; // wskaznik na szczyt drugiego stosu
		std::cout << "Podaj kolejno cyfry pierwszej liczby" << std::endl;
		for(int i=0;i<ilosc2;i++){
			int x;
			std::cin >> x;
			Push(x,&top2);
		}
		
		Node* wynik = Dodawanie(top1,top2);
		Print(wynik);
		Zapisz(wynik);
	//}
	/*if(odpowiedz == 0){
		Node* top1 = NULL;
		Node* top2 = NULL;
		Odczyt(top1,top2);
		Node* wynik = Dodawanie(top1,top2);
		Print(wynik);
		Zapisz(wynik);
	}*/
	
	
	
	
	return 0;
}

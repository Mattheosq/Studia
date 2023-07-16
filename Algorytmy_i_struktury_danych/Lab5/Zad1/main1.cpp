#include <iostream>
#include <cstdlib>
// WCY21IY4S1 Grabowski Mateusz Zad1
struct Node{
	int value;
	Node* next;
};

void Push(Node** top, int x){ 
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->value = x;
	temp->next = *top;
	*top = temp;
}

int Pop(Node** top){ // zwraca int, dzieki czemu usuwajac zapamietuje ktory dysk wyjelismy ze stosu, zeby byc w stanie przeniesc go potem na inny stos
	if(*top == NULL)
		return -1;
	Node* temp = *top;
	*top = temp->next;
	int pamiec = temp->value; // zapamietuje usuwana wartosc
	free(temp);
	return pamiec;
}

void Print(Node* top){
	Node* temp = top;
	while(top != NULL){
		std::cout << top->value << " ";
		top = top->next;
	}
	std::cout << std::endl;
	
}
int main(int argc, char** argv) {
	
	int x,y,N;
	int dysk; // do dysk bedzie przypisywany zapamietany dysk z funkcji Pop()
	Node* top1 = NULL;// wskazniki na 3 stosy
	Node* top2 = NULL;
	Node* top3 = NULL;
	
	
	while(true){
		std::cout << "Podaj liczbe dyskow: ";
		std::cin >> N;
		if(N <= 8){
			break;
		}
		else{
			std::cout << "Podaj zmienna, ktora jest mniejsza od 9" << std::endl;
		}
	
	
	}
	
	for(int i=0;i<N;i++) // zapelnij pierwszy stos dyskami, najwiekszy dysk ma wartosc 0, mniejszy 1 itd.
    {
        Push(&top1,i);
    }
    
    std::cout << "Najwiekszy dysk jest oznaczony jako 0, mniejszy 1 itd." << std::endl;
	std::cout << "Stos A(start)" << std::endl;
    Print(top1);
    std::cout << "------------------------------" << std::endl;
    
    for(int i=1;i < 1<<N;i++){ /* implementacja binarna, 1<<n to przesuniecie bitowe w lewo, czyli kolejne potegi dwojki, dla n=3 1<<n wynosi 8
    wiemy ze ilosc powtorzen musi byc rowna 2^n - 1, dlatego iteracje zaczynamy od i=1*/
    	
		x=(i&i-1) % 3; // warunek na wyciagniecie dysku z jednego ze stosow np. dla i=1 mamy 1&0 % 3 => 0 % 3 = 0, czyli usunie nam najpierw z pierwszego stosu
	    y=((i|i-1)+1) % 3; // warunek na przeniesienie dysku do jednego ze stosow np. dla i=1 mamy (1|0)+1 % 3 => 1+1 % 3 = 2, czyli doda nam na trzeci stos
	   
	    switch(x) // wyciaganie dysku
	    {
	        case 0: 
				dysk = Pop(&top1); // z pierwszego stosu
		        break;
	        case 1: 
				dysk = Pop(&top2); // z drugiego
		        break;
	        case 2: 
				dysk = Pop(&top3); // z trzeciego
		        break;
	    }
	
	    switch(y) // wsadzanie dysku
	    {
	        case 0: 
				Push(&top1,dysk); // do pierwszego
		        break;
	        case 1: 
				Push(&top2,dysk); // do drugiego
		        break;
	        case 2: 
				Push(&top3,dysk); // do trzeciego
		        break;
	    }
	    
		std::cout << "Krok " << i << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cout << "Stos A" << std::endl;
		Print(top1);
	    std::cout << "Stos B" << std::endl;
		Print(top2);
	    std::cout << "Stos C" << std::endl;
		Print(top3);
	    std::cout << std::endl;
    	
	}
	return 0;
}

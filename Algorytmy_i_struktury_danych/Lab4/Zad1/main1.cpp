#include <iostream>
#include <cstdlib>
#include <string>
// WCY21IY4S1 Grabowski Mateusz Zad1
struct Node{
	char value;
	Node* next;
};


int Pierwszenstwo(char znak)
{
    if (znak == '^')
        return 3;
    else if (znak == '/' || znak == '*' || znak == '%')
        return 2;
    else if (znak == '+' || znak == '-')
        return 1;
    else
        return -1;
}

void Push(char x, Node** top) {
	
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
	*top = (*top)->next;
	free(temp);
}

void InfixToPostfix(std::string s){ 
	
	Node* top; // wskaznik na szczyt stosu operatorow
	std::string result = "";
	for(int i=0;i<s.length();i++){
		
		char znak = s[i];
		if((znak >= 'a' && znak <= 'z') || (znak >= 'A' && znak <= 'Z') || (znak >= '0' && znak <= '9')) // sprawdza, czy znak jest operandem
			result += znak; // tworze nowego stringa w formie postfixowej
		else if(znak == '(') // dopisujemy na stos
			Push('(', &top);	
		else if(znak == ')'){ // dopisz do result operatory az do nawiasu (
			while(top->value != '('){
				result += top->value;
				Pop(&top);
			}
			Pop(&top);
		}
		else{
			while(top != NULL && Pierwszenstwo(s[i]) <= Pierwszenstwo(top->value) ){ // sprawdz czy nie trzeba wyciagnac operatora ze stosu z wyzszym pierwszenstwem
				result += top->value;
				Pop(&top);
			}
			Push(znak, &top); // dodaje operator do stacka
			
		}
	}
	while(top->next != NULL){
		result += top->value;
		Pop(&top);
	}
	std::cout << "Postfix: " << result << std::endl;
	
}
int main(int argc, char** argv) {
	
	std::string wyrazenie;
	std::cout << "Podaj wyrazenie bez spacji" << std::endl;
	std::getline(std::cin, wyrazenie);
	std::cout << "Infix: " << wyrazenie << std::endl;
	
	InfixToPostfix(wyrazenie);
	
	return 0;
}


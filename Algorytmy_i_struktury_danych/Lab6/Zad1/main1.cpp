//WCY21IY4S1 Grabowski Mateusz Zad1
#include <iostream>
#include <cstdlib>
#include <conio.h>


struct Node{ // struktura drzewa BST
	
	int data;
	Node* left; // lewy nastepnik
	Node* right; // prawy nastepnik
};

struct Queue{ // Kolejka
	
	Node* qNode; // node fifo, ktory przechowuje struktury Node
	Queue* next;
};

Queue* front = NULL; // wskaznik na pierwszy element kolejki
Queue* rear = NULL; // wskaznik na ostatni element kolejki

// przy dodawaniu do kolejki przesuwamy rear
// przy usuwaniu z kolejki przesuwamy front

// Kolejka Queue dla narysowania drzewa ////////
////////////////////////////////////////////////
void Enqueue(Node* root) { // tworze kolejke struktur Node pochodzacych z drzewa
    
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
//////////////////////////////////////////
//////////////////////////////////////////

Node* CreateNode(int data){ // domyslne tworzenie nowych node'ow drzewa
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}


// Dodanie wezla //////////////////
Node* Insert(Node* root, int data){
	if(root == NULL){
		root = CreateNode(data);
	}
	else if(data <= root->data){
		root->left = Insert(root->left, data); // rekurencja, dodanie na lewa strone
	}
	else{
		root->right = Insert(root->right, data); // dodanie na prawa strone
	}
	
	return root;
}

Node* FindMin(Node* root){
	while(root->left != NULL){
		root = root->left;
	}
	return root;
}
// Usuwanie wezla /////////////////
Node* Delete(Node* root, int data){
	if(root == NULL)
		return root;
	else if(data < root->data)
		root->left = Delete(root->left,data);
	else if(data > root->data)
		root->right = Delete(root->right,data);
	else{ // do usuniecia
		
		if(root->left == NULL && root->right == NULL){ // gdy nie ma potomka
			free(root);
			root = NULL;
		}
		else if(root->left == NULL){ // gdy jest jeden potomek z prawej
			Node* temp = root;
			root = root->right;
			free(temp);
		}
		else if(root->right == NULL){ // gdy jest jeden potomek z lewej
			Node* temp = root;
			root = root->left;
			free(temp);
		}
		else{
			Node* current = FindMin(root->right);
		
			root->data = current->data;
			root->right = Delete(root->right,current->data);
			
		}
		
	}
	return root;
}
// Usuwanie drzewa //////////////// sprobowac z kolejka
void _DeleteTree(Node* root){ // post-order
	if(root == NULL)
		return;
	// usuwanie poddrzew
	_DeleteTree(root->left);
	_DeleteTree(root->right);
	
	std::cout << "\nUsuwam " << root->data;
	free(root);
	
}

void DeleteTree(Node** root){ // po _DeleteTree zostaje dangling pointer, ktorego trzeba sie pozbyc
	_DeleteTree(*root);
	*root = NULL;
}
// Narysowanie drzewa /////////////
void DrawTree(Node* root, int l){ //rekurencyjnie
	
	if(root == NULL)
		return;
	DrawTree(root->right, l+1);
	for(int i=0; i<l; i++)
		std::cout << "\t";
	std::cout << root->data << "\n";
	DrawTree(root->left, l+1);
}


// Szukanie wezla /////////////////
Node* FindByValue(Node* root, int data){  
	
	while(root != NULL){
		if(data == root->data)  
			return root;
		
		else if(data < root->data) // przejdz do lewego poddrzewa
			root = root->left;
		
		else if(data > root->data) // przejdz do prawego poddrzewa
			root = root->right;
	}
	
	return NULL;
}


// Przechodzenie////////////////////
////////////////////////////////////

// korzystamy z kolejki Queue, root jest dodawany do kolejki, po czym jest odczytywany, co oznacza, ze korzen zostal odwiedzony
// nastepnie do kolejki dodawane sa lewe i prawe nastepniki;wezly

// to co jest w kolejce, jest odkryte i przygotowuje sie do bycia odwiedzonym
// to co bedzie wypisane, zostanie odwiedzone



// w g³¹b (rekurencyjnie)

// LVR, in-order ///////////////////
void InOrder(Node* root){
	if(root == NULL)
		return;
	
	InOrder(root->left);//L
	std::cout << root->data << " "; //V
	InOrder(root->right);//R
}
// VLR, pre-order //////////////////
void PreOrder(Node* root){ 
	if(root == NULL)
		return;
	
	std::cout << root->data << " "; //V
	PreOrder(root->left);//L
	PreOrder(root->right);//R
}
// LRV, post-order /////////////////
void PostOrder(Node* root){
	if(root == NULL)
		return;
	
	PostOrder(root->left);//L
	PostOrder(root->right);//R
	std::cout << root->data << " "; //V
}


int main(int argc, char** argv) {
	
	Node* root = NULL;
	
	int choice;
	do
    {
        system("cls");
        std::cout << "***************************************************" << std::endl
        << "(1) Dodaj element do drzewa" << std::endl
        << "(2) Usun element z drzewa" << std::endl
        << "(3) Wyczysc drzewo" << std::endl
        << "(4) Narysuj drzewo" << std::endl
        << "(5) Przechodzenie LVR, in-order" << std::endl
        << "(6) Przechodznie VLR, pre-order " << std::endl
        << "(7) Przechodzenie LRV, post-order" << std::endl
        << "(8) Szukanie elementu w drzewie" << std::endl
        << "(0) Zakoncz dzialanie programu" << std::endl;
        std::cout << "***************************************************" << std::endl;
        std::cin >> choice;
        
        switch(choice){
        	
			case 0:
         		exit(0);
				break;
            
			case 1:
         		int added_data;
         		std::cout << "Podaj wartosc, ktora chcesz dodac do drzewa BST" << std::endl;
         		std::cin >> added_data;
				root = Insert(root, added_data);
                break;
        
            case 2:
				int deleted_data;
				std::cout << "Podaj wartosc, ktora chcesz usunac z drzewa" << std::endl;
				std::cin >> deleted_data;
				root = Delete(root, deleted_data);
                break;

            case 3:
               	DeleteTree(&root);
               	std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
				break;
				
            case 4:
                std::cout << "Drzewo BST(obrocone w lewo): " << std::endl;
				DrawTree(root, 0);
                std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
               	break;
               	
            case 5:
               	std::cout << "Przejscie In-order: " << std::endl;
               	InOrder(root);
               	std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
				break;
				
            case 6:
                std::cout << "Przejscie Pre-order: " << std::endl;
				PreOrder(root);
                std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
                break;
            
            case 7:
            	std::cout << "Przejscie Post-order: " << std::endl;
            	PostOrder(root);
            	std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
				break;
            	
            case 8:
            	int find_data;
            	std::cout << "Podaj szukana wartosc" << std::endl;
            	std::cin >> find_data;
				Node* temp = FindByValue(root, find_data);
            	if(temp == NULL){
            		std::cout << "Nie znaleziono takiej wartosci" << std::endl;
            		std::cout << "Kliknij enter, by kontynuowac..." << std::endl;
					getch();
				}
				else{
					std::cout << "Podana wartosc " << temp->data << " wystepuje w drzewie" << std::endl;
					std::cout << "Kliknij enter, by kontynuowac..." << std::endl;
					getch();
				}
            	break;
            		
        }		
        
    } while (true);
	
	return 0;
}

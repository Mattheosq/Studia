//WCY21IY4S1 Grabowski Mateusz Zad2
#include <iostream>
#include <cstdlib>
#include <conio.h>

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
	std::cout << std::endl;
}
// Narysowanie kopca /////////////
void DrawTree(Node* root, int x){ //rekurencyjnie
	
	if(root == NULL)
		return;
	DrawTree(root->right, x+1);
	for(int i=0; i<x; i++)
		std::cout << "\t";
	std::cout << root->data << "\n";
	DrawTree(root->left, x+1);
}

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

int main() {
  	
  	Node* root = NULL;
  	
	int choice;
	do
    {
        system("cls");
        std::cout << "***************************************************" << std::endl
        << "(1) Dodaj element do kopca maksymalnego" << std::endl
        << "(2) Usun maksymalny element(korzen)" << std::endl
        << "(3) Wyczysc kopiec" << std::endl
        << "(4) Narysuj kopiec" << std::endl
        << "(5) Przechodzenie LVR, in-order" << std::endl
        << "(6) Przechodznie VLR, pre-order " << std::endl
        << "(7) Przechodzenie LRV, post-order" << std::endl
        << "(0) Zakoncz dzialanie programu" << std::endl;
        std::cout << "***************************************************" << std::endl;
        std::cin >> choice;
        
        switch(choice){
        	
			case 0:
         		exit(0);
				break;
            
			case 1:
         		int added_data;
         		std::cout << "Podaj wartosc, ktora chcesz dodac do kopca" << std::endl;
         		std::cin >> added_data;
				root = Insert(root, added_data);
                break;
        
            case 2:
				
				root = DeleteMax(root);
				std::cout << "Usunieto korzen" << std::endl;
				std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
                break;

            case 3:
               	DeleteTree(&root);
               	std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
				break;
				
            case 4:
                std::cout << "Kopiec(obrocony w lewo) : " << std::endl;
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
            	
            		
        }		
        
    } while (true);
  	
    return 0;
}

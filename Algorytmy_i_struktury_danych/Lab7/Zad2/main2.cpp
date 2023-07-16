//WCY21IY4S1 Grabowski Mateusz Zad2
#include <iostream>
#include <cstdlib>
#include <conio.h>

struct Node{ // struktura drzewa RB
	int data; 
	char color; // kolor elementu
	Node* left; 
	Node* right; 
	Node* parent;
};


// rotacje
void LeftRotate(Node** root, Node* x)
{
	if(x == NULL || x->right == NULL)
		return ;
	// y przechowuje wskaznik na prawego potomka x
	Node *y = x->right;

	x->right = y->left; // przechowujemy wskaŸnik na lewe poddrzewo y jako prawy potomek x
	if (x->right != NULL)
	    x->right->parent = x;// zmieniamy parent pointer prawgo poddrzewa x
	
	y->parent = x->parent; // zmieniamy parent pointer y'greka
	
	if (x->parent == NULL) // jezeli parent na nic nie wskazuje , to ustaw y jako root
	    (*root) = y;
	
	else if (x == x->parent->left) // przechowujemy y w x
	    x->parent->left = y;
	else    
		x->parent->right = y;
	

	y->left = x; 	// tworzymy z x lewego potomka
	x->parent = y; 	//zmieniamy parent pointer x'sa
}


void RightRotate(Node** root, Node* y) // analogicznie
{
	if (y == NULL || y->left == NULL)
		return ;
	Node *x = y->left;
	
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;
	
	x->parent =y->parent;
	
	if (x->parent == NULL)
		(*root) = x;
	
	else if (y == y->parent->left)
		y->parent->left = x;
	else 
		y->parent->right = x;
	
	x->right = y;
	y->parent = x;
}

// Funkcja naprawiajaca drzewo RB po wstawieniu elementu do drzewa

// Jezeli y jest czerwony:
// 1.Zamienic kolor parenta i y(uncle) na czarny
// 2.Zamienic kolor rodzica rodzica na czerwony
// 3.Ustawic sie na rodzicu rodzica
void InsertFixUp(Node** root, Node* z)
{
	// iteracja poki z nie jest root'em i kolor rodzica to czerwony
	while (z != *root && z != (*root)->left && z != (*root)->right && z->parent->color == 'R')
	{
		Node *y;
	
	    // znalezienie i przechowanie adresu node'a 'uncle' w zmiennej y
	    if (z->parent && z->parent->parent && z->parent == z->parent->parent->left)
	        y = z->parent->parent->right;
	    else
	        y = z->parent->parent->left;
	
	    
	    if (y == NULL)
	        z = z->parent->parent;
	    else if (y->color == 'R')
	    {
	        y->color = 'B';
	        z->parent->color = 'B';
	        z->parent->parent->color = 'R';
	        z = z->parent->parent;
	    }
	
	    // Jezeli y(uncle) jest czarny
	    else
	    {
	        // Left-Left
	        if (z->parent == z->parent->parent->left &&
	            z == z->parent->left)
	        {
	            char ch = z->parent->color ;
	            z->parent->color = z->parent->parent->color;
	            z->parent->parent->color = ch;
	            RightRotate(root,z->parent->parent);
	        }
	
	        // Left-Right
	        if (z->parent && z->parent->parent && z->parent == z->parent->parent->left && z == z->parent->right)
	        {
	            char ch = z->color ;
	            z->color = z->parent->parent->color;
	            z->parent->parent->color = ch;
	            LeftRotate(root,z->parent);
	            RightRotate(root,z->parent->parent);
	        }
	
	        // Right-Right 
	        if (z->parent && z->parent->parent && z->parent == z->parent->parent->right && z == z->parent->right)
	        {
	            char ch = z->parent->color ;
	            z->parent->color = z->parent->parent->color;
	            z->parent->parent->color = ch;
	            LeftRotate(root,z->parent->parent);
	        }
	
	        // Right-Left 
	        if (z->parent && z->parent->parent && z->parent == z->parent->parent->right && z == z->parent->left)
	        {
	            char ch = z->color ;
	            z->color = z->parent->parent->color;
	            z->parent->parent->color = ch;
	            RightRotate(root,z->parent);
	            LeftRotate(root,z->parent->parent);
	        }
	    }
	}
	
	(*root)->color = 'B'; //utrzymujemy root jako czarny
}

// Dodawanie wezla
void Insert(Node** root, int data)
{
	
	Node* z = (Node*)malloc(sizeof(Node));
	
	z->data = data;
	z->left = NULL;
	z->right = NULL;
	z->parent = NULL;
	
	if(*root == NULL)
	{
	    z->color = 'B';
	    (*root) = z;
	}
	else
	{
	    Node *y = NULL;
	    Node *x = (*root);
	
	    while (x != NULL)
	    {
	        y = x;
	        if (z->data < x->data)
	            x = x->left;
	        else
	            x = x->right;
	    }
	    z->parent = y;
	    if (z->data > y->data)
	        y->right = z;
	    else
	        y->left = z;
	    z->color = 'R';
	
	    InsertFixUp(root,z);
	}
}

Node* FindMin(Node* root){
	while(root->left != NULL){
		root = root->left;
	}
	return root;
}


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

void _DeleteTree(Node* root){ // post-order
	if(root == NULL)
		return;
	// usuwanie poddrzew
	_DeleteTree(root->left);
	_DeleteTree(root->right);
	
	std::cout << "\nUsuwam " << root->data << root->color;
	free(root);
	
}

void DeleteTree(Node** root){ // po _DeleteTree zostaje dangling pointer, ktorego trzeba sie pozbyc
	_DeleteTree(*root);
	*root = NULL;
}

void DrawTree(Node* root,int l) // rekurencyjnie
{
	if(root){
		l+=10;
		DrawTree(root->right,l);
		std::cout << "\n\n";
		for(int i= 10; i<l; i++)
		{
			std::cout << " ";
		}
		std::cout << root->data <<  root->color;
		DrawTree(root->left,l);
	}
}


void InOrder(Node* root){
	if(root == NULL)
		return;
	
	InOrder(root->left);//L
	std::cout << root->data << root->color << " "; //V
	InOrder(root->right);//R
}

void PreOrder(Node* root){ 
	if(root == NULL)
		return;
	
	std::cout << root->data << root->color << " "; //V
	PreOrder(root->left);//L
	PreOrder(root->right);//R
}
// LRV, post-order /////////////////
void PostOrder(Node* root){
	if(root == NULL)
		return;
	
	PostOrder(root->left);//L
	PostOrder(root->right);//R
	std::cout << root->data << root->color << " "; //V
}

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

int main(int argc, char** argv)
{
	Node* root= NULL;
	
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
         		std::cout << "Podaj wartosc, ktora chcesz dodac do drzewa RB" << std::endl;
         		std::cin >> added_data;
				Insert(&root, added_data);
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
                std::cout << "Drzewo RB(obrocone w lewo): " << std::endl;
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


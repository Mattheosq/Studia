//WCY21IY4S1 Grabowski Mateusz Zad1
#include <iostream>
#include <cstdlib>
#include <conio.h>

struct Node{ // struktura drzewa AVL
	
	int data;
	Node* left; // lewy nastepnik
	Node* right; // prawy nastepnik
};


Node* CreateNode(int data){ // domyslne tworzenie nowych node'ow drzewa
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int FindHeight(Node* root){ // rekurencyjnie // wysokosc od zadanego korzenia korzen->podkorzen->lisc => wyskokosc od korzenia to 2, wysokosc od podkorzenia to 1
	if(root == NULL)
		return -1; // wysokosc node'a liscia wynosi zero(zalozenie) // brak nodow, wysokosc = -1, jeden node(korzen), wysokosc = 0 itd.
	return std::max(FindHeight(root->left),FindHeight(root->right)) + 1; // +1 zwieksza wysokosc co rekurencje
	
}
//       x	height=0
//    y		height=1
// z		height=2

int GetBalanceFactor(Node* root){ // funkcja uzyta w sprawdzeniu rownowagi
	if(root == NULL)
		return -1;
	else
		return	(FindHeight(root->left)-FindHeight(root->right));
}

Node* RightRotate(Node* root){
	Node* rootl = root->left; // wskazuje na lewo od root; root left
	Node* rootlr = rootl->right; // wskazuje na prawo od root->left; root left then right;zapamietuje ten stan
	
	// rotacja
	
	rootl->right = root; // lewy node od root laczymy z root(prawy wskaznik lewego node'a wskazuje na root), oba na tym etapie wskazuja na siebie(lewy wskaznik root'a wskazuje na lewy node)
	root->left = rootlr; // teraz zmieniamy lewy wskaznik root'a, lewy wskaznik root'a wskazuje teraz nie na lewy node, tylko na node, ktory znajdowal sie po prawej stronie od tego lewego node'a
	return rootl; // po ratacji lewy node, na ktory wskazuje rootl, stal sie glownym korzeniem
}

Node* LeftRotate(Node* root){ // analogicznie
	Node* rootr = root->right;
	Node* rootrl = rootr->left; // x root , y rootr , T2 rootrl
	
	// rotacja
	
	rootr->left = root;
	root->right = rootrl;
	return rootr;
}

// Dodanie wezla //////////////////
Node* Insert(Node* root, int data){ // *new_node == data
	if(root == NULL){
		root = CreateNode(data);
		return root;
	}
	if(data < root->data){
		root->left = Insert(root->left, data); // rekurencja, dodanie na lewa strone
	}
	else if(data > root->data){
		root->right = Insert(root->right, data); // dodanie na prawa strone
	}
	else{
		std::cout << "Duplikaty sa niedozwolone" << std::endl;
		return root;
	}
	
	// rotacje	
	// przy dodaniu drugiego elementu drzewo nadal jest zrownowazone
	// imbalance zaczyna sie od dodania trzeciego elementu(dolaczajac go pod juz istniejace root->left albo root->right)
	int balance_factor = GetBalanceFactor(root); // sprawdza czy drzewo bedzie zrownowazone(bedzie dla -1,0,1)
												
	//LEFT-LEFT imbalance
	if(balance_factor > 1 && data < root->left->data){ // element trafil do lewej strony korzenia, w poddrzewie tez znajduje sie po lewej stronie, z czego wynika nierownosc z lewej strony
		return RightRotate(root); // trzeba obrocic w prawo, by bylo zrownowazenie
	}
	//RIGHT-RIGHT imbalance
	if(balance_factor < -1 && data > root->right->data){ // element trafil do prawej strony z czego wynika nierownosc z prawej strony, w poddrzewie tez znajduje sie po prawej stronie
		return LeftRotate(root);
	}
	//LEFT-RIGHT imbalance 
	if(balance_factor > 1 && data > root->left->data){ // element trafil do lewej strony korzenia, ale jest prawym nastepnikiem ktoregos podkorzenia,
														//  z czego wynika lewa nierownosc, ale trzeba zrotowac podkorzen raz w lewo, a dopiero potem cale drzewo w prawo
		root->left = LeftRotate(root->left); // obracamy podkorzen w lewo
		return RightRotate(root); // obracamy cale drzewo w prawo
	}
	//RIGHT-LEFT imbalance 
	if(balance_factor < -1 && data < root->right->data){ // analogicznie, tym razem najpierw raz w prawo, a potem calkowicie w lewo
		
		root->right = RightRotate(root->right); // obracamy podkorzen w prawo; rotacja w prawo wzgledem root->right
		return LeftRotate(root); // obracamy drzewo w lewo; rotacja w lewo wzgledem root
	}
	
	return root; // zwraca korzen drzewa AVL
}

Node* FindMin(Node* root){
	while(root->left != NULL){
		root = root->left;
	}
	return root;
}
// Usuwanie wezla /////////////////
Node* Delete(Node* root, int data){ // rekurencyjnie
	if(root == NULL)
		return root;
	else if(data < root->data)
		root->left = Delete(root->left,data);
	else if(data > root->data)
		root->right = Delete(root->right,data);
	else{ // gdy zajdzie rownosc
		
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
		else{ // gdy sa dwa potomki
			Node* current = FindMin(root->right);
		
			root->data = current->data;
			root->right = Delete(root->right,current->data);
			
		}
			
	}
	// usuwanie AVL
	
	int balance_factor = GetBalanceFactor(root);						//				korzen				korzen
																	//				lewo		lub		lewo
	if(balance_factor == 2 && GetBalanceFactor(root->left) >= 0){ //2 przypadki: lewo				lewo	lprawo
		return RightRotate(root);
	}
																			//					korzen
																			//				lewo
	else if(balance_factor == 2 && GetBalanceFactor(root->left) == -1){ //1 przypadek:  		lprawo
		root->left = LeftRotate(root->left);
		return RightRotate(root);
	}
																			//				korzen					korzen
																		//						prawo		lub     	prawo
	else if(balance_factor == -2 && GetBalanceFactor(root->right) <= 0){ // 2 przypadki: 			prawo		   plewo	prawo
		return LeftRotate(root);
	}
																			//					korzen
																			//						prawo
	else if(balance_factor == -2 && GetBalanceFactor(root->right) == 1){ // 1 przypadek:     	plewo
		root->right = RightRotate(root->right);
		return LeftRotate(root);
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
         		std::cout << "Podaj wartosc, ktora chcesz dodac do drzewa AVL" << std::endl;
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
                std::cout << "Drzewo AVL(obrocone w lewo): " << std::endl;
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

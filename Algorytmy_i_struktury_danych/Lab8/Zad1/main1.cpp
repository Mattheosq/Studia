//WCY21IY4S1 Grabowski Mateusz Zad1
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 

#define MAX 3 
#define MIN 1

struct btreeNode{ // struktura B-Drzewa stopnia 4 
    int num_keys; // liczba kluczy w wezle
    int keys[MAX+1]; // zerowy element tablicy pelni role bufora, jesli trafi do niego czwarta wartosc, wezel ulega podzieleniu, w wezle moga znajdowac sie maksymalnie 3 klucze
    struct btreeNode *children[MAX+1]; // tablica wskaznikow na dzieci, ktorych liczba wynosi maksymalnie 4
};

///////////// FUNKCJE POMOCNICZE ///////////////////////

// Funkcja szukajaca node'a z szukana wartoscia
int search_node(int val, struct btreeNode *n, int *pos){ 
    if(val < n->keys[1] ){ 
        *pos = 0; 
        return 0; 
    } 
    else{ 
        *pos = n->num_keys; 
        while ((val < n->keys[*pos]) && *pos > 1) 
            (*pos)--; 
        if (val == n->keys[*pos]) 
            return 1; 
        else return 0; 
    } 
} 
 
 
// Funkcja dostosowujaca wartosc wezla
void insert_adjust(int val, struct btreeNode *c, struct btreeNode *n, int k){ 
    int i; 
    
    for(i = n->num_keys; i > k;i--) { // przesuwanie wartosci tablicy
        n->keys[i+1] = n->keys[i]; 
        n->children[i+1] = n->children[i]; 
    } 
    n->keys[k+1] = val; // wstawienie nowej wartosci
    n->children[k+1] = c; 
    n->num_keys++; 
} 
 
// Funkcja dzielaca wezel
void split(int val, struct btreeNode *c, struct btreeNode *n, int k, int *y, struct btreeNode **newnode ){ // uzywa funkcji insert_adjust
    int i;
	int median; // zmienna reprezentujaca srodkowa wartosc w wezle
 
    if(k <= MIN) 
        median = MIN; 
    else 
        median = MIN + 1; 
 
    *newnode = (struct btreeNode*)malloc(sizeof(struct btreeNode)); // tworzenie node'a na wartosci po podzieleniu
 
    for (i = median + 1; i <= MAX; i++){ // przenoszenie wartosci wiekszych od mediany do nowego node'a
        (*newnode)->keys[i-median] = n->keys[i]; 
        (*newnode)->children[i-median] = n->children[i]; 
    } 
 
    (*newnode)->num_keys = MAX - median; 
    n->num_keys = median; 
 
    if(k <= MIN) 
        insert_adjust(val, c, n, k); 
    else 
        insert_adjust(val, c, *newnode, k - median); 
 
    *y = n->keys[n->num_keys]; 
    (*newnode)->children[0] = n->children[n->num_keys]; 
    n->num_keys--; 
}

// Funkcja usuwajaca wartosc z wezla i dostosowujaca reszte wartosci w wezle
void clear_value(struct btreeNode *node, int k){ 
    int i; 
    for(i = k + 1; i <= node->num_keys; i++){ 
        node->keys[i-1] = node->keys[i]; 
        node->children[i-1] = node->children[i]; 
    } 
    node->num_keys--; 
} 
 
// Funkcja kopiujaca sukcesor wezla wartosci, ktora zamierzamy usunac
void copy_successor(struct btreeNode *node, int i){ 
    struct btreeNode *temp; 
 
    temp = node->children[i]; 
 
    while(temp->children[0]) 
        temp = temp->children[0]; 
 
    node->keys[i] = temp->keys[1]; 
} 
/////////////////////////////////////////////////////////////////////


//////////////////////////// DODAWANIE WEZLA ////////////////////////
// Funkcja ustawiajaca wartosc w wezle
int insert_key(int val, struct btreeNode *n, int *p, struct btreeNode **c){ //rekurencyjnie, uzywa funkcji search_node, insert_adjust, split
    int k; 
    if(n == NULL) { 
        *p = val; 
        *c = NULL; 
        return 1; 
    } 
    else{ 
        if(search_node(val, n, &k)){
        	printf ("\nZadany klucz juz istnieje.\n");
        	printf("Kliknij enter, by kontynuowac...\n");
			getch();
        }
            
        if(insert_key(val, n->children[k], p, c)){ 
            if (n->num_keys < MAX){ 
                insert_adjust(*p, *c, n, k); 
                return 0; 
            } 
            else{ 
                split(*p, *c, n, k, p, c); 
                return 1; 
            } 
        } 
        return 0; 
    } 
} 


// Funkcja ustawiajaca wartosc w drzewie
struct btreeNode *insert_node(int val, struct btreeNode *root){ // korzysta z funkcji insert_key
    int i; 
    struct btreeNode *c, *n; 
    int flag; 
 
    flag = insert_key(val, root, &i, &c); 
    if(flag) 
    { 
        n = (struct btreeNode*)malloc(sizeof(struct btreeNode)); 
        n->num_keys = 1; 
        n->keys[1] = i; 
        n->children[0] = root; 
        n->children[1] = c; 
        return n; 
    } 
    return root; 
}

/////////////////////////////////////////////////////////////////////////

///////////////////////////// USUWANIE WEZLA ////////////////////////////

// Funkcja dostosowujaca wartosci i potomkow, przenoszac rownoczesnie wartosc z rodzica do lewego potomka
void leftshift ( struct btreeNode *node, int k ){ 
    int i; 
    struct btreeNode *temp; 
 
    temp = node->children[k-1]; 
    temp->num_keys++; 
    temp->keys[temp->num_keys] = node->keys[k]; 
    temp->children[temp->num_keys] = node->children[k]->children[0]; 
 
    temp = node->children[k]; 
    node->keys[k] = temp->keys[1]; 
    temp->children[0] = temp->children[1]; 
    temp->num_keys--; 
 
    for (i = 1; i <= temp->num_keys; i++){ 
        temp->keys[i] = temp->keys[i+1]; 
        temp->children[i] = temp->children[i+1]; 
    } 
} 

// Funkcja dostosowujaca wartosci i potomkow, przenoszac rownoczesnie wartosc z rodzica do prawego potomka
void rightshift(struct btreeNode *node, int k){ 
    int i; 
    struct btreeNode *temp; 
 
    temp = node->children[k]; 
 
    for(i = temp->num_keys; i > 0; i--){ 
        temp->keys[i+1] = temp->keys[i]; 
        temp->children[i+1] = temp->children[i]; 
    } 
 
    temp->children[1] = temp->children[0]; 
    temp->num_keys++; 
    temp->keys[1] = node->keys[k]; 
 
    temp = node->children[k-1]; 
    node->keys[k] = temp->keys[temp->num_keys]; 
    node->children[k]->children[0] = temp->children[temp->num_keys]; 
    temp->num_keys--; 
} 
 

 
// Funkcja zlaczajaca wezly
void merge(struct btreeNode *node, int k){ 
    int i; 
    struct btreeNode *temp1, *temp2; 
 
    temp1 = node->children[k]; 
    temp2 = node->children[k-1]; 
    temp2->num_keys++; 
    
    temp2->keys[temp2->num_keys] = node->keys[k]; 
    temp2->children[temp2->num_keys] = node->children[0]; 
 
    for( i = 1; i <= temp1 -> num_keys; i++ ){ 
        temp2->num_keys++; 
        temp2->keys[temp2->num_keys] = temp1->keys[i]; 
        temp2->children[temp2->num_keys] = temp1->children[i]; 
    } 
    for(i = k; i < node->num_keys; i++){ 
        node->keys[i] = node->keys[i+1]; 
        node->children[i] = node->children[i+1]; 
    } 
    node->num_keys--; 
    free(temp1); 
} 

// Funkcja dostosowujaca wezel, przywraca wlasnosci B-Drzewa
void restore(struct btreeNode *node, int i){ // uzywa funkcji leftshift, merge, rightshift
    if (i == 0){ 
        if(node->children[1]->num_keys > MIN) 
            leftshift(node, 1); 
        else 
            merge(node, 1); 
    } 
    else{ 
        if(i == node->num_keys){ 
            if(node->children[i-1]->num_keys > MIN) 
                rightshift(node, i); 
            else 
                merge(node, i); 
        } 
        else{ 
            if(node->children[i-1]->num_keys > MIN) 
                rightshift (node, i); 
            else{ 
                if(node->children[i + 1]->num_keys > MIN) 
                    leftshift(node, i + 1); 
                else 
                    merge(node, i); 
            } 
        } 
    } 
} 

// funkcja pomocnicza dla funkcji delete_node()
int delete_node_helper(int val, struct btreeNode *root){ // rekurencyjnie, uzywa funkcji search_node, copy_successor, clear_value, restore
    int i; 
    int flag; 
    if(root == NULL) 
        return 0; 
    else{ 
        flag = search_node(val, root, &i); 
        if(flag){ 
            if(root->children[i-1]){ 
                copy_successor(root, i); 
                flag = delete_node_helper(root->keys[i], root->children[i]);      
            } 
            else 
                clear_value(root, i); 
        } 
        else 
            flag = delete_node_helper (val, root->children[i]); 
 
        if(root->children[i] != NULL){ 
            if(root->children[i]->num_keys < MIN) 
                restore(root, i);
        } 
        return flag; 
    } 
}

// usuwa wartosc z wezla
struct btreeNode *delete_node(int val, struct btreeNode *root){ // uzywa funkcji delete_node_helper
    struct btreeNode *temp; 
    if (!delete_node_helper(val, root)){
    	printf ( "\nNie znaleziono wartosci %d\n", val);
		printf("Kliknij enter, by kontynuowac...\n");
		getch(); 
    	
	} 
    else{ 
        if(root->num_keys == 0){ 
            temp = root; 
            root = root->children[0]; 
            free(temp); 
        } 
    } 
    return root; 
} 

//////////////////////////////////////////////////////////////////////////////

///////////////////////// WYSZUKIWANIE WEZLA ///////////////////////////////
struct btreeNode *search(int val, struct btreeNode *root, int *pos){ // rekurencyjnie,uzywa funkcji search_node
    if (root == NULL) 
        return NULL; 
    else{ 
        if(search_node(val, root, pos)) 
            return root; 
        else 
			return search(val, root->children[*pos], pos); 
    } 
}
///////////////////////// RYSOWANIE DRZEWA ///////////////////////////////////
void draw_tree(struct btreeNode *root, int l){
	if(root){
		int i;
		for(i = 1; i <= l; i++){
			printf("-");
		}
		for(i = 1; i <= root->num_keys; i++){
			if(i == 1)
				printf("{");
			printf(" %d ", root->keys[i]);
			if(i == root->num_keys)
				printf("}");
		}
		printf("\n");
		for(i = 0; i <= root->num_keys; i++){
			draw_tree(root->children[i], l + 10);
		}
		
	}
}

///////////////////////// WYSWIETLANIE INORDER ///////////////////////////////
void inorder(struct btreeNode *root){ // rekurencyjnie
    int i; 
 
    if(root != NULL){ 
        for (i = 0; i < root->num_keys; i++){ 
            inorder(root->children[i]); 
            printf("%d\t", root->keys[i + 1]); 
        } 
        inorder(root->children[i]); 
    } 
} 

int main( ) 
{ 
    int pos; // zmienna inicjalizowana w funkcji lokalnej po przekazaniu jej adresu jako parametr funkcji
	struct btreeNode *root; // wskaznik na korzen drzewa
    root = NULL; 
    
    int choice;
	do
    {
        system("cls");
        
        printf("***************************************************\n");
        printf("(1) Dodaj element do B-Drzewa\n");
        printf("(2) Usun element z B-Drzewa\n");
        printf("(brak) Wyczysc B-Drzewo\n");
        printf("(4) Narysuj B-Drzewo\n");
        printf("(5) Przechodzenie LVR, in-order\n");
        printf("(6) Szukanie elementu w B-Drzewie\n");
        printf("(0) Zakoncz dzialanie programu\n");
        printf("***************************************************\n");
        scanf("%d",&choice);
        
        switch(choice){
        	
			case 0:
         		exit(0);
				break;
            
			case 1:
         		int added_data;
         		printf("Podaj wartosc, ktora chcesz dodac do B-Drzewa\n");
         		scanf("%d",&added_data);
				root = insert_node(added_data, root);
                break;
        
            case 2:
				int deleted_data;
				printf("Podaj wartosc, ktora chcesz usunac z B-Drzewa\n");
				scanf("%d",&deleted_data);
				root = delete_node(deleted_data, root);
                break;

            case 3:
               	/*DeleteTree(&root);
               	std::cout << "\nKliknij enter, by kontynuowac..." << std::endl;
				getch();
				break;*/
				
            case 4:
                printf("B-Drzewo (dlugosc linii '---' reprezentuje poziom jaki zajmuje wezel '{}' w drzewie)\n");
                printf("(W pierwszej kolumnie jest korzen, w nastepnej kolumnie jego potomkowie...\n");
                printf("...w kolejnej potomkowie potomka do momentu az bedzie puste miejsce w tej kolumnie)\n");
                printf("(tzn. linia '---' sie cofnie)\n");
				draw_tree(root, 0);
                printf("\nKliknij enter, by kontynuowac...\n");
				getch();
               	break;
               	
            case 5:
               	printf("Przejscie In-order: \n");
               	inorder(root);
               	printf("\nKliknij enter, by kontynuowac...\n");
				getch();
				break;
				
            case 6:
                int searched_data;
				printf("Podaj szukana wartosc\n");
                scanf("%d",&searched_data);
				struct btreeNode *found_node = search(searched_data, root, &pos);
			    if(found_node == NULL){
			    	printf("Nie znaleziono takiej wartosci\n");
			    	printf("Kliknij enter, by kontynuowac...\n");
			    	getch();
				}
				else{
					int i;
					for(i = 0; i < found_node->num_keys + 1; i++){  
				        if(found_node->keys[i] == searched_data){
				            break;
				        }
			    	}
					printf("Znaleziono szukana wartosc %d w drzewie. Zajmuje %d miejsce w szukanym wezle.\n", found_node->keys[i],i);
					printf("Kliknij enter, by kontynuowac...\n");
					getch();
				}
            	break;
            		
        }		
        
    } while (true);
    
    return 0;
} 


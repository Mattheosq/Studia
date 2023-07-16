//WCY21IY4S1 Grabowski Mateusz Zad1 (Merge Sort)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
	int data;
	struct Node* next;
};

// Funkcja dodaj�ca elementy na pocz�tek listy
void Insert_front(struct Node** head_ptr, int data)
{
	
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	new_node->data = data;
	new_node->next = (*head_ptr);
	(*head_ptr) = new_node;
}
// Funkcja rozdzielaj�ca list� na dwie cz�ci
void split(struct Node* source, struct Node** front, struct Node** back)
{
	struct Node* cur; // wska�nik, kt�ry porusza si� powoli
	struct Node* nxt; //wska�nik, kt�ry porusza si� szybko
	cur = source;
	nxt = source->next;

	// Przesuni�cie wska�nika nxt o dwa elementy, oraz przesuni�cie cur o jeden element
	while (nxt != NULL) {
		// Przesuni�cie wska�nika nxt o jeden element
		nxt = nxt->next;
		
		// Je�li nxt nie jest NULL, przesuni�cie wska�nika cur o jeden element
    	// i przesuni�cie wska�nika nxt o kolejny element
		if (nxt != NULL) {
			cur = cur->next;
			nxt = nxt->next;
		}
	}

	// cur jest przed po�ow� listy,wi�c dzieli j� na dwie cz�ci
	*front = source; // pierwsza cz�� to pierwotna lista
	*back = cur->next; // druga cz�� to elementy po po�owie listy
	cur->next = NULL; // od��czenie drugiej cz�ci od pierwszej
}

// Funkcja ��cz�ca dwie posortowane listy w jedn� posortowan� list�
struct Node* sorted(struct Node* x, struct Node* y)
{
	struct Node* result = NULL;

	// gdy lista jest pusta
	if (x == NULL)
		return y; // zwracanie niepustej listy
	else if (y == NULL)
		return x; // zwracanie niepustej listy

	 // Por�wnanie warto�ci pierwszego elementu obu list i umieszczenie mniejszej warto�ci na pocz�tku nowej listy
	if (x->data <= y->data) {
		result = x; // pierwszy element nowej listy to mniejsza warto��
		result->next = sorted(x->next, y); // rekurencyjne po��czenie reszty element�w pierwszej listy z drug� list�
	}
	else {
		result = y; // analogicznie jak wy�ej
		result->next = sorted(x, y->next); // drugiej z pierwsz�
	}
	return (result);
}

// Funkcja sortuj�ca list� korzystaj�ca z funckji split i sorted
void merge_sort(struct Node** head_ptr)
{
	struct Node* head = *head_ptr;
	struct Node* x;
	struct Node* y;

	// gdy lista jest pusta lub ma jeden element
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	// Podzia� head na podlisty x i y
	split(head, &x, &y);

	// Sortowanie rekurencyjne podlist
	merge_sort(&x);
	merge_sort(&y);
	
	// Po��czenie posortowanych podlist
	*head_ptr = sorted(x, y);

}

void display_list(struct Node* node)
{
	int i = 0;
	while (node != NULL) {
		printf("%d\t", node->data);
		node = node->next;
		if ((i + 1) % 10 == 0) {
            printf("\n");
        }
        i++;
	}
	printf("\n");
}

int main()
{
	
	int opcja;
	printf("(1) Generator\n");
	printf("(2) Plik wejsciowy\n");
	scanf("%d",&opcja);
	
	if(opcja == 1){
		/////////////////////////////////////////// GENERATOR
		struct Node* head = NULL;
		
		unsigned int n;
		printf("Podaj ilosc elementow ");
		scanf("%d",&n);
		
		int a,b;
		printf("Podaj zakres od a(>=0) do b(>=0) \n");
		printf("a: ");
		scanf("%d",&a);
		printf("\nb: ");
		scanf("%d",&b);
		
		srand(time(0));
		
		for(int i=0; i < n; i++){
			
			Insert_front(&head, rand() % (b - a + 1) + a);
		}
		printf("Przed sortowaniem: \n");
		display_list(head);
	
		merge_sort(&head);
	
		printf("Po sortowaniu: \n");
		display_list(head);
		/////////////////////////////////////////// GENERATOR
		
	}
	else if(opcja == 2){
		/////////////////////////////////////////// PLIK
		struct Node* head = NULL;
		FILE* file_pointer = NULL;
		char input_file[20];
		int x;
		printf("Podaj pelna nazwe pliku(np. we.txt): ");
		scanf("%s",input_file);
		
		file_pointer = fopen(input_file,"r");
		
		printf("Przed sortowaniem: \n");
		int i = 0;
		while(fscanf(file_pointer,"%d",&x)!=EOF){
			
			Insert_front(&head, x);
			printf("%d\t",x);
			if ((i + 1) % 10 == 0) {
	            printf("\n");
	        }
			i++;
		}
		printf("\n");
		fclose(file_pointer);
		
		merge_sort(&head);
			
		printf("Po sortowaniu: \n");
		display_list(head);
		////////////////////////////////////////////// PLIK
	}
	
	return 0;
}


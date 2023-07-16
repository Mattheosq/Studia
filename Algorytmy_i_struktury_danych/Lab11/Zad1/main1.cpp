//WCY21IY4S1 Grabowski Mateusz Zad1 (Merge Sort)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
	int data;
	struct Node* next;
};

// Funkcja dodaj¹ca elementy na pocz¹tek listy
void Insert_front(struct Node** head_ptr, int data)
{
	
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	new_node->data = data;
	new_node->next = (*head_ptr);
	(*head_ptr) = new_node;
}
// Funkcja rozdzielaj¹ca listê na dwie czêœci
void split(struct Node* source, struct Node** front, struct Node** back)
{
	struct Node* cur; // wskaŸnik, który porusza siê powoli
	struct Node* nxt; //wskaŸnik, który porusza siê szybko
	cur = source;
	nxt = source->next;

	// Przesuniêcie wskaŸnika nxt o dwa elementy, oraz przesuniêcie cur o jeden element
	while (nxt != NULL) {
		// Przesuniêcie wskaŸnika nxt o jeden element
		nxt = nxt->next;
		
		// Jeœli nxt nie jest NULL, przesuniêcie wskaŸnika cur o jeden element
    	// i przesuniêcie wskaŸnika nxt o kolejny element
		if (nxt != NULL) {
			cur = cur->next;
			nxt = nxt->next;
		}
	}

	// cur jest przed po³ow¹ listy,wiêc dzieli j¹ na dwie czêœci
	*front = source; // pierwsza czêœæ to pierwotna lista
	*back = cur->next; // druga czêœæ to elementy po po³owie listy
	cur->next = NULL; // od³¹czenie drugiej czêœci od pierwszej
}

// Funkcja ³¹cz¹ca dwie posortowane listy w jedn¹ posortowan¹ listê
struct Node* sorted(struct Node* x, struct Node* y)
{
	struct Node* result = NULL;

	// gdy lista jest pusta
	if (x == NULL)
		return y; // zwracanie niepustej listy
	else if (y == NULL)
		return x; // zwracanie niepustej listy

	 // Porównanie wartoœci pierwszego elementu obu list i umieszczenie mniejszej wartoœci na pocz¹tku nowej listy
	if (x->data <= y->data) {
		result = x; // pierwszy element nowej listy to mniejsza wartoœæ
		result->next = sorted(x->next, y); // rekurencyjne po³¹czenie reszty elementów pierwszej listy z drug¹ list¹
	}
	else {
		result = y; // analogicznie jak wy¿ej
		result->next = sorted(x, y->next); // drugiej z pierwsz¹
	}
	return (result);
}

// Funkcja sortuj¹ca listê korzystaj¹ca z funckji split i sorted
void merge_sort(struct Node** head_ptr)
{
	struct Node* head = *head_ptr;
	struct Node* x;
	struct Node* y;

	// gdy lista jest pusta lub ma jeden element
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	// Podzia³ head na podlisty x i y
	split(head, &x, &y);

	// Sortowanie rekurencyjne podlist
	merge_sort(&x);
	merge_sort(&y);
	
	// Po³¹czenie posortowanych podlist
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


//WCY21IY4S1 Grabowski Mateusz Zad2 (��czenie naturalne)
#include <stdlib.h>
#include <stdio.h>

FILE *file_pointer = NULL;// deklaracja wska�nika pliku wej�ciowego

// funkcja do scalania posortowanych liczb z plik�w pomocniczych do pliku 
void merge(FILE* file_pointer, char* input_file){
	
	// zmienne pomocnicze do przechowywania liczb
	int x;
	int y;
	
	file_pointer = fopen(input_file,"w");
	
	// deklaracja wska�nik�w plik�w pomocniczych
	FILE *temp_file1 = NULL;
    FILE *temp_file2 = NULL;
	temp_file1 = fopen("aux1.txt","r");
	temp_file2 = fopen("aux2.txt","r");	
	
	// ustawienie wska�nik�w na koniec dla obu plik�w pomocniczych	i zapisanie ostatnich pozycji
	fseek(temp_file1, 0, SEEK_END); 
    int last_position_1 = ftell(temp_file1);
    fseek(temp_file2, 0, SEEK_END); 
    int last_position_2 = ftell(temp_file2); 
	
	// przywr�cenie stanu pocz�tkowego wska�nik�w
	fseek(temp_file1, 0, SEEK_SET);
	fseek(temp_file2, 0, SEEK_SET);
	
	// zmienne do przechowywania aktualnej pozycji w pliku
	int current_position_1 = 0;
    int current_position_2 = 0;
	
	// p�tla scalaj�ca liczby z plik�w pomocniczych do pliku wej�ciowego
	while(current_position_1 != last_position_1 ||  current_position_2 != last_position_2 ){ 

		// odczytanie pierwszych liczb z obu plik�w pomocniczych
		fscanf(temp_file1,"%d ",&x);
		fscanf(temp_file2,"%d ",&y);
		
		// p�tla por�wnuj�ca i scalaj�ca liczby z obu plik�w pomocniczych, tak aby by�y posortowane niemalej�co
		while(x != 0 && y != 0){	
			if(x<=y){
				// zapisanie liczby i odczytanie nast�pnej liczby z pierwszego pliku pomocniczego do pliku wej�ciowego
				fprintf(file_pointer,"%d ",x);
				fscanf(temp_file1,"%d ",&x);
			}
			if(y<x){
				// zapisanie liczby i odczytanie nast�pnej liczby z drugiego pliku pomocniczego do pliku wej�ciowego
				fprintf(file_pointer,"%d ",y);
				fscanf(temp_file2,"%d ",&y);
			}	
		}
		// je�li sko�czy�y si� liczby z pierwszego pliku pomocniczego
		if(x == 0){
			while(y != 0){
				fprintf(file_pointer,"%d ",y); // zapisanie pozosta�ych liczb z drugiego pliku pomocniczego do pliku wej�ciowego
				fscanf(temp_file2,"%d ",&y); // odczytanie nast�pnej liczby z drugiego pliku pomocniczego
			}
		}
		// je�li sko�czy�y si� liczby z drugiego pliku pomocniczego
		if(y == 0){
			while(x != 0){
				fprintf(file_pointer,"%d ",x); // zapisanie pozosta�ych liczb z pierwszego pliku pomocniczego do pliku wej�ciowego
				fscanf(temp_file1,"%d ",&x); // odczytanie nast�pnej liczby z pierwszego pliku pomocniczego
			}
		}
		// aktualizacja pozycji w pliku
		current_position_1 = ftell(temp_file1);
        current_position_2 = ftell(temp_file2);
	}	
	fclose(file_pointer);
	fclose(temp_file1);
	fclose(temp_file2);
}

// funkcja dziel�ca plik wej�ciowy na pliki pomocnicze i sortuj�ca w nich liczby
void file_div(FILE* file_pointer, char* input_file){
    int was_first_time = 0;
	int buffer[3] = {0};
	int x;
	
	file_pointer = fopen(input_file,"r");
    
	FILE *temp_file1 = NULL;
    FILE *temp_file2 = NULL;
	temp_file1 = fopen("aux1.txt","w");
    temp_file2 = fopen("aux2.txt","w");
    
    // wska�nik do aktualnie u�ywanego pliku pomocniczego
    FILE *current_file;
    current_file = temp_file1; 

	
    rewind(file_pointer); // przesuni�cie wska�nika pliku wej�ciowego na pocz�tek
    
    // odczytanie pierwszych dw�ch liczb z pliku wej�ciowego
    if(was_first_time == 0){
        fscanf(file_pointer,"%d",&x);
        buffer[1]=x;
        fscanf(file_pointer,"%d",&x);
        buffer[2]=x;
        was_first_time = 1;       
    }
	
	// p�tla odczytuj�ca liczby z pliku wej�ciowego i sortuj�ca je do plik�w pomocniczych
    while(fscanf(file_pointer,"%d",&x)!=EOF){
        if(buffer[1]>=buffer[0]){
        	// zapisanie liczby do aktualnie u�ywanego pliku pomocniczego
            fprintf(current_file,"%d ",buffer[1]);
        }
        else if(buffer[1]<=buffer[0]){
        	// zapisanie znaku ko�ca linii do aktualnie u�ywanego pliku pomocniczego
            fprintf(current_file," 0\n");
            // zmiana aktualnie u�ywanego pliku pomocniczego
            if(current_file == temp_file1)
                current_file = temp_file2;
            else if(current_file == temp_file2)
                current_file = temp_file1;
			fprintf(current_file,"%d ",buffer[1]);
        }
        // przesuni�cie liczb w buforze
		buffer[0]= buffer[1];
		buffer[1]= buffer[2];
        buffer[2] = x;
    }
    // zapisanie pozosta�ych dw�ch liczb z bufora do pliku pomocniczego
	for(int i=0; i < 2; i++){ 
		
		if(buffer[1]>=buffer[0]){
			fprintf(current_file,"%d ",buffer[1]);	
		}
		else if(buffer[1]<=buffer[0]){
			fprintf(current_file," 0\n");
			if(current_file == temp_file1)
				current_file = temp_file2;
			else if(current_file == temp_file2)
				current_file =	temp_file1;
			fprintf(current_file,"%d 0\n",buffer[1]);	
		}
		buffer[0]= buffer[1];
		buffer[1]= buffer[2];
		buffer[2] = 0;		
	}
	fprintf(current_file," 0");
	
	fclose(file_pointer);
	fclose(temp_file1);
	fclose(temp_file2);
}

// funckja sprawdzaj�ca czy plik jest posortowany
int check_sorted(FILE* file_pointer, char* input_file){
	file_pointer = fopen(input_file,"r");
	int x,y; 
	if(file_pointer){
		rewind(file_pointer);
		fscanf(file_pointer,"%d",&x);
		while(fscanf(file_pointer,"%d",&y)!=EOF){
			if(y<x){ // nie jest posortowane, wtedy funkcja zwraca 0, kt�re powoduje kontynuowanie iterowania p�tli w main
				fclose(file_pointer);
				return 0;
			}
			x = y; // przechodzenie do nast�pnej liczby
		}
		fclose(file_pointer);
		return 1;
	}
	fclose(file_pointer);
	return 0;
}

// funkcja wypisuj�ca zawarto�� pliku
void display_file(char* input_file)
{
	int x;
	int iter = 0;
	file_pointer = fopen(input_file,"r");
	
	while(fscanf(file_pointer,"%d",&x)!=EOF){
		printf("%d\t",x);
		iter++;
		if(iter%10 == 0)
			printf("\n");
	}
	printf("\n");
}

int main(){
	
	char input_file[20];
	printf("Podaj pelna nazwe pliku(np. we.txt): ");
	scanf("%s",input_file);

	printf("Przed sortowaniem: \n");
	display_file(input_file);
		
	while(!check_sorted(file_pointer, input_file)){
		file_div(file_pointer, input_file);
		merge(file_pointer, input_file);
	}
	remove("aux1.txt");
	remove("aux2.txt");
		
	printf("Po sortowaniu: \n");
	display_file(input_file);
	
	return 0;
}



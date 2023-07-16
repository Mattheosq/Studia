//WCY21IY4S1 Grabowski Mateusz Zad2 (£¹czenie naturalne)
#include <stdlib.h>
#include <stdio.h>

FILE *file_pointer = NULL;// deklaracja wskaŸnika pliku wejœciowego

// funkcja do scalania posortowanych liczb z plików pomocniczych do pliku 
void merge(FILE* file_pointer, char* input_file){
	
	// zmienne pomocnicze do przechowywania liczb
	int x;
	int y;
	
	file_pointer = fopen(input_file,"w");
	
	// deklaracja wskaŸników plików pomocniczych
	FILE *temp_file1 = NULL;
    FILE *temp_file2 = NULL;
	temp_file1 = fopen("aux1.txt","r");
	temp_file2 = fopen("aux2.txt","r");	
	
	// ustawienie wskaŸników na koniec dla obu plików pomocniczych	i zapisanie ostatnich pozycji
	fseek(temp_file1, 0, SEEK_END); 
    int last_position_1 = ftell(temp_file1);
    fseek(temp_file2, 0, SEEK_END); 
    int last_position_2 = ftell(temp_file2); 
	
	// przywrócenie stanu pocz¹tkowego wskaŸników
	fseek(temp_file1, 0, SEEK_SET);
	fseek(temp_file2, 0, SEEK_SET);
	
	// zmienne do przechowywania aktualnej pozycji w pliku
	int current_position_1 = 0;
    int current_position_2 = 0;
	
	// pêtla scalaj¹ca liczby z plików pomocniczych do pliku wejœciowego
	while(current_position_1 != last_position_1 ||  current_position_2 != last_position_2 ){ 

		// odczytanie pierwszych liczb z obu plików pomocniczych
		fscanf(temp_file1,"%d ",&x);
		fscanf(temp_file2,"%d ",&y);
		
		// pêtla porównuj¹ca i scalaj¹ca liczby z obu plików pomocniczych, tak aby by³y posortowane niemalej¹co
		while(x != 0 && y != 0){	
			if(x<=y){
				// zapisanie liczby i odczytanie nastêpnej liczby z pierwszego pliku pomocniczego do pliku wejœciowego
				fprintf(file_pointer,"%d ",x);
				fscanf(temp_file1,"%d ",&x);
			}
			if(y<x){
				// zapisanie liczby i odczytanie nastêpnej liczby z drugiego pliku pomocniczego do pliku wejœciowego
				fprintf(file_pointer,"%d ",y);
				fscanf(temp_file2,"%d ",&y);
			}	
		}
		// jeœli skoñczy³y siê liczby z pierwszego pliku pomocniczego
		if(x == 0){
			while(y != 0){
				fprintf(file_pointer,"%d ",y); // zapisanie pozosta³ych liczb z drugiego pliku pomocniczego do pliku wejœciowego
				fscanf(temp_file2,"%d ",&y); // odczytanie nastêpnej liczby z drugiego pliku pomocniczego
			}
		}
		// jeœli skoñczy³y siê liczby z drugiego pliku pomocniczego
		if(y == 0){
			while(x != 0){
				fprintf(file_pointer,"%d ",x); // zapisanie pozosta³ych liczb z pierwszego pliku pomocniczego do pliku wejœciowego
				fscanf(temp_file1,"%d ",&x); // odczytanie nastêpnej liczby z pierwszego pliku pomocniczego
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

// funkcja dziel¹ca plik wejœciowy na pliki pomocnicze i sortuj¹ca w nich liczby
void file_div(FILE* file_pointer, char* input_file){
    int was_first_time = 0;
	int buffer[3] = {0};
	int x;
	
	file_pointer = fopen(input_file,"r");
    
	FILE *temp_file1 = NULL;
    FILE *temp_file2 = NULL;
	temp_file1 = fopen("aux1.txt","w");
    temp_file2 = fopen("aux2.txt","w");
    
    // wskaŸnik do aktualnie u¿ywanego pliku pomocniczego
    FILE *current_file;
    current_file = temp_file1; 

	
    rewind(file_pointer); // przesuniêcie wskaŸnika pliku wejœciowego na pocz¹tek
    
    // odczytanie pierwszych dwóch liczb z pliku wejœciowego
    if(was_first_time == 0){
        fscanf(file_pointer,"%d",&x);
        buffer[1]=x;
        fscanf(file_pointer,"%d",&x);
        buffer[2]=x;
        was_first_time = 1;       
    }
	
	// pêtla odczytuj¹ca liczby z pliku wejœciowego i sortuj¹ca je do plików pomocniczych
    while(fscanf(file_pointer,"%d",&x)!=EOF){
        if(buffer[1]>=buffer[0]){
        	// zapisanie liczby do aktualnie u¿ywanego pliku pomocniczego
            fprintf(current_file,"%d ",buffer[1]);
        }
        else if(buffer[1]<=buffer[0]){
        	// zapisanie znaku koñca linii do aktualnie u¿ywanego pliku pomocniczego
            fprintf(current_file," 0\n");
            // zmiana aktualnie u¿ywanego pliku pomocniczego
            if(current_file == temp_file1)
                current_file = temp_file2;
            else if(current_file == temp_file2)
                current_file = temp_file1;
			fprintf(current_file,"%d ",buffer[1]);
        }
        // przesuniêcie liczb w buforze
		buffer[0]= buffer[1];
		buffer[1]= buffer[2];
        buffer[2] = x;
    }
    // zapisanie pozosta³ych dwóch liczb z bufora do pliku pomocniczego
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

// funckja sprawdzaj¹ca czy plik jest posortowany
int check_sorted(FILE* file_pointer, char* input_file){
	file_pointer = fopen(input_file,"r");
	int x,y; 
	if(file_pointer){
		rewind(file_pointer);
		fscanf(file_pointer,"%d",&x);
		while(fscanf(file_pointer,"%d",&y)!=EOF){
			if(y<x){ // nie jest posortowane, wtedy funkcja zwraca 0, które powoduje kontynuowanie iterowania pêtli w main
				fclose(file_pointer);
				return 0;
			}
			x = y; // przechodzenie do nastêpnej liczby
		}
		fclose(file_pointer);
		return 1;
	}
	fclose(file_pointer);
	return 0;
}

// funkcja wypisuj¹ca zawartoœæ pliku
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



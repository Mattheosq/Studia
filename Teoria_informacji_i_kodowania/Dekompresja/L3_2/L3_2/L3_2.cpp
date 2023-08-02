#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void modify_file_name_extension1(char* str) {
    char* dot_ptr = strchr(str, '.');
    if (dot_ptr != NULL) {
        *dot_ptr = '\0';
        strcat_s(str, strlen(str) + 10, ".recovery");
    }
}

typedef struct HuffmanCode {

    unsigned char data; // znak
    int code[100]; // slowo kodowe
    int code_length; // dlugosc slowa kodowego
    struct HuffmanCode* next;

}HuffmanCode;

HuffmanCode* createNode(char data, int code_length,int arr[]) {
    HuffmanCode* newNode = (HuffmanCode*)malloc(sizeof(HuffmanCode));
    newNode->data = data;
    newNode->code_length = code_length;
    
    for (int i = 0; i < code_length; i++) {
        newNode->code[i] = arr[i];
    }
    
    
    newNode->next = NULL;
    return newNode;
}

void insertNode(HuffmanCode** head, char data, int code_length, int arr[]) { // dodawanie elementow do modelu w posortowany sposob
    if (*head == NULL) {
        *head = createNode(data, code_length, arr);
        return;
    }

    HuffmanCode* current = *head;
    while (current->next != NULL) {
        if (current->data == data) { // sprawdzanie czy nie powtarza sie dany znak
            return;
        }
        current = current->next;
    }

    if (current->data == data) { // sprawdzenie czy nie powtarza sie znak w ostatnim(lub pierwszym dodanym) node
        return;
    }
    else {
        current->next = createNode(data, code_length, arr);// tworzenie nowego node'a dla nowego znaku
    }
}


void printCodess(HuffmanCode* head) { // testowanie wypisywania listy slow kodowych
    if (head == NULL) {
        return;
    }
    while (head) {
        printf("char data: %c (0x%02X)\n", head->data, head->data);
        printf("int code[100]: ");
        for (int i = 0; i < head->code_length; i++) {
            printf("%d", head->code[i]);
        }
        printf("\nint code_length: %d\n\n", head->code_length);
        head = head->next;
    }
}

int findMaxCodeLength(HuffmanCode* head) { // zwracanie maksymalnej dlugosci slowa kodowego
    int maxCodeLength = 0;

    while (head != NULL) {
        if (head->code_length > maxCodeLength) {
            maxCodeLength = head->code_length;
        }
        head = head->next;
    }

    return maxCodeLength;
}


void decompressFile(char* argv[]) {

    char input_file_name[100], output_file_name1[100];
    FILE* output_file1;
    FILE* input_file;
    char* input_string;
    // otwarcie pliku wejsciowego i pozyskanie string'a z input_file
    strcpy_s(input_file_name, sizeof(input_file_name), argv[1]);
    errno_t err = fopen_s(&input_file, input_file_name, "rb");
    if (err != 0) {
        printf("Nie udalo sie otworzyc pliku %s\n", input_file_name);
        return;
    }

    fseek(input_file, 0, SEEK_END);
    long size = ftell(input_file); // rozmiar pliku rowny rozmiarowi zakodowanej wiadomosci
    fseek(input_file, 0, SEEK_SET);

    input_string = (char*)malloc(size);
    fread_s(input_string, size, 1, size, input_file);

    fclose(input_file);
    
    // wypisywanie do pliku wyjsciowego
    // zmiana rozszerzen
    modify_file_name_extension1(input_file_name);
    strcpy_s(output_file_name1, sizeof(output_file_name1), input_file_name);

    HuffmanCode* head_list2 = NULL; // lista slow kodowych

    //############ DEKOMPRESJA ####################
    // Przeksztalcenie bajtow na bity i zapisanie ciagu bitow jako string

    char* buffer = (char*)malloc(9 * sizeof(char)); // miejsce na przeksztalcenie odczytanego bajtu na 8 bitow jako znaki w stringu
    char* final_string = NULL;
    for (int i = 0; i < size; i++) { // iteruje po calej zakodowanej wiadomosci

        for (int j = 7; j >= 0; j--) { // petla przedstawiajaca dlugosc zakodowanego ciagu binarnie jako string
            buffer[7 - j] = ((input_string[i] >> j) & 1) + '0';
        }
        buffer[8] = '\0';
        
        if (final_string == NULL) {
            final_string = (char*)malloc((8 * size * sizeof(char)) + 1);
            strcpy_s(final_string, (8 * size * sizeof(char)) + 1, buffer);
        }
        else {
            strcat_s(final_string, (8 * size * sizeof(char)) + 1, buffer);
        }
        
    }
    printf("%s\n", final_string);
    printf("Liczba bitow final stringa: %ld\n", strlen(final_string));

    // plik wyjsciowy .recovery
    err = fopen_s(&output_file1, output_file_name1, "wb");
    if (err != 0) {
        printf("Nie udalo sie utworzyc/otworzyc pliku wyjsciowego  %s\n", output_file_name1);
        return;
    }

    int message_size = 0; // dlugosc zakodowanej wiadomosci w bitach
    int info_count = 0; // liczba slow kodowych
    int current_bit = 0;
    
    // odczytanie czesci informacyjnej
    for (int i = 0; i < 16; i++) {
        message_size = (message_size << 1) + (final_string[i] - '0');
    }
    printf("message size: %d\n", message_size);
    current_bit += 16;

    for (int i = 0; i < 8; i++) {
        info_count = (info_count << 1) + (final_string[current_bit + i] - '0');
    }
    printf("info count: %d\n", info_count);
    current_bit += 8;

   
    HuffmanCode* head = NULL;
    int code[100];
    
    for (int i = 0; i < info_count; i++) {

        unsigned char data = 0;
        int code_length = 0;
        for (int j = 0; j < 8; j++) {
            data = (data << 1) + (final_string[current_bit + j] - '0');
        }
        current_bit += 8;
        for (int j = 0; j < 8; j++) {
            code_length = (code_length << 1) + (final_string[current_bit + j] - '0');
        }
        current_bit += 8;
        for (int j = 0; j < code_length; j++) {
            code[j] = (final_string[current_bit + j] - '0');
        }
        current_bit += code_length;

        insertNode(&head, data, code_length, code);

    }
    // odczytanie zakodowanej wiadomosci
    
    HuffmanCode* current = head;
    
    int max_code_length = findMaxCodeLength(head);
    unsigned char* output_string = NULL;
    long output_length = 0;
    
    char* temp_string = (char*)malloc(sizeof(char) * max_code_length + 1);
    temp_string[max_code_length] = '\0';
    int found = 0;
    int y = -1;
    
    for (int i = 0; i < message_size; i++) {
       
       
       if (found == 1) {
           temp_string = (char*)malloc(sizeof(char) * max_code_length + 1);
           y = 0;
           found = 0;
       }
       else {
           y++;
       }
       temp_string[y] = final_string[current_bit];
       temp_string[y + 1] = '\0';
       
       while (current) {
            char* code_string = (char*)malloc((sizeof(char) * (current->code_length + 1))); // co iteracje zamieniany jest int code na string i porownywany z temp
            for (int k = 0; k < current->code_length; k++) {
                code_string[k] = current->code[k] + '0'; 
            }
            code_string[current->code_length] = '\0';

            
            if (strncmp(temp_string, code_string, current->code_length) == 0) { // porownywane sa stringi do dlugosci stringa z listy slow kodowych, jesli oba stringi sa takie same, zwalnia sie pamiec temp i przechodzi sie do nastepnego bitu

                output_string = (unsigned char*)realloc(output_string, (output_length + 2) * sizeof(unsigned char));
                output_string[output_length] = current->data;
                output_string[output_length + 1] = '\0';

                output_length++;
                found = 1;
                free(temp_string);
                temp_string = NULL;
                break;
            }
            free(code_string);
            current = current->next;
       }
       current_bit++;
       current = head;
       if (i == message_size)
           free(temp_string);
        
    }
    printf("ZDEKODOWANY CIAG: \n");
    printf("Output length: %ld\n", output_length);
    int x = 0;
    while (x < output_length) {
        printf("%c", output_string[x]);

        x++;
    }
    printf("\n\n");
    fwrite(output_string, sizeof(unsigned char), output_length, output_file1); // wypisuje po bajcie az do output_length elementow

    fclose(output_file1);

    //printCodess(head);
    printf("\nZdekompresowano plik");
    free(buffer);
    free(output_string);
   
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Poprawna forma: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }

    decompressFile(argv);

    return 0;
}


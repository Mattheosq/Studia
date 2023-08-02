#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

////////////
// Stworzenie listy przechowujacej unikatowe znaki i ich czestosci, znajdujace sie w ciagu w przekazanym pliku, stanowi ona nieposortowany model informacji
typedef struct Node {
    char data;
    size_t frequency;
    struct Node* next;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->frequency = 1;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, char data) { // dodawanie elementow do modelu w posortowany sposob
    if (*head == NULL) {
        *head = createNode(data);
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        if (current->data == data) { // sprawdzanie czy nie powtarza sie dany znak
            current->frequency++;
            return;
        }
        current = current->next;
    }

    if (current->data == data) { // sprawdzenie czy nie powtarza sie znak w ostatnim(lub pierwszym dodanym) node
        current->frequency++;
    }
    else {
        current->next = createNode(data);// tworzenie nowego node'a dla nowego znaku
    }
}

void sortModel(Node** head) { // bubble sort
    if (*head == NULL || (*head)->next == NULL) { // pojedynczy node jest posortowany
        return;
    }

    int swapped;
    Node* current;
    Node* last = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != last) { // najmniejsza wartosc bedzie wypychana na koniec listy i oznaczona jako last, aby nie trzeba bylo iterowac ponownie po dlugosci calej listy
            if (current->frequency < current->next->frequency) {
                char tempData = current->data;
                size_t tempFrequency = current->frequency;
                current->data = current->next->data;
                current->frequency = current->next->frequency;
                current->next->data = tempData;
                current->next->frequency = tempFrequency;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped); // do momentu az dochodzi do zamian, petla sie wykonuje
}

size_t getSize(Node* head) { // policzenie elementow listy (unikatowych znakow)

    Node* current = head;
    size_t iter = 0;
    while (current != NULL) {
        current = current->next;
        iter++;
    }
    return iter;
}

void freeList(Node** head) { // zwolnienie pamieci
    Node* current = *head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}


/// ///////////////////////////////////////////////////////
// Kopiec minimalny przechowujacy dane z listy;modelu informacyjnego
// elementy kopca nie sa ze soba polaczone, kazdy element stanowi oddzielny korzen, ktory znajduje sie we wspolnej tablicy wskaznikow array struktury MinHeap
// po zapelnieniu tej tablicy, elementy sa sortowane pod wzgledem ich czestosci, tworzac poprawna strukture kopca minimalnego
// z tak utworzonego kopca minimalnego beda wyciagane dwa elementy o najmniejszych czestosciach(wyciagajac je z wierzcholka kopca)
// dla wyjetych elementow stworzony zostanie nowy, wspolny korzen, przechowujacy sume czestosci jego lisci
// tak utworzone poddrzewo jest zwracane do kopca; tablicy wskaznikow
// proces jest powtarzany az kopiec bedzie skladal sie tylko z jednego elementu;tablica wskaznikow bedzie posiadala tylko jeden element bedacy wskaznikiem na cale drzewo Huffmana

typedef struct  MinHeapNode { // element kopca do ktorego beda przekazywane dane z listy

    char data;
    size_t frequency;
    struct MinHeapNode* left, * right;

}MinHeapNode;

typedef struct MinHeap { // kopiec posiadajacy tablice wskaznikow na poszczegolne elementy kopca, kopiec poczatkowo zostanie zapelniony danymi z listy, a nastepnie posortowany, tak aby zachowac wlasnosc kopca
    size_t size;
    size_t capacity;
    struct MinHeapNode** array;

}MinHeap;


MinHeapNode* createMinHeapNode(Node* list1_var) { // tworzenie elementu kopca kopiujac dane z listy

    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(struct MinHeapNode));

    temp->left = NULL;
    temp->right = NULL;
    temp->data = list1_var->data;
    temp->frequency = list1_var->frequency;

    return temp;

}

MinHeap* createMinHeap(size_t capacity) { // tworzenie pustego kopca o zadanej pojemnosci i poczatkowym rozmiarze wynoszacym 0

    MinHeap* temp = (MinHeap*)malloc(sizeof(MinHeap));

    temp->size = 0;
    temp->capacity = capacity;
    temp->array = (MinHeapNode**)malloc(temp->capacity * sizeof(MinHeapNode*)); // alokowanie pamieci tablicy wskaznikow na poszczegolne elementy MinHeapNode

    return temp;
}

void swapMinHeapNode(MinHeapNode** x, MinHeapNode** y) { // przekazanie jako parametry adresow wskaznikow, w celu zamiany wartosci pod tymi adresami; funkcja wykorzystywana przy sortowaniu kopca

    MinHeapNode* temp = *x;
    *x = *y;
    *y = temp;

}

// funkcja przywracajaca wlasnosci kopca minimalnego
// jezeli wyliczony indeks lewego potomka jest mniejszy od rozmiaru kopca i lewy potemek jest mniejszy od poczatkowego rodzica, do indeksu rodzica jest przypisywany indeks lewego potomka
// analogicznie z prawym potomkiem
// jezeli doszlo do zmiany, zamieniane sa elementy kopca i rekurencyjnie proces jest powtarzany startujacac od nowo ustawionego indeksu parent
void minHeapify(MinHeap* _minHeap, size_t index) {

    size_t parent = index;
    size_t left_child = 2 * index + 1;
    size_t right_child = 2 * index + 2;


    if (left_child < _minHeap->size && _minHeap->array[left_child]->frequency < _minHeap->array[parent]->frequency)
        parent = left_child;
    if (right_child < _minHeap->size && _minHeap->array[right_child]->frequency < _minHeap->array[parent]->frequency)
        parent = right_child;
    if (parent != index) {

        swapMinHeapNode(&_minHeap->array[index], &_minHeap->array[parent]);
        minHeapify(_minHeap, parent);
    }
}

// funkcja wyciagajaca z kopca wierzcholek, wskaznik temp zapamietuje adres wierzcholka, wiercholek jest nadpisywany ostatnia wartoscia kopca
// rozmiar kopca jest zmniejszany(elementy nadal istnieja w tablicy, ale nie beda juz brane pod uwage)
// na koncu minHeapify przywraca wlasnosc kopca minimalnego
MinHeapNode* extractMinHeap(MinHeap* _minHeap) {

    MinHeapNode* temp = _minHeap->array[0];

    _minHeap->array[0] = _minHeap->array[_minHeap->size - 1];
    _minHeap->size--;// dotychczasowy ostatni element tablicy bedzie nieosiagalny, bo juz nie bedzie potrzebny
    minHeapify(_minHeap, 0);

    return temp;
}

// utworzenie kopca o pojemnosci rownej rozmiarowi listy, a nastepnie zapelnienie go elementami tej listy i naprawa kopca
MinHeap* SetUpMinHeap(Node* list1) {


    Node* current = list1;
    size_t capacity = getSize(current);
    MinHeap* _minHeap = createMinHeap(capacity);
    size_t last_index;

    for (int i = 0; i < capacity; i++) {

        _minHeap->array[i] = createMinHeapNode(current);
        current = current->next;
    }

    _minHeap->size = capacity; // zapelniono kopiec
    last_index = _minHeap->size - 1;

    for (int i = (last_index - 1) / 2; i >= 0; i--) { // przejscie po kazdym korzeniu i naprawa kopca

        minHeapify(_minHeap, i);
    }

    return _minHeap;
}

// drzewo Huffmana utworzone z elementow struktury MinHeapNode, ktore znajduja sie w MinHeap
MinHeapNode* HuffmanTree(MinHeap* _minHeap) {

    MinHeapNode* left_child, * right_child, * parent;
    size_t new_index;

    while (_minHeap->size != 1) {

        left_child = extractMinHeap(_minHeap);
        right_child = extractMinHeap(_minHeap);

        // tworzenie poddrzewa
        parent = (MinHeapNode*)malloc(sizeof(MinHeapNode));
        parent->data = '#';
        parent->frequency = left_child->frequency + right_child->frequency;
        parent->left = left_child;
        parent->right = right_child;

        // ponowne wstawienie utworzonego poddrzewa do kopca
        _minHeap->size++;
        new_index = _minHeap->size - 1;
        _minHeap->array[new_index] = parent;

        for (int i = (new_index - 1) / 2; i >= 0; i--) { // przejscie po kazdym korzeniu i naprawa kopca

            minHeapify(_minHeap, i);
        }
    }

    return extractMinHeap(_minHeap); // zwrocenie drzewa Huffmana
}

void freeTree(MinHeapNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);

    free(root);

}

void modify_file_name_extension1(char* str) {
    char* dot_ptr = strchr(str, '.');
    if (dot_ptr != NULL) {
        *dot_ptr = '\0';
        strcat_s(str, strlen(str) + 9, ".Huffman");
    }
}

void printModel(Node* head) {
    printf("\nModel informacyjny:\n");
    Node* current = head;
    while (current != NULL) {
        unsigned int variable = static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&current->data));
        variable &= 0x000000FF;
        printf("Byte: %c (0x%02X), Frequency: %zu\n", (current->data || isalnum(current->data) ? current->data : ' '), variable, current->frequency);
        current = current->next;
    }
    printf("\n------------------\n");
}

typedef struct HuffmanCode {

    unsigned char data; // znak
    int code[100]; // slowo kodowe
    int code_length; // dlugosc slowa kodowego
    struct HuffmanCode* next;

}HuffmanCode;

// tworzenie tabeli kodowej, wypisujac po kolei kod kazdego unikatowego znaku do pliku wyjsciowego
void HuffmanCodes(MinHeapNode* root, int buffer[], int index, HuffmanCode** head) {

    // lewe galezie oznaczone jako 0, prawe 1
    if (root->left) {
        buffer[index] = 0;
        HuffmanCodes(root->left, buffer, index + 1, head);
    }
    if (root->right) {
        buffer[index] = 1;
        HuffmanCodes(root->right, buffer, index + 1, head);
    }
    // po dotarciu do liscia wypisywanie danych do listy slow kodowych poszczegolnych znakow
    if (!(root->left) && !(root->right)) {
        
        // tworzenie nowego node'a pod slowo kodowe
        HuffmanCode* new_code = (HuffmanCode*)malloc(sizeof(HuffmanCode));
        new_code->data = root->data;
        new_code->code_length = index;
        new_code->next = NULL;
        
        for (int i = 0; i < new_code->code_length; i++) {
            new_code->code[i] = buffer[i];
        }
        // tworzenie listy
        if (*head == NULL) {
            *head = new_code;
        }
        else {
            new_code->next = *head;
            *head = new_code;
        }
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




void compressFile(char* argv[]) {
    
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
    long size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    input_string = (char*)malloc(size);
    fread_s(input_string, size, 1, size, input_file);

    fclose(input_file);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
   // zapełnienie listy kolejnymi znakami ciągu, lista przechowuje znaki i ich czestosci
    Node* head_list1 = NULL; // model informacyjny

    for (int i = 0; i < size; i++) {

        insertNode(&head_list1, input_string[i]);
    }

    MinHeap* _minHeap = SetUpMinHeap(head_list1);// utworzenie i zapelnienie kopca elementami z listy
    MinHeapNode* root = HuffmanTree(_minHeap); // stworzenie  drzewa
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    // wypisywanie do pliku wyjsciowego
    // zmiana rozszerzen
    modify_file_name_extension1(input_file_name);
    strcpy_s(output_file_name1, sizeof(output_file_name1), input_file_name);

    sortModel(&head_list1); // sortowanie modelu informacyjnego
    int code_buffer[256] = { 0 };
    int index = 0;
    
    HuffmanCode* head_list2 = NULL; // lista slow kodowych

    HuffmanCodes(root, code_buffer, index, &head_list2);  

    //############ KOMPRESJA ####################
    // Przygotowywanie ciagu do kompresji
    char* encode_string = NULL;
    char* info_string = NULL;
    char* pre_compress_string = NULL;
    HuffmanCode* code_iterator = head_list2; // iterator po liscie slow kodowych
    int flag = 1;
    bool check_first_occurance[256] = { false };
    
    char* encode_string1 = (char*)malloc(9 * sizeof(char)); // 8 bitow + null-terminator; string dla ilosci slow kodowych
    int codes_count = getSize(head_list1); // rozmiar modelu informacyjnego jest rowny ilosci slow kodowych
    for (int i = 7; i >= 0; i--) { // petla przedstawiajaca codes_count binarnie w postaci stringa
        encode_string1[7 - i] = ((codes_count >> i) & 1) + '0';
    }
    encode_string1[8] = '\0';
    
    for (int i = 0; i < size; i++) { // iteruje po input_stringu

        while (code_iterator) { // iteruje po liscie slow kodowych
            
            if ((unsigned char)(input_string[i]) == code_iterator->data) {
                
                // konwersja slowa kodowego na string

                int single_code_length = code_iterator->code_length; // dlugosc konkretnego slowa kodowego

                char* single_code = (char*)malloc((single_code_length + 1) * sizeof(char)); // string dla slowa kodowego w czesci kodujacej ciag wejsciowy
                for (int i = 0; i < single_code_length; i++) {
                    single_code[i] = code_iterator->code[i] + '0'; // '0' w celu przekazywania znakow ascii, 0 + '0' = '0', 1 + '0' = '1'
                }
                single_code[single_code_length] = '\0'; // utworzono string pojedynczego slowa kodowego

                
                // tworzenie encode stringa zawierajacy zakodowany ciag wejsciowy z pliku
                if (encode_string == NULL) {
                    encode_string = (char*)malloc((single_code_length + 1) * sizeof(char));
                    strcpy_s(encode_string, (single_code_length + 1) * sizeof(char), single_code); // single_code stanowi pierwszy czlon encode_string 
                }
                else {
                    size_t encode_string_length = strlen(encode_string);
                    encode_string = (char*)realloc(encode_string, (encode_string_length + single_code_length + 1) * sizeof(char)); 
                    strcat_s(encode_string, strlen(encode_string) + strlen(single_code) + 1, single_code);

                }

                // tworzenie podciagow info stringa zawierajacego informacje o ilosci slow kodowych oraz informacje o znakach i odpowiadajacym im slowom kodowym(przed informacja o slowie kodowym znaku jest rowniez podana dlugosc tego slowa kodowego)
                
                if (check_first_occurance[(unsigned char)(input_string[i])] == false) { // jesli jeden z 256 znakow sie juz pojawil, dalsza czesc kodu jest pomijana,poniewaz informacje o danych znakach maja sie pojawic tylko raz
                    check_first_occurance[(unsigned char)(input_string[i])] = true; // pojawienie sie znaku zostalo uwzglednione

                    char* encode_string2 = (char*)malloc(9 * sizeof(char));; // string dla znaku
                    for (int i = 7; i >= 0; i--) {
                        encode_string2[7 - i] = ((code_iterator->data >> i) & 1) + '0';
                    }
                    encode_string2[8] = '\0';

                    char* encode_string3 = (char*)malloc(9 * sizeof(char));; // string dla dlugosci slowa kodowego
                    for (int i = 7; i >= 0; i--) {
                        encode_string3[7 - i] = ((single_code_length >> i) & 1) + '0';
                    }
                    encode_string3[8] = '\0';

                    char* encode_string4 = (char*)malloc(sizeof(char) * (single_code_length + 1)); // string dla slowa kodowego w czesci informacyjnej
                    strcpy_s(encode_string4, sizeof(char) * (single_code_length + 1), single_code); // single_code stanowi czesc informacji w info_string

                    // laczenie w jeden podciag informacyjny, ktory dolaczam pozniej do info_string
                    size_t sub_info_string_length;
                    char* sub_info_string;

                    if (flag == 1) { // dla pierwszego przypadku ciag informacyjny sklada sie na poczatku z informacji o ilosci slow kodowych, w kolejnych iteracjach informacja ta nie musi sie juz powtarzac

                        sub_info_string_length = strlen(encode_string1) + strlen(encode_string2) + strlen(encode_string3) + strlen(encode_string4);
                        sub_info_string = (char*)malloc((sub_info_string_length + 1) * sizeof(char));
                        strcpy_s(sub_info_string, (sub_info_string_length + 1) * sizeof(char), encode_string1);
                        strcat_s(sub_info_string, (sub_info_string_length + 1) * sizeof(char), encode_string2);
                        strcat_s(sub_info_string, (sub_info_string_length + 1) * sizeof(char), encode_string3);
                        strcat_s(sub_info_string, (sub_info_string_length + 1) * sizeof(char), encode_string4);
                        flag = 0;
                    }
                    else {

                        sub_info_string_length = strlen(encode_string2) + strlen(encode_string3) + strlen(encode_string4);
                        sub_info_string = (char*)malloc((sub_info_string_length + 1) * sizeof(char));
                        strcpy_s(sub_info_string, (sub_info_string_length + 1) * sizeof(char), encode_string2);
                        strcat_s(sub_info_string, (sub_info_string_length + 1) * sizeof(char), encode_string3);
                        strcat_s(sub_info_string, (sub_info_string_length + 1) * sizeof(char), encode_string4);
                    }


                    // tworzenie info_stringa
                    if (info_string == NULL) {
                        info_string = (char*)malloc((sub_info_string_length + 1) * sizeof(char));
                        strcpy_s(info_string, (sub_info_string_length + 1) * sizeof(char), sub_info_string);
                    }
                    else {
                        size_t info_string_length = strlen(info_string);
                        info_string = (char*)realloc(info_string, (info_string_length + sub_info_string_length + 1) * sizeof(char));
                        strcat_s(info_string, strlen(info_string) + strlen(sub_info_string) + 1, sub_info_string);
                    }

                    free(encode_string2);
                    free(encode_string3);
                    free(encode_string4);
                    
                }
                free(single_code);
                break;
                
            }
            code_iterator = code_iterator->next;
        }
        code_iterator = head_list2; // po kazdym break powrot wskaznika na poczatek

    }
    free(encode_string1);
    
    int encoded_length = strlen(encode_string); // na dwoch bajtach
    char* string_encoded_length1 = (char*)malloc(9 * sizeof(char)); // lewy bajt
    char* string_encoded_length2 = (char*)malloc(9 * sizeof(char)); // prawy bajt
    
    for (int i = 7; i >= 0; i--) { // petla przedstawiajaca dlugosc zakodowanego ciagu binarnie jako string na dwoch bajtach(tak aby moc kompresowac wieksze pliki)
        string_encoded_length1[7 - i] = ((encoded_length >> (i+8)) & 1) + '0';
    }
    string_encoded_length1[8] = '\0'; 

    for (int i = 7; i >= 0; i--) { 
        string_encoded_length2[7 - i] = ((encoded_length >> i) & 1) + '0';
    }
    string_encoded_length2[8] = '\0';

    pre_compress_string = (char*)malloc((strlen(string_encoded_length1) + strlen(string_encoded_length2) + strlen(info_string) + strlen(encode_string) + 1) * sizeof(char));
    strcpy_s(pre_compress_string, (strlen(string_encoded_length1) + strlen(string_encoded_length2) + strlen(info_string) + strlen(encode_string) + 1), string_encoded_length1);
    strcat_s(pre_compress_string, (strlen(string_encoded_length1) + strlen(string_encoded_length2) + strlen(info_string) + strlen(encode_string) + 1), string_encoded_length2);
    strcat_s(pre_compress_string, (strlen(string_encoded_length1) + strlen(string_encoded_length2) + strlen(info_string) + strlen(encode_string) + 1), info_string);
    strcat_s(pre_compress_string, (strlen(string_encoded_length1) + strlen(string_encoded_length2) + strlen(info_string) + strlen(encode_string) + 1), encode_string);
    printf("Ciag przed kompresja: \n%s", pre_compress_string);
    
    // plik wyjsciowy .Huffman
    err = fopen_s(&output_file1, output_file_name1, "wb");
    if (err != 0) {
        printf("Nie udalo sie utworzyc/otworzyc pliku wyjsciowego  %s\n", output_file_name1);
        return;
    }

    // na tak utworzonym stringu dokonuje podzialu po 8 bitow, kazde kolejne 8 znakow(bajtow) stringa reprezentujacych bity zapisuje jako jeden bajt i wpisuje do pliku
    unsigned char _buffer = 0;
    int _buffer_index = 0;
    int j;
    for (j = 0; j < strlen(pre_compress_string); j++) {

        unsigned char bit = pre_compress_string[j];
        bit = bit - 48; // '0' = 48 , '1' = 49
        _buffer = _buffer << 1;
        _buffer |= bit; // wstawianie kolejnych cyfr do bajta
        _buffer_index++;

        if (_buffer_index == 8) { // gdy bajt sie zapelni, wysylany jest do pliku
            fwrite(&_buffer, sizeof(_buffer), 1, output_file1);
            printf("\nBuffer nr.%d: (0x%02X)", (j+1)/8, _buffer);
            _buffer = 0;
            _buffer_index = 0;
        }
    }
    
    // przypadek gdy bajt sie nie zapelni
    if (_buffer_index > 0) {
        _buffer = _buffer << (8 - _buffer_index); // przesuwanie o tyle miejsc, ile zostalo niezapelnionych
        fwrite(&_buffer, sizeof(_buffer), 1, output_file1);
        printf("\nBuffer dopelniony: (0x%02X)\n", _buffer);
        printf("\nRozmiar przed kompresja: %d\n", size);
        printf("Rozmiar po kompresji: %d\n", ((j + 1) / 8) + 1);
    }
    else {
        printf("\nRozmiar przed kompresja: %d\n", size);
        printf("Rozmiar po kompresji: %d\n", ((j + 1) / 8));
    }


    fclose(output_file1);
    
    
    printModel(head_list1);
    printCodess(head_list2);
    
    freeList(&head_list1);
    freeTree(root);
    root = NULL;
    free(_minHeap);
    _minHeap = NULL;
    free(encode_string);
    free(info_string);
    free(pre_compress_string);

}

int main(int argc, char* argv[]) {
    
    

    if (argc != 2) {
        printf("Poprawna forma: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }
    
    compressFile(argv);

    

    
    return 0;
}


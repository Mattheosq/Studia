#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
// WCY21IY4S1 Mateusz Grabowski Zad5
void generuj_element(int tab[],int n){
    for(int i=0;i<n;i++){
        int random = rand();
        tab[i] = random;
        std::cout << tab[i] << std::endl;
    }
}

int max_f(int tab[], int n){
    int max = tab[0];
    for(int i=1;i<n;i++){
        if(max<tab[i]){
            max = tab[i];
        }
    }
    return max;
}

int min_f(int tab[], int n){
    int min = tab[0];
        for(int i=1;i<n;i++){
            if(min>tab[i]){
                min = tab[i];
            }
        }
    return min;
}

int main(){
    size_t size;
    srand(time(NULL));   
	 
    std::cout << "Podaj rozmiar tablicy: " << std::endl;
    std::cin >> size;
    int* ptr_tab = new int[size];
    std::cout << "Tablica: " << std::endl;
    generuj_element(ptr_tab,size);
    std::cout << "Max element = " << max_f(ptr_tab,size) << " Min element = " << min_f(ptr_tab,size);

	delete [] ptr_tab;
    return 0;
}

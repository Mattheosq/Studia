#include <iostream>

// WCY21IY4S1 Mateusz Grabowski Zad1

int silnia_rekurencja(int n){
    if(n==1){
        return 1;
    }
    else
        return n*silnia_rekurencja(n-1);
}

int silnia_iteracja(int n){
    int wynik = 1;
    int stala = n;
    
    for(int i=0;i<stala;i++){
        wynik = wynik*n;
        n--;
    }
    return wynik;
    
    
}


int main(int argc, char** argv) {
    
    int n;
    std::cout << "Podaj wartosc dla n: " << std::endl;
    std::cin >> n;
    
    std::cout << "REKURENCJA: n!= " << silnia_rekurencja(n) << std::endl;
    std::cout << "ITERACJA: n!= " << silnia_iteracja(n) << std::endl;
    return 0;
}

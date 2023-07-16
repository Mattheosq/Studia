#include <iostream>
//WCY21IY4S1 Mateusz Grabowski Zad3

int horner_i(int wspolczynniki[], int stopien, int x){
    int wynik = wspolczynniki[0];
    
    for(int i=1;i<=stopien;i++){
        wynik= x*wynik + wspolczynniki[i];
        
    }
    return wynik;
    
}

int horner_r(int wspolczynniki[], int stopien, int x){
    if(stopien==0){
        return wspolczynniki[0];
    }
    else
        return x*horner_r(wspolczynniki,stopien-1,x) + wspolczynniki[stopien];
}

int main(int argc, char** argv) {
    int *wspolczynniki;
    int stopien, argument;
    
    std::cout << "Podaj stopien wielomianu" << std::endl;
    std::cin >> stopien;
    
    wspolczynniki = new int [stopien+1];
    for(int i=0;i<=stopien;i++){
        std::cout << "Podaj wspolczynnik stojacy przy" << stopien-i << " stopniu" << std::endl;
        std::cin >> wspolczynniki[i];
    }
    std::cout << "Podaj argument" << std::endl;
    std::cin >> argument;
    
    std::cout << "REKURENCJA: Wynik = " << horner_r(wspolczynniki,stopien,argument) << std::endl;
    std::cout << "ITERACJA: Wynik = " << horner_i(wspolczynniki,stopien,argument) << std::endl;
    
    delete [] wspolczynniki;
    return 0;
}

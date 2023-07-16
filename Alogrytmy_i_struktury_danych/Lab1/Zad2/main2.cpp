#include <iostream>

//WCY21IY4S1 Grabowski Mateusz Zad2

void fibonacci_iteracja(int n){
    
    int a=0;
    int b=1;
    for(int i=0;i<n;i++){
        std::cout << b << std::endl;
        b+=a;
        a=b-a;
    } 
}

int fibonacci_rekurencja(int n){
    if(n<=2){
        return 1;
    }
    else{
            
            return fibonacci_rekurencja(n-2)+fibonacci_rekurencja(n-1);
    } 
    
}

int main(int argc, char** argv) {
    
    int n;
    
    std::cout << "Podaj ilosc wyrazow ciagu: " << std::endl;
    std::cin >> n;
    
    std::cout << "ITERACJA: Wynik= ";
    fibonacci_iteracja(n);
    std::cout << std::endl;
    std::cout << "REKURENCJA: Wynik= ";
    for(int i=1;i<n+1;i++){
        std::cout << fibonacci_rekurencja(i) << std::endl;
    
    }
    return 0;
}

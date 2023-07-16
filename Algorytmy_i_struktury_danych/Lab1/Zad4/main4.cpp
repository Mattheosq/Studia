#include <iostream>
#include <iomanip>
// WCY21IY4S1 Mateusz Grabowski Zad4
int main(){

    int n,m,k;
    int** A;
    int** B;
    int** C; 

    std::cout << "Mnozenie macierzy o rozmiarach NxM i MxK" << std::endl;
    std::cout << "Podaj kolejno wartosci dla N, M i K: ";
    std::cin >> n >> m >> k;
    std::cout << std::endl;

    A = new int* [n];
    B = new int* [m];
    C = new int* [n];
    // tworzenie rozmiarow
    for(int i=0;i<n;i++)
        A[i] = new int [m];
    for(int i=0;i<m;i++)
        B[i] = new int [k];
    for(int i=0;i<n;i++)
        C[i] = new int [k];
    
    // uzupelnienie macierzy A
    std::cout << "Macierz A" << std::endl;
    for(int i=0;i<n;i++){
        std::cout << i << " wiersz" << std::endl;
        for(int j=0;j<m;j++){
            std::cin >> A[i][j];
        }
    }
    // uzupelnienie macierzy B
    std::cout << "Macierz B" << std::endl;
    for(int i=0;i<m;i++){
        std::cout << i << " wiersz" << std::endl;
        for(int j=0;j<k;j++){
            std::cin >> B[i][j];
        }
    }
    // mnozenie macierzy

    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            int wynik = 0;
            for(int q=0;q<m;q++){
                wynik += A[i][q] * B[q][j];
            }
            C[i][j] = wynik;
        }
    }

    // wynik

    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            std::cout << std::setw(5) << C[i][j];
        }
        std::cout << std::endl;
    }
    //czyszczenie pamieci
    for(int i=0;i<n;i++){
        delete [] A[i];
        delete [] C[i];
    }
    for(int i=0;i<m;i++){
        delete [] B[i];
    }
    
    delete [] A;
    delete [] B;
    delete [] C;


    return 0;
}
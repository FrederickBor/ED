#include <iostream>
#include "../TADs/pila.h"

using namespace std;

void imprimir(Pila<int>& p, int length){

    int suma = 0;

    while (!p.esVacia()){
        cout << p.cima();
        suma += p.cima();
        p.desapila();
        length--;
        if (length == 0){
            cout << " = ";
        } 
        else{
            cout << " + ";
        }
    }

    cout << suma << endl;
    
}

void llenarPila(int n, Pila<int>& p, int& length){
    while (n > 9){
        p.apila(n % 10);
        n = n / 10;
        length++;
    }

    p.apila(n);
    length++;
}

int main(){

    int n, length;
    Pila<int> p;
    
    cout << "\n\n--- EJ 1: IMPRIMIR UN NUMERO EN ORDEN LEXICOGRAFICO Y MOSTRAR SU RESULTADO ---\n";
    
    n = 64323;
    length = 0;
    cout << "\nCon n = " << n << ". Resulta:\n";
    llenarPila(n, p, length);
    imprimir(p, length);
    cout << endl;

    n = 123456789;
    length = 0;
    cout << "\nCon n = " << n << ". Resulta:\n";
    llenarPila(n, p, length);
    imprimir(p, length);
    cout << endl;

    n = 951;
    length = 0;
    cout << "\nCon n = " << n << ". Resulta:\n";
    llenarPila(n, p, length);
    imprimir(p, length);
    cout << endl;

    n = 4268;
    length = 0;
    cout << "\nCon n = " << n << ". Resulta:\n";
    llenarPila(n, p, length);
    imprimir(p, length);
    cout << endl;

    n = 79130;
    length = 0;
    cout << "\nCon n = " << n << ". Resulta:\n";
    llenarPila(n, p, length);
    imprimir(p, length);
    cout << endl;

    return 0;
}
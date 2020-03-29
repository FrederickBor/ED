#include <iostream>
#include <string>
#include "pila.h"
using namespace std;

void impAbajoArribaRecursivo(Pila<int> p){
    if (p.esVacia()) return;

    int n = p.cima();
    p.desapila();
    impAbajoArribaRecursivo(p);
    cout << n << " ";
}

void impAbajoArribaIterativo(Pila<int> p){
    Pila<int> aux;
    
    while (!p.esVacia()){
        aux.apila(p.cima());
        p.desapila();
    }

    while (!aux.esVacia()){
        cout << aux.cima() << " ";
        aux.desapila();
    }
}

int main()
{
	Pila<int> p;
    p.apila(0);
    p.apila(1);
    p.apila(2);
    p.apila(3);
    p.apila(4);
    p.apila(5);
    p.apila(6);
    p.apila(7);
    p.apila(8);
    p.apila(9);

	cout << "\n\n--- EJ 5: IMPRIMIR UNA PILA DE ABAJO HACIA ARRIBA ---\n";
    cout << "\n RECURSIVO:\n";
    impAbajoArribaRecursivo(p);
    cout << "\n\n ITERATIVO:\n";
    impAbajoArribaIterativo(p);
    cout << "\n\n TAD:\n";
    p.impAbajoArriba();
    cout << endl;
    
	return 0;
}
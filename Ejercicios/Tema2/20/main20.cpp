#include <iostream>
#include "pinta.h"

using namespace std;

int main(){
	// listas para las pruebas
	Lista<int> listaVacia, lista1;
		
	for (int i = 1; i <= 5; i++)
		lista1.pon_final(i);	

	cout << "\n\n--- EJ 20: USO DE PROCEDIMIENTOS GENERICOS PARA MOSTRAR UNA LISTA ---\n";
	cout << "Lista vacia\n";
	pinta(listaVacia);
	cout << endl;
	cout << "Lista lista1\n";
	pinta(lista1);
	cout << endl;

	return 0;
}
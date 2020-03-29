#include <iostream>
#include "quitaPares.h"

using namespace std;

// EJERCICIO 20
// procedimiento genérico que muestra por pantalla una lista (asume elementos imprimibles)
template <class T>
void pinta(const Lista<T>& lista) {
	typename Lista<T>::ConstIterator it = lista.cbegin();  
	while (it != lista.cend()) {
		cout << it.elem() << endl;
		it.next();
	}
}

int main(){
	// listas para las pruebas
	Lista<int> listaVacia, lista1, lista2;

	for (int i = 1; i <= 6; i++) 
		for (int repeticiones = 1; repeticiones <=2; repeticiones++)
			lista1.pon_final(i);
		
	for (int i = 2; i <= 6; i = i + 2)
		lista2.pon_ppio(i);

	cout << "\n\n--- EJ25: uso de ELIMINAR para ELIMINAR LOS PARES DE lista ---\n";

	cout << "Cuando elimino los numeros pares de la lista vacia resulta\n";
	quitaPares(listaVacia);
	pinta(listaVacia);
	cout << endl;

	cout << "Cuando elimino los numeros pares de la lista\n";
	pinta(lista1);
	cout << "Resulta\n";
	quitaPares(lista1);
	pinta(lista1);
	cout << endl;

	cout << "Cuando elimino los numeros pares de la lista\n";
	pinta(lista2);
	cout << "Resulta\n";
	quitaPares(lista2);
	pinta(lista2);
	cout << endl;

	return 0;
}
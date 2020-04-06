#include <iostream>
#include "repiteElementos.h"

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
	Lista<int> listaVacia, lista1;
		
	for (int i = 1; i <= 5; i++)
		lista1.pon_final(i);

	cout << "\n\n--- EJ23: uso de REPITEELEMENTOS para DUPLICAR LOS ELEMENTOS DE lista ---\n";
	cout << "Cuando repito la lista vacia\n";
	pinta(listaVacia);
	cout << endl;
	cout << "Resulta\n";
	repiteElementos(listaVacia);
	pinta(listaVacia);
	cout << endl;
	cout << "Cuando repito la lista\n";
	pinta(lista1);
	cout << "Resulta\n";
	repiteElementos(lista1);
	pinta(lista1);
	cout << endl;

	return 0;
}
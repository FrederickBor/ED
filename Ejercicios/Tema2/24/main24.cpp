#include <iostream>
#include "mezclar.h"

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
	Lista<int> listaVacia, lo1, lo2;

	for (int i = 1; i < 10; i = i + 2)
		lo1.pon_final(i);

	for (int i = 0; i <= 10; i = i + 2)
		lo2.pon_final(i);

	cout << "\n\n--- EJ24: uso de MEZCLAR para MEZCLAR DOS LISTAS ORDENADAS ---\n";
	
	cout << "Cuando mezclo dos listas vacias resulta\n";
	pinta(mezclar(listaVacia, listaVacia));
	cout << endl;

	cout << "Cuando mezclo la lista vacia con \n";
	pinta(lo1);
	cout << "Resulta\n";
	pinta(mezclar(listaVacia, lo1));

	cout << "Cuando mezclo\n";
	pinta(lo1);
	cout << "con la lista vacia resulta\n";
	pinta(mezclar(lo1, listaVacia));

	cout << "Cuando mezclo\n";
	pinta(lo1);
	cout << "con\n";
	pinta(lo2);
	cout << "Resulta\n";
	pinta(mezclar(lo1, lo2));

	cout << "Cuando mezclo\n";
	pinta(lo2);
	cout << "con\n";
	pinta(lo1);
	cout << "Resulta\n";
	pinta(mezclar(lo2, lo1));

	return 0;
}
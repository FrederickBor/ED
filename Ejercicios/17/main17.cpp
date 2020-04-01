#include <iostream>
using namespace std;
#include "lista.h"

// EJERCICIO 20
// procedimiento genérico que muestra por pantalla una lista (asume elementos imprimibles)
template <class T>
void pinta(const Lista<T>& lista) {
	if (lista.esVacia()) return;
	typename Lista<T>::ConstIterator it = lista.cbegin();  
	while (it != lista.cend()) {
		cout << it.elem() << endl;
		it.next();
	}
}


int main() {
		
	Lista<int> l1, l2;

	cout << "Resultado de concatenar dos listas vacias\n";
	l1.concatenaConst(l2);
	pinta(l1);
	cout << endl << endl;


	for (int i = 1; i <= 5; i++)
		l1.pon_ppio(i);
	
	cout << "Al concatenar la lista...\n";
	pinta(l1);
	l1.concatenaConst(l2);
	cout << "con una lista vacia resulta...\n";
	pinta(l1);
	cout << endl;

	cout << "Al concatenar la lista vacia con la lista\n";
	pinta(l1);
	l2.concatenaConst(l1);
	cout << "resulta...\n";
	pinta(l2);

	cout << "Al concatenar la lista...\n";
	pinta(l1);
	cout << "con la lista...\n";
	l2.quita_ppio();
	cout << "quita ppio...\n";
	l2.quita_final();
	cout << "quita final...\n";
	pinta(l2);
	l1.concatenaConst(l2);
	cout << "resulta...\n";
	pinta(l1);
	cout << endl;

	return 0;
}


#include <iostream>
#include "../TADs/lista.h"

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
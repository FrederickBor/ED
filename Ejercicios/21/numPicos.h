#include "../TADs/lista.h"

// EJERCICIO 21
// Implementa un subprograma que reciba una lista de enteros 
// y cuente cuántas posiciones hay en ella tales que el elemento que hay 
// en esa posición es igual a la suma de todos sus precedentes 
int numPicos(const Lista<int>& lista){
	int suma = 0;
	int cont = 0;
	Lista<int>::ConstIterator it = lista.cbegin();  
	while (it != lista.cend()) {
		if (it.elem() == suma)
			cont++;
		suma += it.elem();
		it.next();
	}

	return cont;
}
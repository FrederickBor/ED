#include "../TADs/lista.h"

// EJERCICIO 25
// subprograma que elimina los números pares de una lista de enteros
void quitaPares(Lista<int>& lista) {
	Lista<int>::Iterator it = lista.begin();  
	while (it != lista.end()) {
		if (it.elem() % 2 == 0)
			it = lista.eliminar(it);
		else
			it.next();
	}
}
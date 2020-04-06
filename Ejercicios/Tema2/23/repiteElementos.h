#include "../../TADs/lista.h"

// EJERCICIO 23
// función que duplica los elementos de una lista de enteros
// si la lista es [1,2,3] la transforma en [1,1,2,2,3,3] 
void repiteElementos (Lista<int> &lista) {
	Lista<int>::Iterator it = lista.begin();  
	while (it != lista.end()) {
		lista.insertar(it.elem(),it);
		it.next();
	}
}
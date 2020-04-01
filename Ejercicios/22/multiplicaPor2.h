#include "../TADs/lista.h"

// EJERICIO 22
// Implementa  un  subprograma  que  reciba  una  lista  de 
// enteros  y  multiplique  por  dos todos sus elementos.
void multiplicaPor2(Lista<int> &lista){
	Lista<int>::Iterator it = lista.begin();  
	while (it != lista.end()) {
		it.set(it.elem()*2);
		it.next();
	}
}
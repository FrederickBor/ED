#include "../../TADs/lista.h"

// EJERCICIO 24
// subprograma que reciba dos listas de enteros ordenados crecientemente 
// y devuelva una nueva lista ordenada con la unión de los enteros de las 
// dos listas iniciales
Lista<int> mezclar(const Lista<int>& l1, const Lista<int>& l2){
	Lista<int> lista;

	Lista<int>::ConstIterator it1 = l1.cbegin();  
	Lista<int>::ConstIterator it2 = l2.cbegin();  

	while ((it1 != l1.cend()) && (it2 != l2.cend())) {
		if (it1.elem() < it2.elem()){
			lista.pon_final(it1.elem());
			it1.next();
		}
		else{
			lista.pon_final(it2.elem());
			it2.next();
		}
	}

	while (it1 != l1.cend()){
		lista.pon_final(it1.elem());
		it1.next();
	}

	while (it2 != l2.cend()){
		lista.pon_final(it2.elem());
		it2.next();
	}
	
	return lista;
}
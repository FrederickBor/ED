#include <iostream>
#include "numPicos.h"

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
		
	for (int i = 1; i <= 5; i++)
		lista1.pon_final(i);

	for (int i = 1; i <= 5; i++)
		lista2.pon_ppio(i);

	Lista<int> listapicos;
	listapicos.pon_final(1);
	listapicos.pon_final(2);
	listapicos.pon_final(3);
	listapicos.pon_final(6);
	listapicos.pon_final(10);
	listapicos.pon_final(22);

	std::cout << "\n\n--- EJ 21: USO DE NUMPICOS PARA CONTAR EL NUMERO DE PICOS DE UNA LISTA ---\n";
	cout << "La lista vacia tiene " << numPicos(listaVacia) << " pico(s)\n";
	cout << "La lista \n";
	pinta(lista1);
	cout << "Tiene " << numPicos(lista1) << " pico(s)\n";
	cout << "La lista \n";
	pinta(lista2);
	cout << "Tiene " << numPicos(lista2) << " pico(s)\n";
	cout << "La lista \n";
	pinta(listapicos);
	cout << "Tiene " << numPicos(listapicos) << " pico(s)\n";
	cout << endl;

	return 0;
}
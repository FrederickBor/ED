#include <iostream>
using namespace std;
#include "lista.h"


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


int main() {
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
	

	cout << "\n\n--- EJ 20: USO DE PROCEDIMIENTOS GENERICOS PARA MOSTRAR UNA LISTA ---\n";
	cout << "Lista vacia\n";
	pinta(listaVacia);
	cout << endl;
	cout << "Lista lista1\n";
	pinta(lista1);
	cout << endl;

	cout << "\n\n--- EJ 21: USO DE NUMPICOS PARA CONTAR EL NUMERO DE PICOS DE UNA LISTA ---\n";
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


	system("PAUSE");
	return 0;
}
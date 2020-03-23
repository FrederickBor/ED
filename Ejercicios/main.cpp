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

	if (it1 == l1.cend()){
		while (it2 != l2.cend()){
			lista.pon_final(it2.elem());
			it2.next();
		}
	}
	else{
		while (it1 != l1.cend()){
			lista.pon_final(it1.elem());
			it1.next();
		}
	}

	return lista;
}


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

void mainEj21y23(){
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
}

void mainEj24y25(){
	// listas para las pruebas
	Lista<int> listaVacia, lista1, lista2, lo1, lo2;

	for (int i = 1; i <= 6; i++) 
		for (int repeticiones = 1; repeticiones <=2; repeticiones++)
			lista1.pon_final(i);
		
	for (int i = 2; i <= 6; i = i + 2)
		lista2.pon_ppio(i);

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

	cout << "\n\n--- EJ25: uso de ELIMINAR para ELIMINAR LOS PARES DE lista ---\n";

	cout << "Cuando elimino los numeros pares de la lista vacia resulta\n";
	quitaPares(listaVacia);
	pinta(listaVacia);
	cout << endl;

	cout << "Cuando elimino los numeros pares de la lista\n";
	pinta(lista1);
	cout << "Resulta\n";
	quitaPares(lista1);
	pinta(lista1);
	cout << endl;

	cout << "Cuando elimino los numeros pares de la lista\n";
	pinta(lista2);
	cout << "Resulta\n";
	quitaPares(lista2);
	pinta(lista2);
	cout << endl;
}


int main() {
	
	mainEj21y23();
	mainEj24y25();
	
	return 0;
}
#include "Arbin.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Implementar aqu� la funciones auxiliares que se consideren necesarias

bool es_hoja(Arbin<int> a){
	return (!a.esVacio() && a.hijoDer().esVacio() && a.hijoIz().esVacio());
}

bool es_zurdo_aux(Arbin<int> a, int& altura, int& suma){
	if (es_hoja(a)){
		suma = a.raiz();
		altura = 1;
		return true;
	}

	int sumaIzq, 
		sumaDer,
		alturaIzq,
		alturaDer;

	es_zurdo_aux(a.hijoIz(), alturaIzq, sumaIzq);
	es_zurdo_aux(a.hijoDer(), alturaDer, sumaDer);

	altura = max(alturaIzq, altura) + 1;
	suma = sumaDer + sumaIzq + a.raiz();
	
	return sumaIzq - sumaDer >= altura - 1;
}

// Funci�n principal a implementar, que determina si
// el �rbol dado como entrada es o no zurdo (devuelve true si es
// zurdo, false en otro caso)
bool es_zurdo(Arbin<int> a) {
	// A implementar
	if (a.esVacio()) return false;
	
	int altura = 1;
	int suma = 0;
	return es_zurdo_aux(a, altura, suma);
}


//-----------------------------------------------------------------------
// C�digo que se encarga de la e/s: no tocar
//

Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}


/**
La entrada al programa consiste de l�neas formadas por �rboles de enteros
codificados de acuerdo con las siguientes reglas:
(1) El �rbol vac�o se codifica como #
(2) Los �rboles simples se codifican como [v], con
	v el valor del nodo
(3) Los �rboles complejos se codifican como (IvD),
	con I la codificaci�n del hijo izquierdo,
	v el valor de la ra�z, y D la codificaci�n
	del hijo derecho.
Para cada l�nea leida, escribe en la salida est�dar
ZURDO si el �rbol es zurdo, y NO_ZURDO en otro caso

Ejemplo de entrada:
#
[5]
([17]5([2]1[3]))
(([2]1[3])5[17])

Salida asociada:
NO_ZURDO
ZURDO
ZURDO
NO_ZURDO


*/

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		string resto_linea;
		getline(cin, resto_linea);
		if (es_zurdo(a)) cout << "ZURDO";
		else cout << "NO_ZURDO";
		cout << endl;
	}
	return 0;
}
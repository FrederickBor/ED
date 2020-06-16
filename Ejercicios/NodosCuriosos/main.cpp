
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

bool es_hoja(const Arbin<int>& a){
	return !a.esVacio() &&
			a.hijoDer().esVacio() &&
			a.hijoIz().esVacio();
}

int nodos_curiosos_aux(const Arbin<int> a, int nivel, int& nodos){	
	if (a.esVacio()){
		nodos = 0;
		return 0;
	}

	if (es_hoja(a)){
		nodos = 1;
		return 0;
	}

	int nodosIzq = 0,
		nodosDer = 0,
		nodosCuriososIzq = 0,
		nodosCuriososDer = 0;
	
	nodosCuriososIzq = nodos_curiosos_aux(a.hijoIz(), nivel + 1, nodosIzq);
	nodosCuriososDer = nodos_curiosos_aux(a.hijoDer(), nivel + 1, nodosDer);

	nodos = nodosIzq + nodosDer + 1;
	return nodosCuriososIzq + nodosCuriososDer + (nodosIzq + nivel == a.raiz());

}

/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   ***A COMPLETAR***
			   
			   Implementar esta operación tiene coste O(n) 
			   donde n es el numero de nodos del arbol.
			  
*/
int nodos_curiosos(const Arbin<int>& a) {
	int nodos = 0;
	return nodos_curiosos_aux(a, 1, nodos);
}

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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		cout << nodos_curiosos(lee_arbol(cin)) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}

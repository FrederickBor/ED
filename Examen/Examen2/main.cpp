/* 
	ALUMNO: FREDERICK ERNESTO BORGES NORONHA
	NIE: Y6217614S
*/
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

bool es_hoja(const Arbin<int>& a){
	return !a.esVacio() &&
			a.hijoDer().esVacio() &&
			a.hijoIz().esVacio();
}

unsigned int numeros_neutros_aux(const Arbin<int>& a, int& nodos){
	if (a.esVacio()){
		nodos = 0;
		return 0;
	}

	if (es_hoja(a)){
		nodos = a.raiz() > 0;
		return 1;
	}

	int nodosIz = 0, nodosDer = 0, neutrosIz = 0, neutrosDer = 0;

	neutrosIz = numeros_neutros_aux(a.hijoIz(), nodosIz);
	neutrosDer = numeros_neutros_aux(a.hijoDer(), nodosDer);

	nodos = nodosDer + nodosIz + (a.raiz() > 0);

	return neutrosDer + neutrosIz + (nodosDer == nodosIz);
}

/** Indica aqu�, razonadamente, la complejidad de numero_neutros
 * La complejida es O(n) ya que solo se recorren los nodos una sola vez.
*/

unsigned int numero_neutros(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int nodos = 0;
	return numeros_neutros_aux(a, nodos);
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
		Arbin<int> a = lee_arbol(cin);
		cout << numero_neutros(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}

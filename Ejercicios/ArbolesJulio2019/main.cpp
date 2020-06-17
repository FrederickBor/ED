#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;



/*
 COMPLEJIDAD: Justifica la complejidad de tu
algoritmo. 
 
 Coste lineal ya que se recorre una vez cada nodo
*/
bool es_hoja(const Arbin<int>& a){
	return !a.esVacio() &&
			a.hijoDer().esVacio() &&
			a.hijoIz().esVacio();
}

unsigned int numNodosSumativos_aux (const Arbin<int>& a, int& sumaDesc){
	if (a.esVacio()){
		sumaDesc = 0;
		return 0;
	}

	if (es_hoja(a)){
		sumaDesc = a.raiz();
		return 0;
	}

	int sumaDescIz = 0,
		sumaDescDer = 0,
		sumativosIz,
		sumativosDer;

	sumativosDer = numNodosSumativos_aux(a.hijoDer(), sumaDescDer);
	sumativosIz = numNodosSumativos_aux(a.hijoIz(), sumaDescIz);

	sumaDesc = a.raiz() + sumaDescIz + sumaDescDer;
	return sumativosDer + sumativosIz + (a.raiz() == (sumaDescDer + sumaDescIz));
}

unsigned int numNodosSumativos (const Arbin<int>& a) {
	/* A IMPLEMENTAR */
	int sumaDesc = 0;
	return numNodosSumativos_aux(a, sumaDesc);
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
		unsigned int resultado = numNodosSumativos(a);
		cout << resultado << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}
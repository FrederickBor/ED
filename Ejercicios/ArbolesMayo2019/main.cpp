#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;



/* Puedes implementar aquí las funciones auxiliares que consideres
   oportuno */

/*
COMPLEJIDAD: Determina justificadamente la complejidad del procedimiento 
Coste lineal.
*/
bool es_hoja(const Arbin<int>& a){
	return !a.esVacio() &&
			a.hijoDer().esVacio() &&
			a.hijoIz().esVacio();
}

void mejor_renta_aux(Arbin<int> a, bool& es_rentable, int& renta_maxima, int sumaAnt){
	if (a.esVacio()){
		renta_maxima = max(renta_maxima, 0);
		es_rentable = true;
		return;
	}

	if (es_hoja(a)){
		renta_maxima = max(renta_maxima, sumaAnt + a.raiz());
		es_rentable &= (sumaAnt + a.raiz() > 0);
		return;
	}

	bool rentableIz = true, rentableDer = true;
	int rentaIz = 0, rentaDer = 0;
	
	if (es_rentable && (sumaAnt + a.raiz() > 0)) {
		mejor_renta_aux(a.hijoDer(), rentableDer, rentaDer, sumaAnt + a.raiz());
		mejor_renta_aux(a.hijoIz(), rentableIz, rentaIz, sumaAnt + a.raiz());

		es_rentable &= rentableIz && rentableDer;
		renta_maxima = max(rentaIz, rentaDer);
	}
	return;
}

void mejor_renta(Arbin<int> a, bool& es_rentable, int& renta_maxima) {
	/* A IMPLEMENTAR */
	if (a.esVacio()) return;
	es_rentable = true;
	renta_maxima = 0;
	mejor_renta_aux(a,es_rentable,renta_maxima, 0);	
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

void muestra_solucion(bool rentable, int renta_max) {
  if (rentable) {
	 cout << renta_max << endl; 
  }	
  else {
	 cout << "NO_RENTABLE " << endl; 
  }
}

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		bool es_rentable;
		int renta_maxima;
		mejor_renta(a,es_rentable,renta_maxima);
		muestra_solucion(es_rentable,renta_maxima);
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}
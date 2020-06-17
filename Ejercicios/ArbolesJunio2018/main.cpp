#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/**
  FUNCION A IMPLEMENTAR.
  Aparte de esta función, puedes implementar todas las funciones auxiliares que
  consideres oportuno. 
  Debes describir y justificar aquí la complejidad de la implementación realizada:
  
  Coste lineal.

*/
bool es_hoja(const Arbin<char>& a){
	return !a.esVacio() &&
			a.hijoDer().esVacio() &&
			a.hijoIz().esVacio();
}

int num_a_salvo_aux(const Arbin<char>& a, int& caballeros, int monstruos){
	if (a.esVacio()){
		caballeros = 0;
		return 0;
	}
	
	if (es_hoja(a)){
		caballeros = (a.raiz() == 'C');
		return (a.raiz() == 'D') && (monstruos <= caballeros);
	}

	monstruos += (a.raiz() == 'M');

	int numASalvoDer = 0,
		numASalvoIz = 0, 
		caballerosIz = 0, 
		caballerosDer = 0;

	numASalvoDer = num_a_salvo_aux(a.hijoDer(), caballerosDer, monstruos);
	numASalvoIz = num_a_salvo_aux(a.hijoIz(), caballerosIz, monstruos);

	caballeros = caballerosIz + caballerosDer + (a.raiz() == 'C');

	return numASalvoDer + numASalvoIz + ((a.raiz() == 'D') && (monstruos <= caballerosIz + caballerosDer));

}

int num_a_salvo(const Arbin<char>& a) {
	/*** A IMPLEMENTAR ***/
	int caballeros = 0;
	return num_a_salvo_aux(a, caballeros, 0);
}



Arbin<char> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
  		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = lee_arbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = lee_arbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}


void escribe_arbol(Arbin<char> a) {
	if (a.esVacio()) cout << "#";
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) cout << "[" << a.raiz() << "]";
	else {
		cout << "("; 
		escribe_arbol(a.hijoIz()); 
		cout << a.raiz(); 
		escribe_arbol(a.hijoDer());
		cout << ")";
	}
}


int main() {
	Arbin<char> arbol;
	while (cin.peek() != EOF)  {
		Arbin<char> mapa = lee_arbol(cin);
		cout << "num_a_salvo ";
		escribe_arbol(mapa);
		cout << " => ";
		cout << num_a_salvo(mapa);
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}

#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool esHoja(const Arbin<char>& a){
	return a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

void tiempoAyudaAux(const Arbin<char>& falda, int horas, int& horasAcum){
	if (falda.esVacio()) return;

	if (esHoja(falda)){
		if(falda.raiz() == 'X') horasAcum += 2 * horas;
		return;
	}
	
	tiempoAyudaAux(falda.hijoIz(),horas + 1, horasAcum);
	tiempoAyudaAux(falda.hijoDer(),horas + 1, horasAcum);

	if(falda.raiz() == 'X') horasAcum += 2 * horas;
}

int tiempoAyuda(const Arbin<char>& falda) {
	// A IMPLEMENTAR
	int horas = 0;
	tiempoAyudaAux(falda,0, horas);
	return horas;
}

Arbin<char> leeArbol(istream& in) {
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
		Arbin<char> iz = leeArbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = leeArbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}

int main() {
	Arbin<char> falda;
	while (cin.peek() != EOF)  {
		cout << tiempoAyuda(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
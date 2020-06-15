#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool es_hoja(const Arbin<int> a){
	return !a.esVacio() &&
			a.hijoDer().esVacio() &&
			a.hijoIz().esVacio();
}

int numTramosNavegables_aux(const Arbin<int> a, int& caudalAcum){

	if (a.esVacio()){
		caudalAcum = 0;
		return 0;
	}

	if (es_hoja(a)) {
		caudalAcum = 1;
		return 0;
	}

	int caudalAcumIzq = 0;
	int caudalAcumDer = 0;
	int tramosIzq, tramosDer;

	tramosIzq = numTramosNavegables_aux(a.hijoIz(), caudalAcumIzq);
	tramosDer = numTramosNavegables_aux(a.hijoDer(), caudalAcumDer);

	caudalAcum = caudalAcumIzq + caudalAcumDer + a.raiz();
	if (caudalAcum < 0) caudalAcum = 0;

	return (tramosIzq + tramosDer + (caudalAcum >= 3));

}

int numeroTramosNavegables(const Arbin<int>& cuenca) {
	// A IMPLEMENTAR
	if (cuenca.esVacio()) return 0;
	int caudalAcum = 0;
	// Le resto uno por culpa del nodo raiz.
	int tramos = numTramosNavegables_aux(cuenca, caudalAcum) - 1 ;
	// Como puede quedarme negativo por la resta 
	// entonces aplico un condicional.
	return tramos < 0 ? 0 : tramos;
}

Arbin<int> leeArbol(istream& in) {
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
		Arbin<int> iz = leeArbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = leeArbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

int main() {
	Arbin<int> cuenca;
	while (cin.peek() != EOF) {
		cout << numeroTramosNavegables(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../../TADs/lista.h"
using namespace std;

// subprograma genérico para visualizar una lista por pantalla
template <class T>
void pinta(const Lista<T>& lista) {
	typename Lista<T>::ConstIterator it = lista.cbegin();
	while (it != lista.cend()) {
		cout << it.elem() << endl;
		it.next();
	}
}


/**
SUBPROGRAMA PARA CONSTRUIR UN ARBOL DE ENTEROS A PARTIR DE SU REPRESENTACIÓN EN UNA LÍNEA DEL ARCHIVO DE ENTRADA
Los árboles se representan de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con
	v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
	con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.

Ejemplos:
#  --> arbol vacío
[1] --> arbol hoja
([1]2[3])  --> arbol con raiz 2, hijo derecho 3 e hijo izdo 1
([1]2([3]4#)) --> arbol con raiz 2, hijo derecho (raíz = 4; sin hijo derecho; hijo izdo 3) e hijo izdo 1
*/
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

// numNodos: devuelve el numero de nodos del arbol.
int numNodos(const Arbin<int>& a) {
	if (a.esVacio()) return 0;

	int numNodosIzq = numNodos(a.hijoIz());
	int numNodosDer = numNodos(a.hijoDer());

	return numNodosIzq + numNodosDer;
}

// esHoja: devuelve cierto si el arbol es una hoja (los hijos izquierdo y derecho son vacios).
bool esHoja(const Arbin<int>& a) {
	if (a.esVacio()) return false;
	return a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

// numHojas: devuelve el numero de hojas del arbol.
int numHojas(const Arbin<int>& a) {
	if (a.esVacio()) return 0;
	if (esHoja(a)) return 1;
	return numHojas(a.hijoIz()) + numHojas(a.hijoDer());
}

//talla: devuelve la talla del arbol.
int talla(const Arbin<int>& a) {
	if (a.esVacio()) return 0;
	if (esHoja(a)) return 1;
	return max(talla(a.hijoIz()), talla(a.hijoDer())) + 1;
}

//frontera: devuelve una lista con todas las hojas del arbol de izquierda a derecha.
Lista<int> frontera(const Arbin<int>& a) {
	if (a.esVacio()) return Lista<int>();

	if (esHoja(a)){
		Lista<int> ret;
		ret.pon_final(a.raiz());
		return ret;
	}

	Lista<int> fronteraIzq = frontera(a.hijoIz());
	Lista<int> fronteraDer = frontera(a.hijoDer());
	
	Lista<int>::ConstIterator it = fronteraDer.cbegin();
	while (it != fronteraDer.cend()){
		fronteraIzq.pon_final(it.elem());
		it.next();
	}
	
	return fronteraIzq;
}

//espejo: devuelve un arbol nuevo que es la imagen especular del recibido
Arbin<int> espejo(const Arbin<int>& a) {
	if (a.esVacio()) return a;
	if (esHoja(a)) return a;

	return Arbin<int>(espejo(a.hijoDer()), a.raiz(), espejo(a.hijoIz()));
}


//minElem: devuelve el elemento mas pequeño de todos los almacenados en el arbol. 
//Es un error ejecutar esta operacion sobre un arbol vacio.
int minElem(const Arbin<int>& a) {
	if (a.esVacio()) throw EArbolVacio();

	if (esHoja(a)) return a.raiz();

	return min(a.raiz(), min(minElem(a.hijoIz()),minElem(a.hijoDer())));
}



void prueba2(Arbin<int> a) {

	cout << "------------------------" << endl;

	cout << a;
	cout << endl;

	cout << "numNodos:" << numNodos(a) << endl;

	cout << "esHoja:";
	if (esHoja(a))
		cout << " si\n";
	else
		cout << " no\n";

	cout << "numHojas:" << numHojas(a)  << endl;
	cout << "talla:" << talla(a) << endl;

	cout << "frontera:\n";
	pinta(frontera(a));

	
	Arbin<int> es = espejo(a);
	cout << "espejo:\n" ;
	cout << es << endl;
	
	if (!a.esVacio())
		cout << "minElem: " << minElem(a) << endl;
	else
		cout << "No se puede obtener el minElem de un arbol vacio" << endl;

	cout << "------------------------" << endl;
}

int main() {
	Arbin<int> arbol;
	ifstream archivo;

	archivo.open("in.txt");
	while (archivo.peek() != EOF)  {
		Arbin<int> a = lee_arbol(archivo);
		prueba2(a);
		string resto_linea;
		getline(archivo, resto_linea);
	}
	archivo.close();
	return 0;
}

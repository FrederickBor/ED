#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

bool esHoja(const Arbin<int> &a){
	return a.hijoDer().esVacio() && a.hijoIz().esVacio();
}

unsigned int auxNumHojasMasProfundasQue(const Arbin<int>& a, unsigned int k, int profundidad){
	if (a.esVacio()) return 0;
	if (esHoja(a)){
		if (profundidad >= k) return 1;
		return 0;
	}
	
	unsigned int hojas_iz, hojas_der;
	hojas_iz = auxNumHojasMasProfundasQue(a.hijoIz(),k,profundidad+1);
	hojas_der = auxNumHojasMasProfundasQue(a.hijoDer(),k,profundidad+1);

	return hojas_iz + hojas_der;
}

/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   La complejidad de la funcion creada es O(k) siendo k el numero de nodos totales del arbol,
			   esto es así ya que se debe pasar una vez por cada nodo para obtener una solución.
*/
unsigned int numero_hojas_mas_profundas_que(const Arbin<int>& a, unsigned int k) {
	// A IMPLEMENTAR
	return auxNumHojasMasProfundasQue(a,k,0);
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



/**
La entrada al programa consiste de líneas formadas por:
(1) Un árbol de enteros
(2) El valor de k
Los árboles se codifican de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada línea leida, escribe en la salida estádar
el número de hojas que están a profundidad mayor que k

	
Ejemplo de entrada:

([2]1([4]3[5])) 0
([2]1([4]3[5])) 1
([2]1([4]3[5])) 2
([2]1([4]3[5])) 3
([2]1([4]3[5])) 4
([2]1([4]3[5])) 100

Salida asociada:

3
3
2
0
0
0

*/


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		int k;
		cin >> k;
		cout << numero_hojas_mas_profundas_que(a,k) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}

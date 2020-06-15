/**
Este programa lee árboles de la entrada estándar, 
codificados de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada árbol leído, escribe en la salida estándar
el número de nodos singulares de dicho árbol.
	
Algunos casos representativos:

#
[0]
[5]
(([4]3[-3])1[-4])

-El primero representa el árbol vacío. Al no tener nodos,
un árbol vacío tiene 0 nodos sigulares.
-El segundo representa un árbol con un único nodo, cuyo valor
es 0. Dicho nodo es singular, ya que: (i) como no tiene 
ascestros, la suma de los ancestros es 0, (ii) como no
tiene descendientes, la suma de los descendientes es 0. 
-El tercero representa otro árbol con un único nodo, cuyo
valor es 5. Por la misma razón que en el segundo ejemplo,
este nodo es singular.
-El cuarto representa el siguiente árbol:
     
	       1
		  /  \
		  3  -4
         / \  
        4  -3 

Este árbol tiene 2 nodos sigulares: la raíz, y la raíz del hijo 
izquierdo. 

Por tanto, la salida del programa para estos casos será:

0
1
1
2

Algunos casos de prueba más:

ENTRADAS
(((#-2[-2])0#)0[-1])
(#-1[0])
([2]1[2])
(#-2(((#0([2]0(((((#1#)0(#0#))0(#-1[-2]))0(((#0#)2#)0[2]))0#)))2#)-1#))
((((#0[1])1#)1((#2(([-2]1#)1([2]1#)))0#))0(#0(#2[-1])))

SALIDAS ASOCIADAS
1
1
0
0
1



*/
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

bool es_hoja(const Arbin<int> a){
	return !a.esVacio() &&
			a.hijoDer().esVacio() &&
			a.hijoIz().esVacio();
}

unsigned int numeros_singulares_aux(const Arbin<int> a, int sumaAnt, int& sumaDes){

	if (a.esVacio()){
		sumaDes = 0;
		return 0;
	}
	
	if (es_hoja(a)){
		sumaDes = a.raiz();
		return sumaAnt == sumaDes - a.raiz();
	}

	int sumaDesIz = 0,
		sumaDesDer = 0,
		numSingIz = 0,
		numSingDer = 0;

	numSingIz = numeros_singulares_aux(a.hijoIz(), sumaAnt + a.raiz(), sumaDesIz);
	numSingDer = numeros_singulares_aux(a.hijoDer(), sumaAnt + a.raiz(), sumaDesDer);

	sumaDes = sumaDesIz + sumaDesDer + a.raiz();
	return numSingDer + numSingIz + (sumaDesDer + sumaDesIz == sumaAnt);

}

/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   ***A COMPLETAR***
			   Esta funcion tiene coste O(n) donde n es el numero de 
			   elementos presentes en el arbol.
*/
unsigned int numero_singulares(const Arbin<int>& a) {
	// A IMPLEMENTAR
	if (a.esVacio()) return 0;
	if (es_hoja(a)) return 1;

	int sumaDes = 0;
	return numeros_singulares_aux(a, 0, sumaDes);
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
		cout << numero_singulares(lee_arbol(cin)) << endl;
		string resto_linea;
		getline(cin, resto_linea);
		//if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}

#include "lista.h"
#include <iostream>
#include <string>
#include "diccionario.h"
using namespace std;


// Clase Puntuacion. Sirve para representar la puntuacion final  (nota)
// obtenida por un alumno.
class Puntuacion {
  public:
    string alumno;
    int nota;	
	Puntuacion(const string& nombre, int puntuacion): alumno(nombre), nota(puntuacion) {}
};

void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado) {
	Diccionario<string, int> dict = Diccionario<string, int>();
	
	Lista<string>::ConstIterator itBien = bien.cbegin();
	Lista<string>::ConstIterator itMal = mal.cbegin();
	
	// Recorre lista bien
	while (itBien != bien.cend()){
		Diccionario<string, int>::Iterator p = dict.busca(itBien.elem());
		if (p == dict.end())
			dict.inserta(itBien.elem(), 1);
		else
			p.valor()++;

		itBien.next();
	}
	
	// Recorre lista mal
	while (itMal != mal.cend()){
		Diccionario<string, int>::Iterator p = dict.busca(itMal.elem());
		if (p == dict.end())
			dict.inserta(itMal.elem(), -1);
		else
			p.valor()--;
		
		itMal.next();
	}
	
	Diccionario<string,int>::ConstIterator it = dict.cbegin();

	while (it != dict.cend()){
		if (it.valor() != 0) listado.pon_ppio(Puntuacion(it.clave(), it.valor())); 
		it.next();
	}
}


void imprimePuntuaciones(Lista<Puntuacion>& listado) {
  Lista<Puntuacion>::ConstIterator i = listado.cbegin();
  Lista<Puntuacion>::ConstIterator e = listado.cend();
  while (i != e) {
	  cout << "[" << i.elem().alumno << ":" << i.elem().nota << "]";
      i.next();	  
  }  
  cout << endl;
}

void leeResultados(Lista<string>& bien, Lista<string>& mal) {
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			string resultado;
			cin >> resultado;
			if (resultado == "+")
				bien.pon_final(nombre);
			else
				mal.pon_final(nombre);
		}
	} while (nombre != "#");
}

int main() {
  string comienzo;
  while (cin >> comienzo) {
	 Lista<string> bien;
	 Lista<string> mal;
	 Lista<Puntuacion> listado;
	 leeResultados(bien, mal);
	 califica(bien, mal,listado);
	 imprimePuntuaciones(listado);
  }
  return 0;   
}
#include <iostream>
using namespace std;
#include <string>

#include "lista.h"
#include "pila.h"
// INCLUIR EL RESTO DE TADS QUE SE CONSIDEREN OPORTUNOS

bool esVocal(char c){
	return (
		(tolower(c) == 'a') ||
		(tolower(c) == 'e') || 
		(tolower(c) == 'i') || 
		(tolower(c) == 'o') || 
		(tolower(c) == 'u')
	);
}

// X'
void invierteSecuenciasNoVocales(Lista<char> &mensaje) {
	Pila<char> p;
	Lista<char>::Iterator it = mensaje.begin();
	while (it != mensaje.end()){
		if (esVocal(it.elem())){
			while (!p.esVacia()){
				// Insertar inserta antes del iterador
				mensaje.insertar(p.cima(), it);
				p.desapila();
			}
			// Me salto la vocal
			it.next();
		}
		else
		{
			// Apilo el valor
			p.apila(it.elem());
			// Quito la letra del mensaje
			it = mensaje.eliminar(it);
		}
	}

	// Si quedan elementos en la pila, los añadimos al mensaje
	while (!p.esVacia()){
		// Insertar inserta antes del iterador
		mensaje.insertar(p.cima(), it);
		p.desapila();
	}
}
 
// Imprime la lista por la salida estandar
void imprime(const Lista<char>& l) {
	l.print();
	cout << endl;
}


// Codifica el mensaje
void codifica(Lista<char>& mensaje) {
	invierteSecuenciasNoVocales(mensaje);
	mensaje.enredar();
}

  // Transforma la linea en una lista de caracteres
void construyeMensaje(const string& linea, Lista<char>& mensaje) {
	for(unsigned int i=0; i < linea.size(); i++)
		mensaje.pon_final(linea[i]);  
}

int main() {
	string linea;
	while(getline(cin,linea)) {
	   Lista<char> mensaje;
	   construyeMensaje(linea,mensaje);
       codifica(mensaje);
	   imprime(mensaje);
	}
	return 0;
}	

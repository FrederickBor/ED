/**
GRUPO:   
*/

/**
@file Cola.h

Implementaci�n del TAD Cola utilizando una
lista enlazada de nodos.

Estructura de Datos y Algoritmos
Facultad de Inform�tica
Universidad Complutense de Madrid

(c) Marco Antonio G�mez Mart�n, 2012   Mercedes G�mez Albarr�n, 2016
*/
#ifndef __COLA_LISTA_ENLAZADA_H
#define __COLA_LISTA_ENLAZADA_H
#include <cstddef>

/// Excepciones generadas por algunos m�todos
class EColaVacia {};

//Excepci�n que se levanta si se especifica
//una posici�n inv�lida para la operaci�n
//llevarAlPrincipio. 
class EPosicionInvalida {};

/**
Implementaci�n del TAD Cola utilizando una lista enlazada.

Las operaciones son:

- ColaVacia: -> Cola. Generadora implementada en el
constructor sin par�metros.
- pon: Cola, Elem -> Cola. Generadora
- quita: Cola - -> Cola. Modificadora parcial.
- primero: Cola - -> Elem. Observadora parcial.
- esVacia: Cola -> Bool. Observadora.
- longitud: unsigned int. Devuelve el n�mero de elementos
de la cola.

@author Marco Antonio G�mez Mart�n   Mercedes G�mez Albarr�n
*/
template <class T>
class Cola {
public:

	

	/**
	Desplaza un nodo, identificado por su posici�n, al principio de la cola.
	En una cola no vac�a, las posiciones v�lidas var�an entre 1 y 
	la longitud de la cola.
	En caso de que la posici�n del nodo no sea v�lida, se levantar�
	la excepci�n EPosicionInvalida.
	@param pos Posici�n del nodo a desplazar.
	**/

	/**
	COMPLEJIDAD: Determinar aqu�, justificadamente, la complejidad de esta operaci�n


	**/

	void llevarAlPrincipio(unsigned int pos) {

		// A IMPLEMENTAR
		if (
			(pos == 0)||
			(pos > longitud()) ||
			esVacia()
		) throw EPosicionInvalida();

		if (pos == 1) return;

		Nodo *anterior = _prim;
		Nodo *aCambiar;

		int i = 1;

		while (i < pos-1){
			anterior = anterior->_sig;
			i++;
		}

		aCambiar = anterior->_sig;
		anterior->_sig = aCambiar->_sig;

		aCambiar->_sig = _prim;

		_prim = aCambiar;

		if (pos == longitud()) _ult = anterior;
	}


	/** Constructor; operacion ColaVacia */
	Cola() : _prim(NULL), _ult(NULL), _nelems(0) {
	}


	/**
	A�ade un elemento en la parte trasera de la cola.
	Operaci�n generadora.

	@param elem Elemento a a�adir.
	*/
	void pon(const T &elem) {
		Nodo *nuevo = new Nodo(elem);
		if (esVacia()) _prim = nuevo;
		else _ult->_sig = nuevo;
		_ult = nuevo;
		_nelems++;
	}

	/**
	Elimina el primer elemento de la cola.
	Operaci�n modificadora parcial.

	error: falla si la cola est� vac�a
	*/
	void quita() {
		if (esVacia())
			throw EColaVacia();
		Nodo *aBorrar = _prim;
		if (_prim == _ult)
			_prim = _ult = NULL;
		else
			_prim = _prim->_sig;
		delete aBorrar;
		_nelems--;
	}

	/**
	Devuelve el primer elemento de la cola. Operaci�n
	observadora parcial.

	error: falla si la cola est� vac�a
	@return El primer elemento de la cola.
	*/
	const T &primero() const {
		if (esVacia())
			throw EColaVacia();
		return _prim->_elem;
	}

	/**
	Indica si la cola tiene elementos o no.

	@return true si la cola no tiene ning�n elemento.
	*/
	bool esVacia() const {
		return _prim == NULL;
	}

	/**
	Devuelve el n�mero de elementos de la cola.

	@return N�mero de elementos de la cola.
	*/
	unsigned int longitud() const {
		return _nelems;
	}

	/** Destructor; elimina la lista enlazada. */
	~Cola() {
		libera();
		_prim = _ult = NULL;
	}


	/** Constructor copia */
	Cola(const Cola<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Cola<T> &operator=(const Cola<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Cola<T> &rhs) const {
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL) && (p1->_elem == p2->_elem)) {
			p1 = p1->_sig;
			p2 = p2->_sig;
		}
		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Cola<T> &rhs) const {
		return !(*this == rhs);
	}


private:

	/**
	Clase nodo que almacena internamente el elemento (de tipo T),
	y un puntero al nodo siguiente, que podr�a ser NULL si
	el nodo es el �ltimo de la lista enlazada.
	*/
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T &elem, Nodo *sig) :
			_elem(elem), _sig(sig) {}

		T _elem;
		Nodo *_sig;
	};


	/**
	Genera una copia de other en la cola receptora
	*/
	void copia(const Cola &other) {
		if (other.esVacia())
			_prim = _ult = NULL;
		else {
			Nodo *puntAOrigen = other._prim;
			Nodo *ultimo;
			_prim = new Nodo(puntAOrigen->_elem);
			ultimo = _prim;
			while (puntAOrigen->_sig != NULL) {
				puntAOrigen = puntAOrigen->_sig;
				ultimo->_sig = new Nodo(puntAOrigen->_elem);
				ultimo = ultimo->_sig;
			}
			_ult = ultimo;
		}
		_nelems = other._nelems;
	}


	/**
	Elimina todos los nodos de la lista enlazada que soporta la cola.
	*/
	void libera() {
		while (_prim != NULL) {
			Nodo *aBorrar = _prim;
			_prim = _prim->_sig;
			delete aBorrar;
		}
	}


	/** Puntero al primer elemento. */
	Nodo *_prim;

	/** Puntero al �ltimo elemento. */
	Nodo *_ult;

	/** N�mero de elementos */
	unsigned int _nelems;
};

#endif // __PILA_LISTA_ENLAZADA_H


	

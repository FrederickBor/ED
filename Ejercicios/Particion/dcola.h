/**
  @file DColaC.h

  Implementaci�n del TAD doble cola, utilizando una
  lista doblemente enlazada con nodo fantasma o
  cabecera.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012   Mercedes G�mez Albarr�n, 2016
*/
#ifndef __DCOLAC_H
#define __DCOLAC_H
#include <cstddef>


/// Excepciones generadas por algunos m�todos
class EDColaVacia {};
#include <cassert>
#include <iostream>

/**
 Implementaci�n del TAD Doble Cola utilizando una lista doblemente
 enlazada circular y con nodo fantasma.

 Las operaciones son:

Crear una doble cola vac�a: dcolaVacia: --> DCola. Generadora
A�adir un elemento al final: pon_final: DCola, Elem --> DCola. Generadora
A�adir un elemento al principio: pon_ppio: DCola, Elem --> DCola. Generadora
Eliminar un elemento por el final: quita_final: DCola--> DCola. Modificadora parcial.
Eliminar un elemento por el principio: quita_ppio: DCola--> DCola. Modificadora parcial.
Acceder al primer elemento: primero: DCola--> Elem. Observadora parcial.
Acceder al �ltimo elemento: : ultimo: DCola--> Elem. Observadora parcial.
Averiguar si una doble cola tiene elementos: esVacia: DCola--> Bool. Observadora.

 @author Marco Antonio G�mez Mart�n   Mercedes G�mez Albarr�n
 */

template <class T>
class DCola {
public:

	/** Constructor; operaci�n DColaVacia. */
	DCola() {
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;
	}

	void particion(int pivote){
		// IMPLEMENTAR
		Nodo* _aux = _fantasma->_sig; // Primer nodo
		Nodo* _ultAux = _fantasma->_ant; // Ultimo nodo
		while (_aux != _ultAux){
			if (_aux->_elem >= pivote){
				_aux = pasar_al_final(_aux);
			}
			else
				_aux = _aux->_sig;
		}

		if (_aux->_elem >= pivote){
			_aux = pasar_al_final(_aux);
		}
	}

	void imprimir() const {
		if (_fantasma->_sig != _fantasma) {
			std::cout << _fantasma->_sig->_elem;
			Nodo* actual = _fantasma->_sig->_sig;
			while (actual != _fantasma) {
				std::cout << " " << actual->_elem;
				actual = actual->_sig;
			}
		}
	}

	/**
	 A�ade un nuevo elemento al final de la dcola (a la "derecha"). Operaci�n generadora.
	 
	 @param elem Elemento que se a�ade en la final de la dcola.
	*/
	void pon_final(const T &e) {
		insertaElem(e, _fantasma->_ant, _fantasma);
	}

	/**
	 A�ade un nuevo elemento en la cabeza de la dcola (a la "izquierda"). Operaci�n generadora.

	 @param elem Elemento que se a�ade en la cabecera de la dcola.
	*/
	void pon_ppio (const T &e) {
		insertaElem(e, _fantasma, _fantasma->_sig);
	}

	/**
	 Devuelve el valor almacenado en la cabecera de la dcola.
	 Observadora pacial.
	 
	 error: falla al preguntar por el primero de una dcola vac�a.
	 @return Elemento en la cabecera de la dcola.
	 */
	const T &primero() const {
		if (esVacia())
			throw EDColaVacia();
		return _fantasma->_sig->_elem;
	}


	/**
	 Elimina el primer elemento de la dcola. Modificadora parcial.
	 Es un error intentar eliminar en una dcola vac�a.
	*/
	void quita_ppio() {
		if (esVacia())
			throw EDColaVacia();
		borraElem(_fantasma->_sig);
	}

	

	/**
	 Devuelve el valor almacenado en la �ltima posici�n
	 de la dcola (a la derecha).
	 Es un error preguntar por el primero de una dcola vac�a.

	 @return Elemento en la cola de la dcola.
	 */
	const T &ultimo() const {
		if (esVacia())
			throw EDColaVacia();
		return _fantasma->_ant->_elem;
	}

	/**
	 Elimina el �ltimo elemento de la dcola. Modificadora parcial.

	 error: al intentar eliminar en una dcola vac�a.
	*/
	void quita_final()  {
		if (esVacia())
			throw EDColaVacia();
		borraElem(_fantasma->_ant);
	}

	
	/**
	 Operaci�n observadora para saber si una dcola tiene o no elementos.

	 @return true si la dcola no tiene elementos.
	 */
	bool esVacia() const {
		return _fantasma->_sig == _fantasma;
	}

	
	/** Destructor; elimina la lista doblemente enlazada. */
	~DCola() {
		libera();
	}

	/** Constructor copia */
	DCola(const DCola<T> &other) : _fantasma(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	DCola<T> &operator=(const DCola<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const DCola<T> &rhs) const {
		Nodo *p1 = _fantasma->_sig; // primer nodo "real" de la dcola receptora
		Nodo *p2 = rhs._fantasma->_sig; // primer nodo "real" de la dcola rhs
		while ((p1 != _fantasma) && (p2 != rhs._fantasma) && (p1->_elem == p2->_elem)) {
			p1 = p1->_sig;
			p2 = p2->_sig;
		}
		return (p1 == _fantasma) && (p2 == rhs._fantasma);
	}


	bool operator!=(const DCola<T> &rhs) const {
		return !(*this == rhs);
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podr�an ser NULL si el nodo es el primero
	 y/o �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
		Nodo(Nodo *ant, const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig), _ant(ant) {}

		T _elem;
		Nodo *_sig;
		Nodo *_ant;
	};

	/**
	 Inserta un elemento entre el nodo1 y el nodo2.
	 Devuelve el puntero al nodo creado.
	 Caso general: los dos nodos existen.
	    nodo1->_sig == nodo2
	    nodo2->_ant == nodo1
	 Casos especiales: alguno de los nodos no existe
	    nodo1 == NULL y/o nodo2 == NULL
	*/
	static Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
		Nodo *nuevo = new Nodo(nodo1, e, nodo2);
		if (nodo1 != NULL) // hay un nodo anterior al nuevo
			nodo1->_sig = nuevo;
		if (nodo2 != NULL) // hay un nodo posterior al nuevo
			nodo2->_ant = nuevo;
		return nuevo;
	}

	/**
	Genera una copia de other en el receptor
	*/
	void copia(const DCola<T> &other) {
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;

		Nodo *act = other._fantasma->_sig;
		while (act != other._fantasma) {
			pon_final(act->_elem);
			act = act->_sig;
		}
	}

	/**
	 Elimina el nodo n. Si el nodo tiene nodos antes
	 o despu�s, actualiza sus punteros anterior y siguiente.
	 Caso general: hay nodos anterior y siguiente.
	 Casos especiales: algunos de los nodos (anterior o siguiente
	 a n) no existen.
	*/
	static void borraElem(Nodo *n) {
		assert(n != NULL);

		Nodo *ant = n->_ant;
		Nodo *sig = n->_sig;
		if (ant != NULL)
			ant->_sig = sig;
		if (sig != NULL)
			sig->_ant = ant;
		delete n;
	}

	/**
	Libera los nodos de la lista que sustenta al receptor
	*/
	void libera() {
		// Antes de empezar a liberar quitamos la circularidad para evitar bucle
		// infinito...
		_fantasma->_ant->_sig = NULL;
		_fantasma->_ant = NULL;
		// Una vez convertida en una lista lineal se liberan los nodos
		while (_fantasma != NULL) {
			Nodo *aux = _fantasma;
			_fantasma = _fantasma->_sig;
			delete aux;
		}
		_fantasma = NULL;
	}

	Nodo* pasar_al_final(Nodo* n){
		Nodo* a_devolver = n->_sig;

		// Desacoplamos el nodo
		n->_ant->_sig = n->_sig;
		a_devolver->_ant = n->_ant;

		// Acoplamos el nodo al final
		n->_sig = _fantasma;
		n->_ant = _fantasma->_ant;
		n->_ant->_sig = n;
		_fantasma->_ant = n;

		return a_devolver;
	}


	// Puntero al nodo fantasma
	Nodo *_fantasma;
};

#endif // __DCOLAC_H

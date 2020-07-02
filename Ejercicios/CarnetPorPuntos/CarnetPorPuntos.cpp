/**
NOMBRE Y APELLIDOS:
LABORATORIO:
PUESTO:
USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "CarnetPorPuntos.h"
#include <iostream>
using namespace std;

/**
Implementa aquí los métodos de las clases adicionales
*/

// COSTE O(1)
unsigned int Conductor::obtener_puntos() const{ return _puntos;};

// COSTE O(1)
void Conductor::sumar_puntos(unsigned int puntos){
	if (_puntos + puntos > 15) _puntos = 15;
	else _puntos += puntos;
};

// COSTE O(1)
void Conductor::restar_puntos(unsigned int puntos){
	if (puntos >= _puntos) _puntos = 0;
	else _puntos -= puntos;	
};

// COSTE O(1)
Posicion Conductor::obtener_posicion() const{
	return _posicion;
};

// COSTE O(1)
void Conductor::cambiar_posicion(const Posicion& posicion){
	_posicion = posicion;
};

// COSTE O(1)
CarnetPorPuntos::CarnetPorPuntos(){
	listas_puntos.inserta(15, Lista<string>());
};
 
/**
Debes completar la implementación de las operaciones de CarnetPorPuntos,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 
 Complejidad Constante ya que solo se busca si esta el nuevo conductor
 e insertar tambien tiene coste constante.
*/
// COSTE O(1)
void CarnetPorPuntos::nuevo(const string& dni) {
	DiccionarioHash<string, Conductor>::ConstIterator it = conductores.cbusca(dni);
	if (it != conductores.cend()) throw EConductorDuplicado();

	DiccionarioHash<int, Lista<string> >::Iterator it_listas = listas_puntos.busca(15);
	it_listas.valor().pon_ppio(dni);
	
	Posicion p = it_listas.valor().begin();
	Conductor c = Conductor(p);
	conductores.inserta(dni, c);
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
 
 Complejidad constante ya que hemos guardado la posicion del 
 conductor como un atributo de la clase conductor.
*/
// COSTE O(1)
void CarnetPorPuntos::quitar(const string& dni, unsigned int puntos) {
	DiccionarioHash<string, Conductor>::Iterator it = conductores.busca(dni);
	if (it == conductores.end()) throw EConductorNoExiste();

	unsigned int puntos_anteriores = it.valor().obtener_puntos();
	it.valor().restar_puntos(puntos);

	if (puntos_anteriores != it.valor().obtener_puntos()){
		DiccionarioHash<int, Lista<string> >::Iterator it_lista = listas_puntos.busca(puntos_anteriores);
		if (! listas_puntos.contiene(it.valor().obtener_puntos()))
			listas_puntos.inserta(it.valor().obtener_puntos(), Lista<string>());
		DiccionarioHash<int, Lista<string> >::Iterator it_lista_nueva = listas_puntos.busca(it.valor().obtener_puntos());
		it_lista.valor().eliminar(it.valor().obtener_posicion());
		it_lista_nueva.valor().pon_ppio(dni);
		Posicion p = it_lista_nueva.valor().begin();
		it.valor().cambiar_posicion(p);
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

 Complejidad constante ya que hemos guardado la posicion del 
 conductor como un atributo de la clase conductor.
*/
// COSTE O(1)
void CarnetPorPuntos::recuperar(const string& dni, unsigned int puntos) {
	DiccionarioHash<string, Conductor>::Iterator it = conductores.busca(dni);
	if (it == conductores.end()) throw EConductorNoExiste();

	unsigned int puntos_anteriores = it.valor().obtener_puntos();
	it.valor().sumar_puntos(puntos);

	if (puntos_anteriores != it.valor().obtener_puntos()){
		DiccionarioHash<int, Lista<string> >::Iterator it_lista = listas_puntos.busca(puntos_anteriores);
		if (! listas_puntos.contiene(it.valor().obtener_puntos()))
			listas_puntos.inserta(it.valor().obtener_puntos(), Lista<string>());
		DiccionarioHash<int, Lista<string> >::Iterator it_lista_nueva = listas_puntos.busca(it.valor().obtener_puntos());
		
		it_lista.valor().eliminar(it.valor().obtener_posicion());
		it_lista_nueva.valor().pon_ppio(dni);
		Posicion p = it_lista_nueva.valor().begin();
		it.valor().cambiar_posicion(p);
	}
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

 Complejidad constante ya que buscar en un diccionario hash tiene 
 coste constante y luego obtener un valor dentro de la clase 
 tambien es constante
*/
// COSTE O(1)
unsigned int CarnetPorPuntos::consultar(const string& dni) const {
	DiccionarioHash<string, Conductor>::ConstIterator it = conductores.cbusca(dni);
	if (it == conductores.cend()) throw EConductorNoExiste();
	return it.valor().obtener_puntos();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

 Complejidad constante ya que no se realizan copias del vector, 
 y solo se busca el valor en un DiccionarioHash y ademas obtener 
 la longitud en una lista es una operacion constante.
*/
// COSTE O(1)
unsigned int CarnetPorPuntos::cuantos_con_puntos(unsigned int puntos) const {
	if (puntos < 0 || puntos > 15) throw EPuntosNoValidos();
	DiccionarioHash<int, Lista<string> >::ConstIterator it = listas_puntos.cbusca(puntos);
	unsigned int ret = 0;
	if (it != listas_puntos.cend()) ret = it.valor().longitud();
	return ret;
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

 Complejidad constante ya que no se realizan copias del vector, 
 y solo se busca el valor en un DiccionarioHash

*/
// COSTE O(1)
const Lista<string>& CarnetPorPuntos::lista_por_puntos(unsigned int puntos) const {
	if (puntos < 0 || puntos > 15) throw EPuntosNoValidos();
	DiccionarioHash<int, Lista<string> >::ConstIterator it = listas_puntos.cbusca(puntos);
	if (it != listas_puntos.cend())
		return it.valor();
	else
		return Lista<string>();
}

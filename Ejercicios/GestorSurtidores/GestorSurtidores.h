#ifndef __SURTIDORES_H
#define __SURTIDORES_H

#include <string>
#include "DiccionarioHash.h"
#include "lista.h"
using namespace std;

typedef string tVehiculo;
typedef string tSurtidor;
typedef string tTipoCombustible;
typedef Lista<tVehiculo>::Iterator Posicion;

/* Excepciones */
class ESurtidorDuplicado {};
class ESurtidorNoExiste {};
class ELlegadaVehiculo {};
class EErrorVenta {};

/* Clase para representar los objetos devueltos
   por la operación 'vende' */
class ResulVenta {
	public:
	   tVehiculo _vehiculo;
	   unsigned int _litros_que_quedan;
	   ResulVenta(tVehiculo vehiculo, unsigned int litros_que_quedan) {
		     _vehiculo = vehiculo;
			 _litros_que_quedan = litros_que_quedan;
	   }	
};

class Surtidor {
	public:
		DiccionarioHash<tTipoCombustible, unsigned int>	combustibles;
		Lista<tVehiculo> fila_espera;
};

class Vehiculo {
	public:
		Posicion _posicion;
		tSurtidor _surtidor;

		Vehiculo(const Posicion& posicion, tSurtidor surtidor) : _surtidor(surtidor), _posicion(posicion) {};
};

class GestorSurtidores {
	public:
	   GestorSurtidores();
	   void an_surtidor(const tSurtidor& surtidor);
	   void carga(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros);
	   void pon_en_espera(const tVehiculo& vehiculo, const tSurtidor& surtidor);
	   ResulVenta vende(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros);
	   void abandona(const tVehiculo& vehiculo);
     private:	   
	    /* Debes añadir aquí los detalles de
	    representación que consideres oportuno */

		DiccionarioHash<tSurtidor, Surtidor> surtidores;
		DiccionarioHash<tVehiculo, Vehiculo> vehiculos;
};

#endif
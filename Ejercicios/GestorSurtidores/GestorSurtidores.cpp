#include "GestorSurtidores.h"


/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación 


*/
GestorSurtidores::GestorSurtidores() {
  // Vacio	
}

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación 

O(1)

*/
void GestorSurtidores::an_surtidor(const tSurtidor& surtidor) {	
  if (surtidores.contiene(surtidor)) throw ESurtidorDuplicado();
  surtidores.inserta(surtidor, Surtidor());
}


/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación 

O(1)

*/
void GestorSurtidores::carga(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros) {
  DiccionarioHash<tSurtidor, Surtidor>::Iterator itSurtidor = surtidores.busca(surtidor);

  if (itSurtidor == surtidores.end()) throw ESurtidorNoExiste();

  DiccionarioHash<tTipoCombustible, unsigned int>::Iterator itTipoCombustible = itSurtidor.valor().combustibles.busca(tipo_combustible);

  if (itTipoCombustible == itSurtidor.valor().combustibles.end())
    itSurtidor.valor().combustibles.inserta(tipo_combustible, litros);
  else
    itTipoCombustible.valor() += litros;
}	

/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación 

O(1)
*/
void GestorSurtidores::pon_en_espera(const tVehiculo& vehiculo, const tSurtidor& surtidor) {
  DiccionarioHash<tSurtidor, Surtidor>::Iterator itSurtidor = surtidores.busca(surtidor);

  if ( (vehiculos.contiene(vehiculo)) || // El vehiculo espera en otro surtidor
    (itSurtidor == surtidores.end())) // Surtidor no existe
    throw ELlegadaVehiculo();

  itSurtidor.valor().fila_espera.pon_ppio(vehiculo);
  Posicion p = itSurtidor.valor().fila_espera.begin();
  vehiculos.inserta(vehiculo, Vehiculo(p, surtidor));
}


/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación 


*/
ResulVenta GestorSurtidores::vende(const tSurtidor& surtidor, const tTipoCombustible& tipo_combustible, unsigned int litros) {
/* A IMPLEMENTAR */	
  DiccionarioHash<tSurtidor, Surtidor>::Iterator itSurtidor = surtidores.busca(surtidor);

  if ((itSurtidor == surtidores.end())|| // Surtidor Existe
      (itSurtidor.valor().fila_espera.esVacia()) // No hay coches en la lista de espera
    ) 
    throw EErrorVenta();

  DiccionarioHash<tTipoCombustible, unsigned int>::Iterator itCombustible = itSurtidor.valor().combustibles.busca(tipo_combustible);
  DiccionarioHash<tTipoCombustible, unsigned int>::Iterator itCombustible_end = itSurtidor.valor().combustibles.end();

  if ((itCombustible == itCombustible_end) ||// no dispone de combustible solicitado
      (litros > itCombustible.valor())) // No hay suficiente combustible
      throw EErrorVenta();

  tVehiculo vehiculo= itSurtidor.valor().fila_espera.ultimo();
  vehiculos.borra(vehiculo);
  itSurtidor.valor().fila_espera.quita_final();
  itCombustible.valor() -= litros;

  return ResulVenta(vehiculo, itCombustible.valor());
}
	   
/*
COMPLEJIDAD: Determina justiticadamente la complejidad
de esta operación 

O(1)
*/
void GestorSurtidores::abandona(const tVehiculo& vehiculo) {
  DiccionarioHash<tVehiculo, Vehiculo>::Iterator itVehiculo = vehiculos.busca(vehiculo);

  if(itVehiculo != vehiculos.end()){
    DiccionarioHash<tSurtidor, Surtidor>::Iterator itSurtidor = surtidores.busca(itVehiculo.valor()._surtidor);
    itSurtidor.valor().fila_espera.eliminar(itVehiculo.valor()._posicion);
    vehiculos.borra(vehiculo);
  }
}

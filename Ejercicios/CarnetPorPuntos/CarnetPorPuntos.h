/**
NOMBRE Y APELLIDOS:
LABORATORIO:
PUESTO:
USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/
#ifndef _CARNET_POR_PUNTOS_H
#define _CARNET_POR_PUNTOS_H

#include "lista.h"
#include "DiccionarioHash.h"
#include <string>
using namespace std;

class EConductorDuplicado {};
class EConductorNoExiste {};
class EPuntosNoValidos {};

typedef Lista<string>::Iterator Posicion;

class Conductor{
public:
   Conductor(const Posicion& posicion) : _puntos(15), _posicion(posicion) {};
   unsigned int obtener_puntos() const;
   void sumar_puntos(unsigned int puntos);
   void restar_puntos(unsigned int puntos);
   Posicion obtener_posicion() const;
   void cambiar_posicion(const Posicion& posicion);
private:
   unsigned int _puntos; // Puntos que tiene en el carnet.
   Posicion _posicion;
};

class CarnetPorPuntos {
public:
   CarnetPorPuntos();
   void nuevo(const string& dni);
   void quitar(const string& dni, unsigned int puntos);
   void recuperar(const string& dni, unsigned int puntos);
   unsigned int consultar(const string& dni) const;
   unsigned int cuantos_con_puntos(unsigned int puntos) const;
   const Lista<string>& lista_por_puntos(unsigned int puntos) const;
private:
   DiccionarioHash<string, Conductor> conductores; // Lleva los conductores registrados y sus puntos.
   DiccionarioHash<int, Lista<string> > listas_puntos; // Lleva las listas actualizadas segun los puntos de cada conductor.
};

#endif
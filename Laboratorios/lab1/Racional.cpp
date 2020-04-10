#include "Racional.h"
#include <cmath>
using namespace std;


//Metodos publicos

  	//**** COMPLETAR
	//  Deben implementarse los metodos publicos de la clase
	//****

Racional::Racional(){
	_numer = new long;
	*_numer = 0;

	_denom = new long;
	*_denom	= 1;
}

Racional::Racional(long n, long d){
	if (d == 0) throw EDenominadorCero();

	_numer = new long;
	*_numer = n;

	_denom = new long;
	*_denom	= d;

	this->reduce();
}

Racional Racional::suma(const Racional & r)
{
	Racional aux;

	*aux._denom = mcm(*_denom, *r._denom);
	*aux._numer = ((*_numer) * (*aux._denom) / (*_denom)) + ((*r._numer) * (*aux._denom) / (*r._denom));

	aux.reduce();

	return aux;
}
	
Racional Racional::operator-(const Racional & r)
{

	long denom = *_denom;

	*_denom = mcm(*_denom, *r._denom);
	*_numer = ((*_numer) * (*_denom) / denom) - ((*r._numer) * (*_denom) / (*r._denom));


	this->reduce();

	return *this;
}

Racional Racional::operator*=(const Racional & r)
{
	*_numer *= (*r._numer);
	*_denom *= (*r._denom);

	reduce();

	return *this;
}

void Racional::divideYActualiza(const Racional & r)
{
	if ((*r._numer) == 0)
		throw EDivisionPorCero();
	
	*_numer *= *r._denom;
	*_denom *= *r._numer;

	reduce();
}

bool Racional::operator==(const Racional & r) const
{
	return (
		((*_numer) == (*r._numer)) && 
		((*_denom) == (*r._denom))
	);
}
	
// Funciones amigas
ostream& operator<<(ostream& out, const Racional& f) {
	out << *f._numer << "/" << *f._denom;
	return out;
}

// Metodos privados
void Racional::reduce() {
	  // Se asegura que el denominador siempre sea positivo   
	if (*_denom < 0) {
		*_numer = -(*_numer);
		*_denom = -(* _denom);
	}
	  // Se divide numerador y denominador por el maximo comun divisor de ambos
	long fsimp = mcd(*_numer, *_denom);
	*_numer /= fsimp;
	*_denom /= fsimp;
}

long Racional::mcd(long v1, long v2) {
	  // El calculo del maximo comun divisor se hace por el algoritmo de Euclides
	v1 = abs(v1); 
    v2 = abs(v2);	
	if (v1 < v2) {
		long tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
	while (v2 != 0) {
		long nv2 = v1%v2;
		v1 = v2;
		v2 = nv2;
	}
	return v1;
}

long Racional::mcm(long v1, long v2) {
	return v1*v2 / mcd(v1, v2);
}


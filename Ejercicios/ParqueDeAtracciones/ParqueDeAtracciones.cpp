#include "ParqueDeAtracciones.h"

// COSTE O(1)
InfoNinio::InfoNinio(){
	atraccionesVisitadas = Diccionario<string, int>();
	esta_en_cola = false;
}

// COSTE O(n)
Lista<string> InfoNinio::atracciones_visitadas() const{
	Diccionario<string, int>::ConstIterator it = atraccionesVisitadas.cbegin();
	Lista<string> ret;
	while (it != atraccionesVisitadas.cend()){
		ret.pon_final(it.clave());
		it.next();
	}
	return ret;
}

// COSTE O(1)
ParqueDeAtracciones::ParqueDeAtracciones() {	
	ninios = DiccionarioHash<string, InfoNinio>();
	atracciones = DiccionarioHash<string, Lista<string> >();
}

// COSTE O(1)
void ParqueDeAtracciones::an_atraccion(const string& nombre_atraccion) {
	DiccionarioHash<string, Lista<string> >::ConstIterator it = atracciones.cbusca(nombre_atraccion);
	if (it != atracciones.cend()) throw EAtraccionYaExiste();
	atracciones.inserta(nombre_atraccion, Lista<string>());
}

// COSTE O(1)
void ParqueDeAtracciones::an_ninio(const string& nombre_ninio) {
	DiccionarioHash<string, InfoNinio >::ConstIterator it = ninios.cbusca(nombre_ninio);
	if (it != ninios.cend()) throw ENinioYaRegistrado();
	ninios.inserta(nombre_ninio, InfoNinio());
}

// COSTE O(1)
bool ParqueDeAtracciones::ninio_en_fila(const string& nombre_ninio){
	DiccionarioHash<string, InfoNinio >::ConstIterator it = ninios.cbusca(nombre_ninio);
	return it.valor().esta_en_cola;
}

// COSTE O(1)
void ParqueDeAtracciones::poner_en_fila(const string& nombre_ninio, const string& nombre_atraccion) {
	DiccionarioHash<string, InfoNinio >::Iterator itNinios = ninios.busca(nombre_ninio);
	DiccionarioHash<string, Lista<string> >::Iterator itAtracciones = atracciones.busca(nombre_atraccion);

	if (itNinios == ninios.end()|| // ninio no registrado
		itAtracciones == atracciones.end() || // No existe la atraccion
		ninio_en_fila(nombre_ninio) // El ninio esta en la fila
	) throw EAccesoAtraccion();
	
	itAtracciones.valor().pon_final(nombre_ninio);
	itNinios.valor().esta_en_cola = true;
}

// COSTE O(log(n))
// PORQUE SE BUSCA EN UN DICCIONARIO BASADO EN ARBOLES
void ParqueDeAtracciones::avanzar(const string& nombre_atraccion) {
	DiccionarioHash<string, Lista<string> >::Iterator itAtracciones = atracciones.busca(nombre_atraccion);
	if (itAtracciones == atracciones.end()) throw EAtraccionNoExiste();
	
	if (!itAtracciones.valor().esVacia()) {
		string nombre_ninio = itAtracciones.valor().primero();
		DiccionarioHash<string, InfoNinio >::Iterator itNinios = ninios.busca(nombre_ninio);
		
		Diccionario<string,int>::Iterator visitas = itNinios.valor().atraccionesVisitadas.busca(nombre_atraccion);
		
		if(visitas == itNinios.valor().atraccionesVisitadas.end())
			itNinios.valor().atraccionesVisitadas.inserta(nombre_atraccion, 1);
		else
			visitas.valor()++;

		itNinios.valor().esta_en_cola = false;
		itAtracciones.valor().quita_ppio();
	}

}

// COSTE O(n)
// POR QUE SE REQUIERE UN DICCIONARIO SOBRE ARBOL DE BUSQUEDA 
Lista<string> ParqueDeAtracciones::atracciones_visitadas(const string& nombre_ninio) const {
	DiccionarioHash<string, InfoNinio >::ConstIterator itNinios = ninios.cbusca(nombre_ninio);
	if (itNinios == ninios.cend()) throw ENinioNoRegistrado();

	return itNinios.valor().atracciones_visitadas();
}
   
// COSTE O(log(n))
// PORQUE SE BUSCA EN UN DICCIONARIO BASADO EN ARBOLES
int ParqueDeAtracciones::numero_visitas(const string& nombre_ninio, const string& nombre_atraccion) const {
	DiccionarioHash<string, InfoNinio >::ConstIterator itNinios = ninios.cbusca(nombre_ninio);
	DiccionarioHash<string, Lista<string> >::ConstIterator itAtracciones = atracciones.cbusca(nombre_atraccion);

	int visitas = 0;
	if (itNinios == ninios.cend() ||
	    itAtracciones == atracciones.cend()) throw EConsultaNumViajes();

	Diccionario<string, int>::ConstIterator atraccion = itNinios.valor().atraccionesVisitadas.cbusca(nombre_atraccion);
	
	int ret = 0;

	if (atraccion != itNinios.valor().atraccionesVisitadas.cend())
		ret = atraccion.valor();

	return ret;
}

/*

NOMBRE Y APELLIDOS:

*/

#include "SistemaVentas.h"
#include <iostream>

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 O(1)
	 
	*/
SistemaVentas::SistemaVentas() {
	// Vacio
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 O(1) Como es un diccionario hash todas sus operaciones tienen coste constante.
	 
	*/
void SistemaVentas::an_oferta(const tProducto& producto, unsigned int num_unidades) {
	if (productos.contiene(producto) || num_unidades <= 0) throw EErrorAltaProducto();
	productos.inserta(producto, Producto(num_unidades));
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 O(1) Acceder a una posicion de un diccionario hash es un opracion con tiempo constante
	 
	*/
void SistemaVentas::pon_en_espera(const tCliente& cliente, const tProducto& producto) {
	DiccionarioHash<tProducto, Producto>::Iterator itProducto = productos.busca(producto);

	if (itProducto == productos.end()) throw EProductoNoExiste();

	if (!clientes.contiene(cliente)) clientes.inserta(cliente, DiccionarioHash<tProducto, Posicion>());

	DiccionarioHash<tCliente, DiccionarioHash<tProducto, Posicion> >::Iterator itCliente = clientes.busca(cliente);
	DiccionarioHash<tProducto, Posicion>::Iterator itCliProd = itCliente.valor().busca(producto);

	if (itCliProd == itCliente.valor().end()){
		itProducto.valor()._lista_espera.pon_ppio(cliente);
		Posicion p = itProducto.valor()._lista_espera.begin();
		itCliente.valor().inserta(producto, p);
	}
}	
	
   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	  
	O(1) Como utilizamos diccionarios has el coste de todas las operaciones que realizamos es constante.
	 
	*/
void SistemaVentas::cancela_espera(const tCliente& cliente, const tProducto& producto) {
	DiccionarioHash<tProducto, Producto>::Iterator itProducto = productos.busca(producto);

	if (itProducto == productos.end()) throw EProductoNoExiste();

	DiccionarioHash<tCliente, DiccionarioHash<tProducto, Posicion> >::Iterator itCliente = clientes.busca(cliente);

	DiccionarioHash<tProducto, Posicion>::Iterator itCliProd = itCliente.valor().busca(producto);

	if (itCliProd != itCliente.valor().end()){
		Posicion p = itCliente.valor().valorPara(producto);
		itProducto.valor()._lista_espera.eliminar(p);
		itCliente.valor().borra(producto);
	}
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 O(1) Como utilizamos diccionarios has el coste de todas las operaciones que realizamos es constante.
	 
	*/
unsigned int SistemaVentas::num_en_espera(const tProducto& producto) const {
	DiccionarioHash<tProducto, Producto>::ConstIterator itProducto = productos.cbusca(producto);

	if (itProducto == productos.cend()) throw EProductoNoExiste();

	return itProducto.valor()._lista_espera.longitud();
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 O(N) ya que en el peor de los casos tengo que quitar a todos los clientes de lista de espera.
	 Siendo N el numero de clientes que se encuentren en la lista de espera.
	 
	*/
void SistemaVentas::venta(const tProducto& producto, unsigned int num_entradas) {
	/* A IMPLEMENTAR */
	DiccionarioHash<tProducto, Producto>::Iterator itProducto = productos.busca(producto);

	if ((itProducto == productos.end()) || // El producto debe estar ofertándose actualmente en el sistema
		(itProducto.valor()._lista_espera.esVacia()) || // La lista de espera de dicho producto no debe estar vacia
		(num_entradas > itProducto.valor()._num_unidades)) // El número de unidades solicitado no debe sobrepasar el numero de unidades disponibles
		throw EErrorVenta();
	
	// Realizamos la venta
	tCliente cliente = itProducto.valor()._lista_espera.ultimo();
	itProducto.valor()._lista_espera.quita_final();
	DiccionarioHash<tCliente, DiccionarioHash<tProducto, Posicion> >::Iterator itCliente = clientes.busca(cliente);
	itCliente.valor().borra(producto);
	itProducto.valor()._num_unidades -= num_entradas;

	if (itProducto.valor()._num_unidades == 0){
		// Limpiamos la lista y borramos el producto
		Lista<string>::Iterator itLista = itProducto.valor()._lista_espera.begin();

		while (itLista != itProducto.valor()._lista_espera.end()){
			cancela_espera(itLista.elem(), producto);
			itLista.next();
		}

		productos.borra(producto);
	}

	// Registramos la venta
	DiccionarioHash<tProducto, Venta>::Iterator itVenta = ventas.busca(producto);

	if (itVenta == ventas.end()){
		Venta v = Venta(producto, num_entradas);
		ventas.inserta(producto, v);
	}
	else{
		itVenta.valor()._unidades_vendidas += num_entradas;
	}
	
	
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 O(1) Como utilizamos diccionarios has el coste de todas las operaciones que realizamos es constante.
	 
	*/
const string& SistemaVentas::primero_en_espera(const tProducto& producto) const {
	DiccionarioHash<tProducto, Producto>::ConstIterator itProducto = productos.cbusca(producto);

	if (itProducto == productos.cend()) throw EErrorAccesoListaEspera();

	return itProducto.valor()._lista_espera.ultimo();
}

    /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 O(1) ya que la lista se obtiene directamente.
	*/
Lista<Venta> SistemaVentas::lista_ventas() const {

	DiccionarioHash<tProducto, Venta>::ConstIterator itVenta = ventas.cbegin();

	Lista<Venta> lista_ventas;

	while (itVenta != ventas.cend()){
		lista_ventas.pon_ppio(itVenta.valor());
		itVenta.next();
	}
	return lista_ventas;
}

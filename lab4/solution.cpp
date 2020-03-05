#include "cola.h"
#include <iostream>
using namespace std;

// A IMPLEMENTAR
void supervivientes(int n, Cola<int>& cola) {
	// Llenar la cola
	for (int i = 1; i <= n; i++){
		if (i % 2 == 0){
			cola.pon(i);
		}
	}

	int m = 3;
	while (m <= cola.longitud()){
		int longitud = cola.longitud();
		int cont = 0; 
		while (cont < longitud){
			if (cont % m == 0)
				// Hay que quitar el elemento
				cola.quita();
			else{
				int aux = cola.primero();
				cola.quita();
				cola.pon(aux);
			}
			cont++;
		}
		m++;
	}
};

int main() {
	
	int n;
	Cola<int> cola;

	cin >> n;
	while (n != 0){

		supervivientes(n, cola);

		cout << n << ":";
		while (!cola.esVacia()) {
			cout << " " << cola.primero();
			cola.quita();
		}
		cout << endl;
		
		cin >> n;	
	}
		
	return 0;
}

#include <iostream>
#include <string>
#include "../../TADs/pila.h"
using namespace std;

bool esEquilibrada(const string &cadena)
{
	Pila<char> p;
	bool ret = true;
	int i = 0;

    while( i < cadena.length() && ret){
        if (cadena[i] == '{'){
            p.apila(cadena[i]);
        }
        else if (cadena[i] == '}'){
            if (!p.esVacia() && (p.cima() == '{')){
                p.desapila();
            }
            else ret = false;
        }

        i++;
    }

    return ret && p.esVacia();
}

int main()
{
	string cadena;

	cout << "\n\n--- EJ 2: INDICAR SI UNA CADENA ESTA EQUILIBRADA EN LLAVES (\"{\" Y \"}\") ---\n";
    
    cadena = "28*{1+{2*3/{4-5}}}/2";
    cout << "\nLa cadena \"" << cadena << "\". Es: ";
    if (esEquilibrada(cadena))
		cout << "EQUILIBRADA" << endl;
	else
		cout << "NO_EQUILIBRADA" << endl;
    
	cadena = "{{{}}{";
    cout << "\nLa cadena \"" << cadena << "\". Es: ";
    if (esEquilibrada(cadena))
		cout << "EQUILIBRADA" << endl;
	else
		cout << "NO_EQUILIBRADA" << endl;
    
	cadena = "{{}}}";
    cout << "\nLa cadena \"" << cadena << "\". Es: ";
    if (esEquilibrada(cadena))
		cout << "EQUILIBRADA" << endl;
	else
		cout << "NO_EQUILIBRADA" << endl;
    
	return 0;
}

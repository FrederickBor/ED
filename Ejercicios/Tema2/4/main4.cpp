#include <iostream>
#include <string>
#include "../../TADs/pila.h"
#include <ctype.h>
using namespace std;


int postfijo(string exp) {
	Pila<int> p;
	
	for (int i = 0; i < exp.length(); ++i) {
		if (isdigit(exp[i])) {
			p.apila(exp[i]-48);
		}
		else {
			if (!p.esVacia()) {
				int num2 = p.cima();
				p.desapila();
				int num1 = p.cima();
				p.desapila();

				switch (exp[i])
				{
                    case '+': p.apila(num1 + num2);
                        break;
                    case '-': p.apila(num1 - num2);
                        break;
                    case '*': p.apila(num1 * num2);
                        break;
                    case '/': p.apila(num1 / num2);
                        break;

                    default:
                        break;
				}
			}

		}

		
	}

	return p.cima();
	
}

int main() {
	
	cout << "\n\n--- EJ 4: INDICAR EL RESULTADO DE UNA OPERACIÓN MATEMÁTICA EN NOTACIÓN POSTFIJA ---\n";

	string expresion = "821-/82+*";
	cout << postfijo(expresion) << endl;
        
	return 0;
}
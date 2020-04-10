#include <iostream>
#include <string>
#include "pila.h"
using namespace std;

bool esEquilibrada(const string &cadena)
{
	// A IMPLEMENTAR
	Pila<char> *p = new Pila<char>();
	bool ret = true;
	int i = 0;

	while (i < cadena.length() && ret)
	{
		if ( (cadena[i] == '(') || (cadena[i] == '{') || (cadena[i] == '[') )
		{
			p->apila(cadena[i]);
		}
		else if (cadena[i] == ')')
		{
			if (!p->esVacia() && '(' == p->cima())
			{
				p->desapila();
			}
			else
			{
				ret = false;
			}
		}
		else if (cadena[i] == '}')
		{
			if (!p->esVacia() && '{' == p->cima())
			{
				p->desapila();
			}
			else
			{
				ret = false;
			}
		}
		else if (cadena[i] == ']')
		{
			if (!p->esVacia() && '[' == p->cima())
			{
				p->desapila();
			}
			else
			{
				ret = false;
			}
		}

		i++;
	}

	return ret && p->esVacia();
}

int main()
{
	string cadena;
	while (getline(cin, cadena))
	{
		if (esEquilibrada(cadena))
			cout << "EQUILIBRADA" << endl;
		else
			cout << "NO_EQUILIBRADA" << endl;
	}
	return 0;
}

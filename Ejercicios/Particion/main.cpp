#include <iostream>
#include "dcola.h"

using namespace std;

void tratar_caso(int num_casos) {
    DCola<int> lista;

    int num, pivote;
    cin >> pivote;

    int i = 0;
    while (i < num_casos) {
        cin >> num;
        lista.pon_final(num);
        i++;
    }
    
    lista.particion(pivote);

    lista.imprimir();
    cout << endl;
}

int main() {
    int num_casos;

    while (cin >> num_casos) {
        tratar_caso(num_casos);
    }

    return 0;
}

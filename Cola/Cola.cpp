#include <iostream>

using namespace std;

const int MAX = 100;

class Cola {
private:
    int frente, final;
    int elementos[MAX];

public:
    Cola() {
        frente = final = 0;
    }

    bool encolar(int dato) {
        if (final == MAX) {
            cout << "Cola llena" << endl;
            return false;
        }
        elementos[final++] = dato;
        return true;
    }

    int desencolar() {
        if (frente == final) {
            cout << "Cola vacía" << endl;
            return -1;
        }
        return elementos[frente++];
    }

    int frenteCola() {
        if (frente == final) {
            cout << "Cola vacía" << endl;
            return -1;
        }
        return elementos[frente];
    }

    bool estaVacia() {
        return frente == final;
    }

    int tamanio() {
        return final - frente;
    }
};

int main() {
    Cola cola;

    cola.encolar(100);
    cola.encolar(200);
    cola.encolar(300);

    cout << "Desencolando: " << cola.desencolar() << endl;
    cout << "Frente de la cola: " << cola.frenteCola() << endl;
    cout << "Tamaño de la cola: " << cola.tamanio() << endl;

    if (cola.estaVacia()) {
        cout << "La cola esta vacia" << endl;
    }
    else {
        cout << "La cola no esta vacia" << endl;
    }

    return 0;
}

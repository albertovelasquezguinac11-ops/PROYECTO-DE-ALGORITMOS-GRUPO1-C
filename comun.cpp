// comun.cpp
// Definicion de las colecciones compartidas y utilidades de entrada.
// Responsable: Jesser Josue Betancourth Chinchilla (Modulo Principal)

#include <iostream>
#include <string>
#include <limits>
#include "comun.h"

using namespace std;

Libro catalogo[MAX_LIBROS];
int totalLibros = 0;

Usuario usuarios[MAX_USUARIOS];
int totalUsuarios = 0;

Prestamo prestamos[MAX_PRESTAMOS];
int totalPrestamos = 0;

int leerEntero(const string &mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  -> Entrada invalida. Ingrese un numero entero.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

string leerTexto(const string &mensaje) {
    string valor;
    while (true) {
        cout << mensaje;
        getline(cin, valor);
        if (valor.empty()) {
            cout << "  -> El campo no puede estar vacio.\n";
        } else {
            return valor;
        }
    }
}

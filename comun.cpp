// comun.cpp
// Definicion de las colecciones compartidas y utilidades de entrada.
// Responsable: Jesser Josue Betancourth Chinchilla (Modulo Principal)

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include "comun.h"

using namespace std;

Libro catalogo[MAX_LIBROS];
int totalLibros = 0;

Usuario usuarios[MAX_USUARIOS];
int totalUsuarios = 0;

Prestamo prestamos[MAX_PRESTAMOS];
int totalPrestamos = 0;

// Si la entrada se agota (el usuario pulsa Ctrl+Z en Windows o Ctrl+D en
// Linux, o se redirige un archivo que termina), cin queda en estado EOF de
// forma permanente: clear() no lo reabre y cualquier lectura posterior vuelve
// a fallar al instante. Sin este control, los bucles de abajo repetirian el
// mensaje de error para siempre. En ese caso se guardan los datos y se cierra
// el sistema de forma ordenada.
static void salirPorEntradaAgotada() {
    cout << "\n  -> La entrada se ha cerrado. El sistema se cerrara.\n";
    guardarDatosFinales();
    exit(0);
}

int leerEntero(const string &mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        if (cin.eof()) {
            salirPorEntradaAgotada();
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  -> Entrada invalida. Ingrese un numero entero.\n";
    }
}

string leerTexto(const string &mensaje) {
    string valor;
    while (true) {
        cout << mensaje;
        if (!getline(cin, valor)) {
            salirPorEntradaAgotada();
        }
        if (valor.empty()) {
            cout << "  -> El campo no puede estar vacio.\n";
        } else {
            return valor;
        }
    }
}

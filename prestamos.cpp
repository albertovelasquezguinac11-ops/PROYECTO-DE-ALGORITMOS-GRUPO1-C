// prestamos.cpp
// Modulo de Prestamos y Devoluciones - Responsable: Marco Antonio Garrido Chacon

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "comun.h"
#include "catalogo.h"
#include "usuarios.h"
#include "prestamos.h"

using namespace std;

const string ARCHIVO_PRESTAMOS = "prestamos.txt";

// Convierte un campo de texto a entero de forma segura.
// Devuelve true solo si el campo contiene un numero valido y completo.
// Parametros: campo (entrada), resultado (salida por referencia)
static bool aEntero(const string &campo, int &resultado) {
    if (campo.empty()) {
        return false;
    }
    try {
        size_t consumidos = 0;
        int valor = stoi(campo, &consumidos);
        if (consumidos != campo.size()) {
            return false;   // habia caracteres sobrantes: 12abc
        }
        resultado = valor;
        return true;
    } catch (const invalid_argument &) {
        return false;       // el campo no era un numero
    } catch (const out_of_range &) {
        return false;       // el numero no cabe en un int
    }
}

bool validarDisponibilidad(int codigoLibro) {
    int pos = buscarLibroPorCodigo(codigoLibro);
    if (pos == -1) {
        cout << "  -> El libro no existe en el catalogo.\n";
        return false;
    }
    if (!catalogo[pos].disponible) {
        cout << "  -> El libro ya esta prestado.\n";
        return false;
    }
    return true;
}

bool realizarPrestamo(int codigoLibro, int codigoUsuario) {
    if (buscarUsuarioPorCodigo(codigoUsuario) == -1) {
        cout << "  -> El usuario no existe.\n";
        return false;
    }
    if (!validarDisponibilidad(codigoLibro)) {
        return false;
    }
    if (totalPrestamos >= MAX_PRESTAMOS) {
        cout << "  -> No hay espacio disponible para mas prestamos.\n";
        return false;
    }
    int pos = buscarLibroPorCodigo(codigoLibro);
    catalogo[pos].disponible = false;

    prestamos[totalPrestamos].codigoLibro = codigoLibro;
    prestamos[totalPrestamos].codigoUsuario = codigoUsuario;
    prestamos[totalPrestamos].activo = true;
    totalPrestamos++;
    guardarPrestamosArchivo();
    return true;
}

bool registrarDevolucion(int codigoLibro, int codigoUsuario) {
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].codigoLibro == codigoLibro &&
            prestamos[i].codigoUsuario == codigoUsuario &&
            prestamos[i].activo) {
            prestamos[i].activo = false;
            int pos = buscarLibroPorCodigo(codigoLibro);
            if (pos != -1) {
                catalogo[pos].disponible = true;
            }
            guardarPrestamosArchivo();
            return true;
        }
    }
    cout << "  -> No se encontro un prestamo activo con esos datos.\n";
    return false;
}

int consultarPrestamosVigentes() {
    int vigentes = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].activo) {
            int posLibro = buscarLibroPorCodigo(prestamos[i].codigoLibro);
            int posUsuario = buscarUsuarioPorCodigo(prestamos[i].codigoUsuario);
            cout << "  Libro: " << (posLibro != -1 ? catalogo[posLibro].titulo : "?")
                 << " | Usuario: " << (posUsuario != -1 ? usuarios[posUsuario].nombre : "?") << "\n";
            vigentes++;
        }
    }
    if (vigentes == 0) {
        cout << "  -> No hay prestamos vigentes.\n";
    }
    return vigentes;
}

void guardarPrestamosArchivo() {
    ofstream archivo(ARCHIVO_PRESTAMOS);
    if (!archivo.is_open()) {
        cout << "  -> No se pudo guardar el archivo de prestamos.\n";
        return;
    }
    for (int i = 0; i < totalPrestamos; i++) {
        archivo << prestamos[i].codigoLibro << ";"
                << prestamos[i].codigoUsuario << ";"
                << (prestamos[i].activo ? 1 : 0) << "\n";
    }
    archivo.close();
}

void cargarPrestamosArchivo() {
    ifstream archivo(ARCHIVO_PRESTAMOS);
    if (!archivo.is_open()) {
        return;
    }

    string linea;
    int descartadas = 0;
    totalPrestamos = 0;

    while (getline(archivo, linea) && totalPrestamos < MAX_PRESTAMOS) {
        if (linea.empty()) {
            continue;
        }
        stringstream ss(linea);
        string campoLibro, campoUsuario, campoActivo;
        int codigoLibro, codigoUsuario, activoInt;

        // Si falta algun campo, la linea esta mal formada y se descarta.
        if (!getline(ss, campoLibro, ';') ||
            !getline(ss, campoUsuario, ';') ||
            !getline(ss, campoActivo, ';')) {
            descartadas++;
            continue;
        }

        // Si algun campo no es un numero valido, la linea se descarta.
        if (!aEntero(campoLibro, codigoLibro) ||
            !aEntero(campoUsuario, codigoUsuario) ||
            !aEntero(campoActivo, activoInt)) {
            descartadas++;
            continue;
        }

        prestamos[totalPrestamos].codigoLibro = codigoLibro;
        prestamos[totalPrestamos].codigoUsuario = codigoUsuario;
        prestamos[totalPrestamos].activo = (activoInt == 1);
        totalPrestamos++;

        if (activoInt == 1) {
            int posLibro = buscarLibroPorCodigo(codigoLibro);
            if (posLibro != -1) {
                catalogo[posLibro].disponible = false;
            }
        }
    }
    archivo.close();
    cout << "  -> Prestamos recuperados del archivo: " << totalPrestamos << "\n";
    if (descartadas > 0) {
        cout << "  -> Lineas descartadas por formato invalido: " << descartadas << "\n";
    }
}

void menuPrestamos() {
    int opcion;
    do {
        cout << "\n--- MODULO DE PRESTAMOS Y DEVOLUCIONES ---\n";
        cout << "1. Realizar prestamo\n";
        cout << "2. Registrar devolucion\n";
        cout << "3. Consultar prestamos vigentes\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int codigoLibro = leerEntero("Codigo del libro: ");
            int codigoUsuario = leerEntero("Codigo del usuario: ");
            if (realizarPrestamo(codigoLibro, codigoUsuario)) {
                cout << "  -> Prestamo realizado correctamente.\n";
            }
        } else if (opcion == 2) {
            int codigoLibro = leerEntero("Codigo del libro: ");
            int codigoUsuario = leerEntero("Codigo del usuario: ");
            if (registrarDevolucion(codigoLibro, codigoUsuario)) {
                cout << "  -> Devolucion registrada correctamente.\n";
            }
        } else if (opcion == 3) {
            consultarPrestamosVigentes();
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

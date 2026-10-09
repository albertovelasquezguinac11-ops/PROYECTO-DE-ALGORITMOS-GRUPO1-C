// reportes.cpp
// Modulo de Reportes y Estadisticas - Responsable: Aracely Adriana Rosales Bautista

#include <iostream>
#include <string>
#include "comun.h"
#include "catalogo.h"
#include "reportes.h"

using namespace std;

int calcularTotalLibros() {
    return totalLibros;
}

int listarLibrosDisponibles() {
    int cantidad = 0;
    for (int i = 0; i < totalLibros; i++) {
        if (catalogo[i].disponible) {
            cout << "  [" << catalogo[i].codigo << "] " << catalogo[i].titulo << "\n";
            cantidad++;
        }
    }
    if (cantidad == 0) {
        cout << "  -> No hay libros disponibles.\n";
    }
    return cantidad;
}

int listarLibrosPrestados() {
    int cantidad = 0;
    for (int i = 0; i < totalLibros; i++) {
        if (!catalogo[i].disponible) {
            cout << "  [" << catalogo[i].codigo << "] " << catalogo[i].titulo << "\n";
            cantidad++;
        }
    }
    if (cantidad == 0) {
        cout << "  -> No hay libros prestados actualmente.\n";
    }
    return cantidad;
}

int reportarPrestamosPorUsuario(int codigoUsuario) {
    int cantidad = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].codigoUsuario == codigoUsuario) {
            int posLibro = buscarLibroPorCodigo(prestamos[i].codigoLibro);
            cout << "  Libro: " << (posLibro != -1 ? catalogo[posLibro].titulo : "?")
                 << " | Estado: " << (prestamos[i].activo ? "Activo" : "Devuelto") << "\n";
            cantidad++;
        }
    }
    if (cantidad == 0) {
        cout << "  -> Este usuario no tiene prestamos registrados.\n";
    }
    return cantidad;
}

// calcularPorcentajeDisponibilidad() -> procesa el catalogo y calcula
// que porcentaje de libros esta disponible actualmente
// Parametros de entrada: ninguno
// Retorno: double con el porcentaje (0 a 100)
double calcularPorcentajeDisponibilidad() {
    if (totalLibros == 0) {
        return 0.0;
    }
    int disponibles = 0;
    for (int i = 0; i < totalLibros; i++) {
        if (catalogo[i].disponible) {
            disponibles++;
        }
    }
    return (disponibles * 100.0) / totalLibros;
}

void menuReportes() {
    int opcion;
    do {
        cout << "\n--- MODULO DE REPORTES Y ESTADISTICAS ---\n";
        cout << "1. Total de libros en el catalogo\n";
        cout << "2. Listar libros disponibles\n";
        cout << "3. Listar libros prestados\n";
        cout << "4. Prestamos por usuario\n";
        cout << "5. Porcentaje de disponibilidad del catalogo\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            cout << "  -> Total de libros: " << calcularTotalLibros() << "\n";
        } else if (opcion == 2) {
            listarLibrosDisponibles();
        } else if (opcion == 3) {
            listarLibrosPrestados();
        } else if (opcion == 4) {
            int codigoUsuario = leerEntero("Codigo del usuario: ");
            reportarPrestamosPorUsuario(codigoUsuario);
        } else if (opcion == 5) {
            cout << "  -> Disponibilidad: " << calcularPorcentajeDisponibilidad() << "%\n";
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

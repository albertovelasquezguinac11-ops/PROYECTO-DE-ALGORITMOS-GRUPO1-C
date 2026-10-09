// comun.h
// Datos compartidos y utilidades de entrada usadas por todos los modulos.
// Responsable: Jesser Josue Betancourth Chinchilla (Modulo Principal)

#ifndef COMUN_H
#define COMUN_H

#include <string>

const int MAX_LIBROS = 100;
const int MAX_USUARIOS = 100;
const int MAX_PRESTAMOS = 100;

struct Libro {
    int codigo;
    std::string titulo;
    std::string autor;
    bool disponible;
};

struct Usuario {
    int codigo;
    std::string nombre;
    std::string carne;
    std::string usuario;
    std::string contrasena;
    std::string rol;
};

struct Prestamo {
    int codigoLibro;
    int codigoUsuario;
    bool activo;
};

// Colecciones del sistema (definidas en comun.cpp)
extern Libro catalogo[MAX_LIBROS];
extern int totalLibros;

extern Usuario usuarios[MAX_USUARIOS];
extern int totalUsuarios;

extern Prestamo prestamos[MAX_PRESTAMOS];
extern int totalPrestamos;

// Utilidades de entrada con validacion
int leerEntero(const std::string &mensaje);
std::string leerTexto(const std::string &mensaje);

#endif

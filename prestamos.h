// prestamos.h
// Modulo de Prestamos y Devoluciones - Responsable: Marco Antonio Garrido Chacon

#ifndef PRESTAMOS_H
#define PRESTAMOS_H

bool validarDisponibilidad(int codigoLibro);
bool realizarPrestamo(int codigoLibro, int codigoUsuario);
bool registrarDevolucion(int codigoLibro, int codigoUsuario);
int consultarPrestamosVigentes();
void guardarPrestamosArchivo();
void cargarPrestamosArchivo();
void menuPrestamos();

#endif

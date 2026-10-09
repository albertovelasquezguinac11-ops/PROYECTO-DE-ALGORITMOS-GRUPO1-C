// reportes.h
// Modulo de Reportes y Estadisticas - Responsable: Aracely Adriana Rosales Bautista

#ifndef REPORTES_H
#define REPORTES_H

int calcularTotalLibros();
int listarLibrosDisponibles();
int listarLibrosPrestados();
int reportarPrestamosPorUsuario(int codigoUsuario);
double calcularPorcentajeDisponibilidad();
void menuReportes();

#endif

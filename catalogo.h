// catalogo.h
// Modulo de Catalogo - Responsable: Pablo Morales

#ifndef CATALOGO_H
#define CATALOGO_H

#include <string>

int buscarLibroPorCodigo(int codigo);
bool registrarLibro(int codigo, const std::string &titulo, const std::string &autor);
bool modificarLibro(int codigo, const std::string &nuevoTitulo, const std::string &nuevoAutor);
void consultarLibro(int codigo);
int buscarLibrosPorTitulo(const std::string &criterio);
void menuCatalogo();

#endif

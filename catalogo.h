
#ifndef CATALOGO_H
#define CATALOGO_H

#include <string>

// Busqueda
int buscarLibroPorCodigo(int codigo);
int buscarLibrosPorTitulo(const std::string &criterio);
int buscarLibrosPorAutor(const std::string &criterio);

// Registro, modificacion y eliminacion
bool registrarLibro(int codigo, const std::string &titulo, const std::string &autor);
bool modificarLibro(int codigo, const std::string &nuevoTitulo, const std::string &nuevoAutor);
bool eliminarLibro(int codigo);

// Consulta y listado
void consultarLibro(int codigo);
int listarCatalogo();
int contarLibrosDisponibles();

// Persistencia
void guardarCatalogoArchivo();
void cargarCatalogoArchivo();

// Menu
void menuCatalogo();

#endif

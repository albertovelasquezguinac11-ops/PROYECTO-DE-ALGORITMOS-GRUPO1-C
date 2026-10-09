// catalogo.cpp
// Modulo de Catalogo - Responsable: Pablo Morales

#include <iostream>
#include <string>
#include <cctype>
#include "comun.h"
#include "catalogo.h"

using namespace std;

// ---------- Funciones auxiliares (solo se usan dentro de este archivo) ----------

static string aMinusculas(string texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = tolower(static_cast<unsigned char>(texto[i]));
    }
    return texto;
}

static bool estaVacio(const string &texto) {
    return texto.find_first_not_of(" \t") == string::npos;
}

// ---------- Busqueda ----------

int buscarLibroPorCodigo(int codigo) {
    for (int i = 0; i < totalLibros; i++) {
        if (catalogo[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarLibrosPorTitulo(const string &criterio) {
    int encontrados = 0;
    string criterioMin = aMinusculas(criterio);
    for (int i = 0; i < totalLibros; i++) {
        if (aMinusculas(catalogo[i].titulo).find(criterioMin) != string::npos) {
            cout << "  [" << catalogo[i].codigo << "] " << catalogo[i].titulo
                 << " - " << catalogo[i].autor << "\n";
            encontrados++;
        }
    }
    if (encontrados == 0) {
        cout << "  -> No se encontraron coincidencias.\n";
    }
    return encontrados;
}

// ---------- Carga y modificacion ----------

bool registrarLibro(int codigo, const string &titulo, const string &autor) {
    if (codigo <= 0) {
        cout << "  -> El codigo debe ser un numero positivo.\n";
        return false;
    }
    if (estaVacio(titulo) || estaVacio(autor)) {
        cout << "  -> El titulo y el autor no pueden estar vacios.\n";
        return false;
    }
    if (totalLibros >= MAX_LIBROS) {
        cout << "  -> No hay espacio disponible en el catalogo.\n";
        return false;
    }
    if (buscarLibroPorCodigo(codigo) != -1) {
        cout << "  -> Ya existe un libro con ese codigo.\n";
        return false;
    }
    catalogo[totalLibros].codigo = codigo;
    catalogo[totalLibros].titulo = titulo;
    catalogo[totalLibros].autor = autor;
    catalogo[totalLibros].disponible = true;
    totalLibros++;
    return true;
}

bool modificarLibro(int codigo, const string &nuevoTitulo, const string &nuevoAutor) {
    int pos = buscarLibroPorCodigo(codigo);
    if (pos == -1) {
        cout << "  -> No existe un libro con ese codigo.\n";
        return false;
    }
    if (estaVacio(nuevoTitulo) || estaVacio(nuevoAutor)) {
        cout << "  -> El titulo y el autor no pueden estar vacios.\n";
        return false;
    }
    catalogo[pos].titulo = nuevoTitulo;
    catalogo[pos].autor = nuevoAutor;
    return true;
}

// ---------- Recorrido y procesamiento ----------

void consultarLibro(int codigo) {
    int pos = buscarLibroPorCodigo(codigo);
    if (pos == -1) {
        cout << "  -> No existe un libro con ese codigo.\n";
        return;
    }
    cout << "  Codigo: " << catalogo[pos].codigo << "\n";
    cout << "  Titulo: " << catalogo[pos].titulo << "\n";
    cout << "  Autor: " << catalogo[pos].autor << "\n";
    cout << "  Disponible: " << (catalogo[pos].disponible ? "Si" : "No") << "\n";
}

// Recorre todo el catalogo y lo muestra. Devuelve cuantos libros hay.
int listarCatalogo() {
    if (totalLibros == 0) {
        cout << "  -> El catalogo esta vacio.\n";
        return 0;
    }
    for (int i = 0; i < totalLibros; i++) {
        cout << "  [" << catalogo[i].codigo << "] " << catalogo[i].titulo
             << " - " << catalogo[i].autor
             << " (" << (catalogo[i].disponible ? "Disponible" : "Prestado") << ")\n";
    }
    return totalLibros;
}

// Procesamiento: cuenta los libros que estan disponibles.
int contarLibrosDisponibles() {
    int disponibles = 0;
    for (int i = 0; i < totalLibros; i++) {
        if (catalogo[i].disponible) {
            disponibles++;
        }
    }
    return disponibles;
}

// ---------- Menu ----------

void menuCatalogo() {
    int opcion;
    do {
        cout << "\n--- MODULO DE CATALOGO ---\n";
        cout << "1. Registrar libro\n";
        cout << "2. Modificar libro\n";
        cout << "3. Consultar libro\n";
        cout << "4. Buscar libros por titulo\n";
        cout << "5. Listar catalogo completo\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int codigo = leerEntero("Codigo del libro: ");
            string titulo = leerTexto("Titulo: ");
            string autor = leerTexto("Autor: ");
            if (registrarLibro(codigo, titulo, autor)) {
                cout << "  -> Libro registrado correctamente.\n";
            }
        } else if (opcion == 2) {
            int codigo = leerEntero("Codigo del libro a modificar: ");
            string titulo = leerTexto("Nuevo titulo: ");
            string autor = leerTexto("Nuevo autor: ");
            if (modificarLibro(codigo, titulo, autor)) {
                cout << "  -> Libro modificado correctamente.\n";
            }
        } else if (opcion == 3) {
            int codigo = leerEntero("Codigo del libro a consultar: ");
            consultarLibro(codigo);
        } else if (opcion == 4) {
            string criterio = leerTexto("Titulo o parte del titulo a buscar: ");
            buscarLibrosPorTitulo(criterio);
        } else if (opcion == 5) {
            int total = listarCatalogo();
            if (total > 0) {
                cout << "  Total: " << total << " libros, "
                     << contarLibrosDisponibles() << " disponibles.\n";
            }
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}
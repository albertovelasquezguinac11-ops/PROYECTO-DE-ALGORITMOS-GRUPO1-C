
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>

#include "comun.h"
#include "catalogo.h"

using namespace std;

// ---------- Funciones auxiliares ----------

static string aMinusculas(string texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = static_cast<char>(
            tolower(static_cast<unsigned char>(texto[i]))
        );
    }
    return texto;
}

static bool estaVacio(const string &texto) {
    return texto.find_first_not_of(" \t") == string::npos;
}

static bool contieneSeparador(const string &texto) {
    return texto.find(';') != string::npos;
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
    if (estaVacio(criterio)) {
        cout << "Ingrese un titulo para buscar.\n";
        return 0;
    }

    int encontrados = 0;
    string criterioMin = aMinusculas(criterio);

    for (int i = 0; i < totalLibros; i++) {
        if (aMinusculas(catalogo[i].titulo).find(criterioMin) != string::npos) {
            cout << "[" << catalogo[i].codigo << "] "
                 << catalogo[i].titulo << " - "
                 << catalogo[i].autor << "\n";
            encontrados++;
        }
    }

    if (encontrados == 0) {
        cout << "No se encontraron coincidencias.\n";
    }

    return encontrados;
}

int buscarLibrosPorAutor(const string &criterio) {
    if (estaVacio(criterio)) {
        cout << "Ingrese un autor para buscar.\n";
        return 0;
    }

    int encontrados = 0;
    string criterioMin = aMinusculas(criterio);

    for (int i = 0; i < totalLibros; i++) {
        if (aMinusculas(catalogo[i].autor).find(criterioMin) != string::npos) {
            cout << "[" << catalogo[i].codigo << "] "
                 << catalogo[i].titulo << " - "
                 << catalogo[i].autor << "\n";
            encontrados++;
        }
    }

    if (encontrados == 0) {
        cout << "No se encontraron coincidencias.\n";
    }

    return encontrados;
}

// ---------- Persistencia ----------

void guardarCatalogoArchivo() {
    ofstream archivo("catalogo.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo guardar catalogo.txt.\n";
        return;
    }

    for (int i = 0; i < totalLibros; i++) {
        archivo << catalogo[i].codigo << ";"
                << catalogo[i].titulo << ";"
                << catalogo[i].autor << "\n";
    }

    archivo.close();
}

void cargarCatalogoArchivo() {
    ifstream archivo("catalogo.txt");

    if (!archivo.is_open()) {
        cout << "No existe catalogo.txt. Se iniciara un catalogo vacio.\n";
        return;
    }

    string linea;
    int recuperados = 0;

    while (getline(archivo, linea) && totalLibros < MAX_LIBROS) {
        stringstream flujo(linea);
        string codigoTexto, titulo, autor, extra;

        if (!getline(flujo, codigoTexto, ';') ||
            !getline(flujo, titulo, ';') ||
            !getline(flujo, autor, ';')) {
            continue;
        }

        if (getline(flujo, extra)) {
            continue;
        }

        try {
            size_t posicion = 0;
            int codigo = stoi(codigoTexto, &posicion);

            if (posicion != codigoTexto.size() ||
                codigo <= 0 ||
                estaVacio(titulo) ||
                estaVacio(autor)) {
                continue;
            }

            if (buscarLibroPorCodigo(codigo) != -1) {
                continue;
            }

            catalogo[totalLibros].codigo = codigo;
            catalogo[totalLibros].titulo = titulo;
            catalogo[totalLibros].autor = autor;
            catalogo[totalLibros].disponible = true;

            totalLibros++;
            recuperados++;

        } catch (...) {
            continue;
        }
    }

    archivo.close();

    cout << "Libros recuperados: " << recuperados << "\n";
}

// ---------- Registro y modificacion ----------

bool registrarLibro(int codigo, const string &titulo, const string &autor) {
    if (codigo <= 0) {
        cout << "El codigo debe ser positivo.\n";
        return false;
    }

    if (estaVacio(titulo) || estaVacio(autor)) {
        cout << "El titulo y el autor no pueden estar vacios.\n";
        return false;
    }

    if (contieneSeparador(titulo) || contieneSeparador(autor)) {
        cout << "No se permite el caracter ; en titulo o autor.\n";
        return false;
    }

    if (totalLibros >= MAX_LIBROS) {
        cout << "No hay espacio disponible en el catalogo.\n";
        return false;
    }

    if (buscarLibroPorCodigo(codigo) != -1) {
        cout << "Ya existe un libro con ese codigo.\n";
        return false;
    }

    catalogo[totalLibros].codigo = codigo;
    catalogo[totalLibros].titulo = titulo;
    catalogo[totalLibros].autor = autor;
    catalogo[totalLibros].disponible = true;

    totalLibros++;
    guardarCatalogoArchivo();

    return true;
}

bool modificarLibro(int codigo, const string &nuevoTitulo,
                    const string &nuevoAutor) {
    int pos = buscarLibroPorCodigo(codigo);

    if (pos == -1) {
        cout << "No existe un libro con ese codigo.\n";
        return false;
    }

    if (estaVacio(nuevoTitulo) || estaVacio(nuevoAutor)) {
        cout << "El titulo y el autor no pueden estar vacios.\n";
        return false;
    }

    if (contieneSeparador(nuevoTitulo) ||
        contieneSeparador(nuevoAutor)) {
        cout << "No se permite el caracter ; en titulo o autor.\n";
        return false;
    }

    catalogo[pos].titulo = nuevoTitulo;
    catalogo[pos].autor = nuevoAutor;

    guardarCatalogoArchivo();

    return true;
}

// ---------- Eliminar libro ----------

bool eliminarLibro(int codigo) {
    int pos = buscarLibroPorCodigo(codigo);

    if (pos == -1) {
        cout << "No existe un libro con ese codigo.\n";
        return false;
    }

    if (!catalogo[pos].disponible) {
        cout << "No se puede eliminar: el libro esta prestado.\n";
        return false;
    }

    for (int i = pos; i < totalLibros - 1; i++) {
        catalogo[i] = catalogo[i + 1];
    }

    totalLibros--;

    guardarCatalogoArchivo();

    cout << "Libro eliminado correctamente.\n";
    return true;
}

// ---------- Consulta y listado ----------

void consultarLibro(int codigo) {
    int pos = buscarLibroPorCodigo(codigo);

    if (pos == -1) {
        cout << "No existe un libro con ese codigo.\n";
        return;
    }

    cout << "Codigo: " << catalogo[pos].codigo << "\n";
    cout << "Titulo: " << catalogo[pos].titulo << "\n";
    cout << "Autor: " << catalogo[pos].autor << "\n";
    cout << "Disponible: "
         << (catalogo[pos].disponible ? "Si" : "No") << "\n";
}

int listarCatalogo() {
    if (totalLibros == 0) {
        cout << "El catalogo esta vacio.\n";
        return 0;
    }

    for (int i = 0; i < totalLibros; i++) {
        cout << "[" << catalogo[i].codigo << "] "
             << catalogo[i].titulo << " - "
             << catalogo[i].autor << " ("
             << (catalogo[i].disponible ? "Disponible" : "Prestado")
             << ")\n";
    }

    return totalLibros;
}

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
        cout << "\n========== MODULO DE CATALOGO ==========\n";
        cout << "1. Registrar libro\n";
        cout << "2. Modificar libro\n";
        cout << "3. Consultar libro\n";
        cout << "4. Buscar libros por titulo\n";
        cout << "5. Listar catalogo completo\n";
        cout << "6. Buscar libros por autor\n";
        cout << "7. Eliminar libro\n";
        cout << "0. Volver al menu principal\n";

        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int codigo = leerEntero("Codigo del libro: ");
            string titulo = leerTexto("Titulo: ");
            string autor = leerTexto("Autor: ");

            if (registrarLibro(codigo, titulo, autor)) {
                cout << "Libro registrado correctamente.\n";
            }

        } else if (opcion == 2) {
            int codigo = leerEntero("Codigo del libro: ");
            string titulo = leerTexto("Nuevo titulo: ");
            string autor = leerTexto("Nuevo autor: ");

            if (modificarLibro(codigo, titulo, autor)) {
                cout << "Libro modificado correctamente.\n";
            }

        } else if (opcion == 3) {
            int codigo = leerEntero("Codigo del libro: ");
            consultarLibro(codigo);

        } else if (opcion == 4) {
            string criterio = leerTexto("Titulo o parte del titulo: ");
            buscarLibrosPorTitulo(criterio);

        } else if (opcion == 5) {
            int total = listarCatalogo();

            if (total > 0) {
                cout << "Total: " << total
                     << " | Disponibles: "
                     << contarLibrosDisponibles() << "\n";
            }

        } else if (opcion == 6) {
            string criterio = leerTexto("Nombre del autor: ");
            buscarLibrosPorAutor(criterio);

        } else if (opcion == 7) {
            int codigo = leerEntero("Codigo del libro que desea eliminar: ");

            string confirmacion = leerTexto(
                "Esta seguro de eliminar este libro? (S/N): "
            );

            if (confirmacion == "S" || confirmacion == "s") {
                eliminarLibro(codigo);
            } else {
                cout << "Operacion cancelada.\n";
            }

        } else if (opcion != 0) {
            cout << "Opcion no valida.\n";
        }

    } while (opcion != 0);
}

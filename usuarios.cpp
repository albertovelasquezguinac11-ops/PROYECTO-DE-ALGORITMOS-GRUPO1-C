// usuarios.cpp
// Modulo de Usuarios - Responsable: Alberto Velasquez Guinac

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "comun.h"
#include "usuarios.h"

using namespace std;

const string ARCHIVO_USUARIOS = "usuarios.txt";

// ---------- Funciones auxiliares (solo se usan dentro de este archivo) ----------

// Convierte un texto a entero. Devuelve false si no es un numero valido.
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

// true si el texto esta vacio o solo tiene espacios.
static bool estaVacio(const string &texto) {
    return texto.find_first_not_of(" \t") == string::npos;
}

// true si el rol es uno de los dos permitidos.
static bool rolValido(const string &rol) {
    return rol == "admin" || rol == "usuario";
}

// ---------- Busqueda ----------

int buscarUsuarioPorCodigo(int codigo) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarUsuarioPorNombre(const string &nombreUsuario) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].usuario == nombreUsuario) {
            return i;
        }
    }
    return -1;
}

bool registrarUsuario(int codigo, const string &nombre, const string &carne,
                      const string &nombreUsuario, const string &contrasena,
                      const string &rol) {
    if (codigo <= 0) {
        cout << "  -> El codigo debe ser un numero positivo.\n";
        return false;
    }
    if (estaVacio(nombre) || estaVacio(carne) ||
        estaVacio(nombreUsuario) || estaVacio(contrasena)) {
        cout << "  -> Ningun campo puede estar vacio.\n";
        return false;
    }
    // El ';' separa los campos en usuarios.txt: si se permitiera, romperia el archivo.
    if (nombre.find(';') != string::npos || carne.find(';') != string::npos ||
        nombreUsuario.find(';') != string::npos || contrasena.find(';') != string::npos) {
        cout << "  -> Los campos no pueden contener el caracter ';'.\n";
        return false;
    }
    if (!rolValido(rol)) {
        cout << "  -> Rol no valido (use admin o usuario).\n";
        return false;
    }
    if (totalUsuarios >= MAX_USUARIOS) {
        cout << "  -> No hay espacio disponible para mas usuarios.\n";
        return false;
    }
    if (buscarUsuarioPorCodigo(codigo) != -1) {
        cout << "  -> Ya existe un usuario con ese codigo.\n";
        return false;
    }
    if (buscarUsuarioPorNombre(nombreUsuario) != -1) {
        cout << "  -> Ese nombre de usuario ya existe.\n";
        return false;
    }

    usuarios[totalUsuarios].codigo = codigo;
    usuarios[totalUsuarios].nombre = nombre;
    usuarios[totalUsuarios].carne = carne;
    usuarios[totalUsuarios].usuario = nombreUsuario;
    usuarios[totalUsuarios].contrasena = contrasena;
    usuarios[totalUsuarios].rol = rol;
    totalUsuarios++;
    // Se guarda de inmediato, igual que registrarLibro() con el catalogo.
    // Si el sistema se cerrara de forma abrupta, un usuario recien creado se
    // perderia pero sus prestamos si quedarian guardados, dejando prestamos
    // que apuntan a un usuario inexistente.
    guardarUsuariosArchivo();
    return true;
}

void consultarUsuario(int codigo) {
    int pos = buscarUsuarioPorCodigo(codigo);
    if (pos == -1) {
        cout << "  -> No existe un usuario con ese codigo.\n";
        return;
    }
    cout << "  Codigo: " << usuarios[pos].codigo << "\n";
    cout << "  Nombre: " << usuarios[pos].nombre << "\n";
    cout << "  Carne: " << usuarios[pos].carne << "\n";
    cout << "  Usuario: " << usuarios[pos].usuario << "\n";
    cout << "  Rol: " << usuarios[pos].rol << "\n";
}

// listarUsuariosPorRol(rol) -> recorre el arreglo de usuarios y filtra por rol
// Parametros de entrada: rol ("admin" o "usuario")
// Retorno: cantidad de usuarios que cumplen el criterio
int listarUsuariosPorRol(const string &rol) {
    int cantidad = 0;
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].rol == rol) {
            cout << "  [" << usuarios[i].codigo << "] " << usuarios[i].nombre
                 << " (" << usuarios[i].usuario << ")\n";
            cantidad++;
        }
    }
    if (cantidad == 0) {
        cout << "  -> No hay usuarios con ese rol.\n";
    }
    return cantidad;
}

void menuUsuarios() {
    int opcion;
    do {
        cout << "\n--- MODULO DE USUARIOS ---\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Consultar usuario\n";
        cout << "3. Listar usuarios por rol\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int codigo = leerEntero("Codigo del usuario: ");
            string nombre = leerTexto("Nombre: ");
            string carne = leerTexto("Carne: ");
            string nombreUsuario = leerTexto("Nombre de usuario: ");
            string contrasena = leerTexto("Contrasena: ");

            cout << "Tipo de usuario:\n";
            cout << "1. Usuario\n";
            cout << "2. Administrador\n";
            int tipo = leerEntero("Seleccione el tipo: ");

            string rol;
            if (tipo == 1) {
                rol = "usuario";
            } else if (tipo == 2) {
                rol = "admin";
            } else {
                cout << "  -> Tipo de usuario no valido.\n";
                rol = "";
            }

            if (!rol.empty() &&
                registrarUsuario(codigo, nombre, carne, nombreUsuario, contrasena, rol)) {
                cout << "  -> Usuario registrado correctamente.\n";
            }
        } else if (opcion == 2) {
            int codigo = leerEntero("Codigo del usuario a consultar: ");
            consultarUsuario(codigo);
        } else if (opcion == 3) {
            string rol = leerTexto("Filtrar por rol (admin / usuario): ");
            listarUsuariosPorRol(rol);
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

// ---------- Persistencia en archivo ----------

// guardarUsuariosArchivo() -> escribe todos los usuarios en usuarios.txt
// Formato por linea: codigo;nombre;carne;usuario;contrasena;rol
// Parametros de entrada: ninguno
// Retorno: ninguno
void guardarUsuariosArchivo() {
    ofstream archivo(ARCHIVO_USUARIOS);
    if (!archivo.is_open()) {
        cout << "  -> No se pudo guardar el archivo de usuarios.\n";
        return;
    }
    for (int i = 0; i < totalUsuarios; i++) {
        archivo << usuarios[i].codigo << ";"
                << usuarios[i].nombre << ";"
                << usuarios[i].carne << ";"
                << usuarios[i].usuario << ";"
                << usuarios[i].contrasena << ";"
                << usuarios[i].rol << "\n";
    }
    archivo.close();
}

// cargarUsuariosArchivo() -> lee usuarios.txt y llena el arreglo de usuarios.
// Tolera archivos danados: una linea mal formada se descarta y se sigue
// con la siguiente, en lugar de detener el programa.
// Parametros de entrada: ninguno
// Retorno: ninguno
void cargarUsuariosArchivo() {
    ifstream archivo(ARCHIVO_USUARIOS);
    if (!archivo.is_open()) {
        return;     // primera ejecucion: todavia no existe el archivo
    }

    string linea;
    int descartadas = 0;
    totalUsuarios = 0;

    while (getline(archivo, linea)) {
        // Si el archivo se edito en Windows, la linea puede terminar en '\r'.
        if (!linea.empty() && linea[linea.size() - 1] == '\r') {
            linea.erase(linea.size() - 1);
        }
        if (linea.empty()) {
            continue;
        }
        if (totalUsuarios >= MAX_USUARIOS) {
            descartadas++;      // no cabe: el arreglo esta lleno
            continue;
        }

        stringstream ss(linea);
        string campoCodigo, nombre, carne, nombreUsuario, contrasena, rol;
        int codigo;

        // Si falta algun campo, la linea esta mal formada y se descarta.
        // El ultimo campo se lee hasta el final de la linea.
        if (!getline(ss, campoCodigo, ';') ||
            !getline(ss, nombre, ';') ||
            !getline(ss, carne, ';') ||
            !getline(ss, nombreUsuario, ';') ||
            !getline(ss, contrasena, ';') ||
            !getline(ss, rol)) {
            descartadas++;
            continue;
        }

        // Validar cada dato. Cualquier problema descarta la linea.
        if (!aEntero(campoCodigo, codigo) || codigo <= 0 ||
            estaVacio(nombre) || estaVacio(carne) ||
            estaVacio(nombreUsuario) || estaVacio(contrasena) ||
            !rolValido(rol)) {
            descartadas++;
            continue;
        }

        // Codigo o nombre de usuario repetidos: se conserva el primero.
        if (buscarUsuarioPorCodigo(codigo) != -1 ||
            buscarUsuarioPorNombre(nombreUsuario) != -1) {
            descartadas++;
            continue;
        }

        usuarios[totalUsuarios].codigo = codigo;
        usuarios[totalUsuarios].nombre = nombre;
        usuarios[totalUsuarios].carne = carne;
        usuarios[totalUsuarios].usuario = nombreUsuario;
        usuarios[totalUsuarios].contrasena = contrasena;
        usuarios[totalUsuarios].rol = rol;
        totalUsuarios++;
    }
    archivo.close();
    cout << "  -> Usuarios recuperados del archivo: " << totalUsuarios << "\n";
    if (descartadas > 0) {
        cout << "  -> Lineas descartadas por formato invalido: " << descartadas << "\n";
    }
}

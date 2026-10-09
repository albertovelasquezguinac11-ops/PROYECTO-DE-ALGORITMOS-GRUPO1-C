// usuarios.cpp
// Modulo de Usuarios - Responsable: Alberto Velasquez Guinac

#include <iostream>
#include <string>
#include "comun.h"
#include "usuarios.h"

using namespace std;

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

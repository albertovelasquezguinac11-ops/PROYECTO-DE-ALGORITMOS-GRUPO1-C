// main.cpp
// Modulo Principal (menu e integracion) - Responsable: Jesser Josue Betancourth Chinchilla
// main() solo coordina: carga datos, inicia sesion y deriva a cada modulo.

#include <iostream>
#include <string>
#include "comun.h"
#include "catalogo.h"
#include "usuarios.h"
#include "prestamos.h"
#include "reportes.h"

using namespace std;

void cargarDatosIniciales() {
    cout << "Cargando datos del sistema...\n";
    cargarPrestamosArchivo();
}

void guardarDatosFinales() {
    cout << "Guardando datos del sistema...\n";
    guardarPrestamosArchivo();
}

// Cuenta de administrador de PRUEBA que se crea al iniciar el sistema.
// Sirve para poder entrar la primera vez y registrar el resto de usuarios.
// En una version real la contrasena no deberia estar escrita en el codigo.
void cargarUsuarioAdministrador() {
    registrarUsuario(1, "Administrador", "ADMIN",
                     "admin", "admin123", "admin");
}

int iniciarSesion() {
    string nombreUsuario;
    string contrasena;

    cout << "\n========================================\n";
    cout << "       INICIO DE SESION\n";
    cout << "========================================\n";

    for (int intento = 1; intento <= 3; intento++) {
        nombreUsuario = leerTexto("Usuario: ");
        contrasena = leerTexto("Contrasena: ");

        for (int i = 0; i < totalUsuarios; i++) {
            if (usuarios[i].usuario == nombreUsuario &&
                usuarios[i].contrasena == contrasena) {
                cout << "\nBienvenido, " << usuarios[i].nombre << ".\n";
                cout << "Rol: " << usuarios[i].rol << "\n";
                return i;
            }
        }

        cout << "  -> Usuario o contrasena incorrectos.\n";
        cout << "  -> Intento " << intento << " de 3.\n\n";
    }

    cout << "Se agotaron los intentos de inicio de sesion.\n";
    return -1;
}

void mostrarMenuUsuario(int indiceUsuario) {
    int opcion;

    do {
        cout << "\n========================================\n";
        cout << " MENU DE USUARIO\n";
        cout << " Usuario: " << usuarios[indiceUsuario].nombre << "\n";
        cout << "========================================\n";
        cout << "1. Consultar libro\n";
        cout << "2. Buscar libros por titulo\n";
        cout << "3. Realizar prestamo\n";
        cout << "4. Registrar devolucion\n";
        cout << "5. Consultar mis prestamos\n";
        cout << "0. Cerrar sesion\n";
        cout << "========================================\n";

        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            int codigo = leerEntero("Codigo del libro: ");
            consultarLibro(codigo);
        } else if (opcion == 2) {
            string criterio = leerTexto("Titulo o parte del titulo: ");
            buscarLibrosPorTitulo(criterio);
        } else if (opcion == 3) {
            int codigoLibro = leerEntero("Codigo del libro: ");
            if (realizarPrestamo(codigoLibro, usuarios[indiceUsuario].codigo)) {
                cout << "  -> Prestamo realizado correctamente.\n";
            }
        } else if (opcion == 4) {
            int codigoLibro = leerEntero("Codigo del libro: ");
            if (registrarDevolucion(codigoLibro, usuarios[indiceUsuario].codigo)) {
                cout << "  -> Devolucion registrada correctamente.\n";
            }
        } else if (opcion == 5) {
            reportarPrestamosPorUsuario(usuarios[indiceUsuario].codigo);
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

void mostrarMenuAdministrador() {
    int opcion;

    do {
        cout << "\n========================================\n";
        cout << " MENU DE ADMINISTRADOR\n";
        cout << "========================================\n";
        cout << "1. Modulo de Catalogo\n";
        cout << "2. Modulo de Usuarios\n";
        cout << "3. Modulo de Prestamos y Devoluciones\n";
        cout << "4. Modulo de Reportes y Estadisticas\n";
        cout << "0. Cerrar sesion\n";
        cout << "========================================\n";

        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            menuCatalogo();
        } else if (opcion == 2) {
            menuUsuarios();
        } else if (opcion == 3) {
            menuPrestamos();
        } else if (opcion == 4) {
            menuReportes();
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

int main() {
    cargarDatosIniciales();
    cargarUsuarioAdministrador();

    while (true) {
        int indiceUsuario = iniciarSesion();

        if (indiceUsuario == -1) {
            cout << "El sistema se cerrara.\n";
            return 0;
        }

        if (usuarios[indiceUsuario].rol == "admin") {
            mostrarMenuAdministrador();
        } else {
            mostrarMenuUsuario(indiceUsuario);
        }

        cout << "\nSesion cerrada.\n";
        cout << "1. Iniciar sesion nuevamente\n";
        cout << "0. Salir\n";

        int opcion = leerEntero("Seleccione una opcion: ");
        if (opcion == 0) {
            guardarDatosFinales();
            cout << "Saliendo del sistema. Hasta pronto.\n";
            break;
        }
    }

    return 0;
}

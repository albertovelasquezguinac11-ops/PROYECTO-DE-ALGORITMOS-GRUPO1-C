#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_LIBROS = 100;
const int MAX_USUARIOS = 100;
const int MAX_PRESTAMOS = 100;

struct Libro {
    int codigo;
    string titulo;
    string autor;
    bool disponible;
};
Libro catalogo[MAX_LIBROS];
int totalLibros = 0;

struct Usuario {
    int codigo;
    string nombre;
    string carne;
    string usuario;
    string contrasena;
    string rol;
};
Usuario usuarios[MAX_USUARIOS];
int totalUsuarios = 0;

struct Prestamo {
    int codigoLibro;
    int codigoUsuario;
    bool activo;
};
Prestamo prestamos[MAX_PRESTAMOS];
int totalPrestamos = 0;

int leerEntero(const string &mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  -> Entrada invalida. Ingrese un numero entero.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

string leerTexto(const string &mensaje) {
    string valor;
    while (true) {
        cout << mensaje;
        getline(cin, valor);
        if (valor.empty()) {
            cout << "  -> El campo no puede estar vacio.\n";
        } else {
            return valor;
        }
    }
}

int buscarLibroPorCodigo(int codigo) {
    for (int i = 0; i < totalLibros; i++) {
        if (catalogo[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

bool registrarLibro(int codigo, const string &titulo, const string &autor) {
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
    catalogo[pos].titulo = nuevoTitulo;
    catalogo[pos].autor = nuevoAutor;
    return true;
}

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

int buscarLibrosPorTitulo(const string &criterio) {
    int encontrados = 0;
    for (int i = 0; i < totalLibros; i++) {
        if (catalogo[i].titulo.find(criterio) != string::npos) {
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

void menuCatalogo() {
    int opcion;
    do {
        cout << "\n--- MODULO DE CATALOGO ---\n";
        cout << "1. Registrar libro\n";
        cout << "2. Modificar libro\n";
        cout << "3. Consultar libro\n";
        cout << "4. Buscar libros por titulo\n";
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
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

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

void menuUsuarios() {
    int opcion;
    do {
        cout << "\n--- MODULO DE USUARIOS ---\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Consultar usuario\n";
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
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

bool validarDisponibilidad(int codigoLibro) {
    int pos = buscarLibroPorCodigo(codigoLibro);
    if (pos == -1) {
        cout << "  -> El libro no existe en el catalogo.\n";
        return false;
    }
    if (!catalogo[pos].disponible) {
        cout << "  -> El libro ya esta prestado.\n";
        return false;
    }
    return true;
}

bool realizarPrestamo(int codigoLibro, int codigoUsuario) {
    if (buscarUsuarioPorCodigo(codigoUsuario) == -1) {
        cout << "  -> El usuario no existe.\n";
        return false;
    }
    if (!validarDisponibilidad(codigoLibro)) {
        return false;
    }
    if (totalPrestamos >= MAX_PRESTAMOS) {
        cout << "  -> No hay espacio disponible para mas prestamos.\n";
        return false;
    }
    int pos = buscarLibroPorCodigo(codigoLibro);
    catalogo[pos].disponible = false;

    prestamos[totalPrestamos].codigoLibro = codigoLibro;
    prestamos[totalPrestamos].codigoUsuario = codigoUsuario;
    prestamos[totalPrestamos].activo = true;
    totalPrestamos++;
    return true;
}

bool registrarDevolucion(int codigoLibro, int codigoUsuario) {
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].codigoLibro == codigoLibro &&
            prestamos[i].codigoUsuario == codigoUsuario &&
            prestamos[i].activo) {
            prestamos[i].activo = false;
            int pos = buscarLibroPorCodigo(codigoLibro);
            if (pos != -1) {
                catalogo[pos].disponible = true;
            }
            return true;
        }
    }
    cout << "  -> No se encontro un prestamo activo con esos datos.\n";
    return false;
}

int consultarPrestamosVigentes() {
    int vigentes = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].activo) {
            int posLibro = buscarLibroPorCodigo(prestamos[i].codigoLibro);
            int posUsuario = buscarUsuarioPorCodigo(prestamos[i].codigoUsuario);
            cout << "  Libro: " << (posLibro != -1 ? catalogo[posLibro].titulo : "?")
                 << " | Usuario: " << (posUsuario != -1 ? usuarios[posUsuario].nombre : "?") << "\n";
            vigentes++;
        }
    }
    if (vigentes == 0) {
        cout << "  -> No hay prestamos vigentes.\n";
    }
    return vigentes;
}

void menuPrestamos() {
    int opcion;
    do {
        cout << "\n--- MODULO DE PRESTAMOS Y DEVOLUCIONES ---\n";
        cout << "1. Realizar prestamo\n";
        cout << "2. Registrar devolucion\n";
        cout << "3. Consultar prestamos vigentes\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int codigoLibro = leerEntero("Codigo del libro: ");
            int codigoUsuario = leerEntero("Codigo del usuario: ");
            if (realizarPrestamo(codigoLibro, codigoUsuario)) {
                cout << "  -> Prestamo realizado correctamente.\n";
            }
        } else if (opcion == 2) {
            int codigoLibro = leerEntero("Codigo del libro: ");
            int codigoUsuario = leerEntero("Codigo del usuario: ");
            if (registrarDevolucion(codigoLibro, codigoUsuario)) {
                cout << "  -> Devolucion registrada correctamente.\n";
            }
        } else if (opcion == 3) {
            consultarPrestamosVigentes();
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

int calcularTotalLibros() {
    return totalLibros;
}

int listarLibrosDisponibles() {
    int cantidad = 0;
    for (int i = 0; i < totalLibros; i++) {
        if (catalogo[i].disponible) {
            cout << "  [" << catalogo[i].codigo << "] " << catalogo[i].titulo << "\n";
            cantidad++;
        }
    }
    if (cantidad == 0) {
        cout << "  -> No hay libros disponibles.\n";
    }
    return cantidad;
}

int listarLibrosPrestados() {
    int cantidad = 0;
    for (int i = 0; i < totalLibros; i++) {
        if (!catalogo[i].disponible) {
            cout << "  [" << catalogo[i].codigo << "] " << catalogo[i].titulo << "\n";
            cantidad++;
        }
    }
    if (cantidad == 0) {
        cout << "  -> No hay libros prestados actualmente.\n";
    }
    return cantidad;
}

int reportarPrestamosPorUsuario(int codigoUsuario) {
    int cantidad = 0;
    for (int i = 0; i < totalPrestamos; i++) {
        if (prestamos[i].codigoUsuario == codigoUsuario) {
            int posLibro = buscarLibroPorCodigo(prestamos[i].codigoLibro);
            cout << "  Libro: " << (posLibro != -1 ? catalogo[posLibro].titulo : "?")
                 << " | Estado: " << (prestamos[i].activo ? "Activo" : "Devuelto") << "\n";
            cantidad++;
        }
    }
    if (cantidad == 0) {
        cout << "  -> Este usuario no tiene prestamos registrados.\n";
    }
    return cantidad;
}

void menuReportes() {
    int opcion;
    do {
        cout << "\n--- MODULO DE REPORTES Y ESTADISTICAS ---\n";
        cout << "1. Total de libros en el catalogo\n";
        cout << "2. Listar libros disponibles\n";
        cout << "3. Listar libros prestados\n";
        cout << "4. Prestamos por usuario\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            cout << "  -> Total de libros: " << calcularTotalLibros() << "\n";
        } else if (opcion == 2) {
            listarLibrosDisponibles();
        } else if (opcion == 3) {
            listarLibrosPrestados();
        } else if (opcion == 4) {
            int codigoUsuario = leerEntero("Codigo del usuario: ");
            reportarPrestamosPorUsuario(codigoUsuario);
        } else if (opcion != 0) {
            cout << "  -> Opcion no valida.\n";
        }
    } while (opcion != 0);
}

void cargarDatosIniciales() {
    cout << "Cargando datos del sistema...\n";
}

void guardarDatosFinales() {
    cout << "Guardando datos del sistema...\n";
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
            guardarDatosFinales();
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

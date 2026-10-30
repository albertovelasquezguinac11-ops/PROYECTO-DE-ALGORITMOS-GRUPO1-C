# Sistema de Gestión de Biblioteca

Proyecto Final — Algoritmos, sección C — Grupo 1

**Repositorio:** https://github.com/albertovelasquezguinac11-ops/PROYECTO-DE-ALGORITMOS-GRUPO1-C

## Descripción

Sistema modular en C++ para automatizar el control del catálogo, los usuarios
y los préstamos de una biblioteca, reduciendo los errores del registro manual.
Incluye inicio de sesión con dos roles: **administrador** (acceso completo a
los cuatro módulos) y **usuario** (consulta de libros, préstamos, devoluciones
y sus propios préstamos).

## Integrantes y módulos

| Integrante | Carné | Módulo | Archivos |
|---|---|---|---|
| Jesser Josué Betancourth Chinchilla | 6590-19-8654 | Módulo Principal / Autenticación | `main.cpp`, `comun.h`, `comun.cpp` |
| Pablo José Eduardo Morales Hernández | 6590-26-21537 | Módulo de Catálogo | `catalogo.h`, `catalogo.cpp` |
| Alberto Velásquez Güinac | 6590-26-26581 | Módulo de Usuarios | `usuarios.h`, `usuarios.cpp` |
| Marco Antonio Garrido Chacón | 6590-26-23445 | Préstamos y Devoluciones | `prestamos.h`, `prestamos.cpp` |
| Aracely Adriana Rosales Bautista | 6590-26-26474 | Reportes y Estadísticas | `reportes.h`, `reportes.cpp` |

## Estructura del repositorio

Cada módulo vive en su propio par de archivos `.h` / `.cpp`; `main.cpp` solo
coordina (inicio de sesión y menús).

```
PROYECTO-DE-ALGORITMOS-GRUPO1-C/
├── main.cpp                  # Menú principal, login y arranque
├── comun.h / comun.cpp       # Structs, arreglos compartidos y lectura validada
├── catalogo.h / .cpp         # Módulo de Catálogo
├── usuarios.h / .cpp         # Módulo de Usuarios
├── prestamos.h / .cpp        # Módulo de Préstamos y Devoluciones
├── reportes.h / .cpp         # Módulo de Reportes y Estadísticas
├── datos_prueba/             # Archivos de ejemplo (normales y corrupto)
└── README.md                 # Este archivo
```

## Cómo compilar

Se compilan los seis `.cpp` juntos:

```bash
g++ -std=c++17 -Wall -Wextra main.cpp comun.cpp catalogo.cpp usuarios.cpp prestamos.cpp reportes.cpp -o biblioteca
```

En Dev-C++ hay que crear un **proyecto** y agregar esos seis archivos
(Proyecto → Añadir al proyecto). Si se compila un solo archivo suelto aparece
el error `undefined reference`.

## Cómo ejecutar

```bash
./biblioteca          # Linux / Mac / WSL
biblioteca.exe        # Windows
```

## Usuario administrador por defecto

Al iniciar el sistema por primera vez se crea automáticamente una cuenta
de administrador para poder entrar y registrar el resto de libros y usuarios:

- **Usuario:** `admin`
- **Contraseña:** `admin123`

## Estructuras de datos

| Módulo | Datos | Estructura | Operaciones |
|---|---|---|---|
| Catálogo | Libros | arreglo de `Libro` | cargar, recorrer, buscar por código, título y autor, contar disponibles, guardar y leer archivo |
| Usuarios | Usuarios | arreglo de `Usuario` | cargar, recorrer, buscar, filtrar por rol |
| Préstamos | Préstamos | arreglo de `Prestamo` | cargar, recorrer, buscar, guardar y leer archivo |
| Reportes | Catálogo y préstamos | usa los arreglos anteriores | contar, filtrar, calcular porcentaje (con **función recursiva** `contarDisponiblesRec`) |

## Persistencia en archivos

Los datos se guardan en archivos de texto con campos separados por `;`. Al
leerlos, una línea dañada se descarta y el programa sigue funcionando.

| Archivo | Contenido | Estado |
|---|---|---|
| `prestamos.txt` | Préstamos y devoluciones | Implementado |
| `usuarios.txt` | Usuarios, con rol y contraseña | Implementado |
| `catalogo.txt` | Libros (`codigo;titulo;autor`) | Implementado |

Estos archivos se generan al ejecutar el programa y **no se suben al
repositorio** (están en `.gitignore`). `usuarios.txt` guarda las contraseñas
en texto plano: es una simplificación del proyecto académico.

## Flujo de trabajo con Git

```bash
git checkout main
git pull
git switch -c feature/nombre-de-tu-cambio
# editar SOLO los archivos de tu módulo
git add <tus archivos>
git commit -m "mensaje descriptivo"
git push -u origin feature/nombre-de-tu-cambio
# abrir Pull Request hacia main, pedir revisión y hacer merge
```

## Pendientes

- Cifrar o aplicar hash a las contraseñas guardadas.
- Más reportes y diagramas finales por módulo.

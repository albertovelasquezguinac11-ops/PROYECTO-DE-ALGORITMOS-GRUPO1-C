# Sistema de Gestión de Biblioteca

Proyecto Final — Algoritmos, sección C — Grupo 1

## Descripción

Sistema modular en C++ para automatizar el control del catálogo, los usuarios
y los préstamos de una biblioteca, reduciendo los errores del registro manual.
Incluye inicio de sesión con dos roles: **administrador** (acceso completo a
los cuatro módulos) y **usuario** (consulta de libros, préstamos, devoluciones
y sus propios préstamos).

## Integrantes y módulos

| Integrante | Carné | Módulo | Rama |
|---|---|---|---|
| Jesser Josué Betancourth Chinchilla | 6590-19-8654 | Módulo Principal / Autenticación | `feature/modulo-principal` |
| Pablo José Eduardo Morales Hernández| 6590-26-21537 | Módulo de Catálogo | `feature/modulo-catalogo` |
| Alberto Velásquez Güinac | 6590-26-26581 | Módulo de Usuarios | `feature/modulo-usuarios` |
| Marco Antonio Garrido Chacón | 6590-26-23445 | Préstamos y Devoluciones | `feature/modulo-prestamos` |
| Aracely Adriana Rosales Bautista | 6590-26-26474 | Reportes y Estadísticas | `feature/modulo-reportes` |

## Estructura del repositorio

```
PROYECTO-DE-ALGORITMOS-GRUPO1-C/
├──PROYECTO_ALGORITMOS.cpp   # Código fuente del sistema
├── README.md        # Este archivo
└── docs/            # Diagramas de la Entrega 01 y Entrega 02
```

## Cómo compilar

```bash
g++ -std=c++17 -Wall -Wextra PROYECTO_ALGORITMOS.cpp  -o biblioteca
```

## Cómo ejecutar

```bash
./biblioteca          # Linux / Mac
biblioteca.exe        # Windows
```

## Usuario administrador por defecto

Al iniciar el sistema por primera vez se crea automáticamente una cuenta
de administrador para poder entrar y registrar el resto de libros y usuarios:

- **Usuario:** `admin`
- **Contraseña:** `admin123`

## Estado del proyecto

Primer avance funcional — Entrega 02. Incluye autenticación con roles.
El proyecto aún no tiene persistencia en archivos; eso se implementará
en una entrega posterior (ya están los puntos de extensión
`cargarDatosIniciales()` y `guardarDatosFinales()`).

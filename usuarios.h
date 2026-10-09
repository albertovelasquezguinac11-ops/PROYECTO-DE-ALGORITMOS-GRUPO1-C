// usuarios.h
// Modulo de Usuarios - Responsable: Alberto Velasquez Guinac

#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>

int buscarUsuarioPorCodigo(int codigo);
int buscarUsuarioPorNombre(const std::string &nombreUsuario);
bool registrarUsuario(int codigo, const std::string &nombre, const std::string &carne,
                      const std::string &nombreUsuario, const std::string &contrasena,
                      const std::string &rol);
void consultarUsuario(int codigo);
int listarUsuariosPorRol(const std::string &rol);
void menuUsuarios();

#endif

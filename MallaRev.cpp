#include "MallaRev.hpp"
#include "file_ply_stl.hpp"
#include <cmath>

float MallaRevol::altera_x(float x, double alpha) {
  return x * alpha;
}

float MallaRevol::altera_z(float z, double alpha) {
  return z * alpha;
}

void MallaRevol::construir(unsigned num_perfiles) {
  vertex_coords.erase(vertex_coords.begin(), vertex_coords.end());
  indexes.erase(indexes.begin(), indexes.end());

  const unsigned Nc = perfil.size(), Nv = perfil.size()/3;
  const double TAU = 6.2831853; // τ = 2π

  // Para calcular todos los vértices tomamos el perfil y lo
  // rotamos a pasos de 2π/num_perfiles

  for (unsigned giro = 0; giro < num_perfiles; giro++)
    for (unsigned i = 0; i < Nc; i += 3) {
      double alpha = TAU * giro / num_perfiles;

      vertex_coords.push_back(Tupla3f(
        altera_x(perfil[i] * cos(alpha), alpha),
        perfil.at(i + 1),
        altera_z(perfil[i] * sin(alpha), alpha)
      ));
    }

  // Añadimos vértices para las bases superior e inferior
  vertex_coords.push_back(Tupla3f(0, perfil.at(1),      0)); // num_perfiles * Nv
  vertex_coords.push_back(Tupla3f(0, perfil.at(Nc - 2), 0)); // num_perfiles * Nv + 1

  // Unimos cada vértice con su lateral y los del siguiente perfil
  for (unsigned giro = 0; giro < num_perfiles; giro++)
    for (unsigned i = 0; i < Nv - 1; i++) {
      indexes.push_back(Tupla3i(
        giro * Nv + i,
        (giro + 1)%num_perfiles * Nv + i,
        (giro + 1)%num_perfiles * Nv + i + 1
      ));
      indexes.push_back(Tupla3i(
        giro * Nv + i,
        giro * Nv + i + 1,
        (giro + 1)%num_perfiles * Nv + i + 1
      ));
    }

  // Caras correspondientes a las bases:
  for (unsigned giro = 0; giro < num_perfiles; giro++) {
    indexes.push_back(Tupla3i(
      giro * Nv,
      (giro + 1)%num_perfiles * Nv,
      num_perfiles * Nv
    ));
  }

  for (unsigned giro = 0; giro < num_perfiles; giro++) {
    indexes.push_back(Tupla3i(
      giro * Nv + (Nv - 1),
      (giro + 1)%num_perfiles * Nv + (Nv - 1),
      num_perfiles * Nv + 1
    ));
  }
}

MallaRevol::MallaRevol(const char * filename, unsigned num_perfiles, std::string nombre) {
  nombre_obj = nombre;

  ply::read_vertices(filename, perfil);
  construir(num_perfiles);
}

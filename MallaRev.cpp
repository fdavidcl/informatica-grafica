#include "MallaRev.hpp"
#include "file_ply_stl.hpp"
#include <cmath>

void MallaRevol::construir(unsigned num_perfiles) {
  vertex_coords.erase(vertex_coords.begin(), vertex_coords.end());
  indexes.erase(indexes.begin(), indexes.end());

  const int Nc = perfil.size(), Nv = perfil.size()/3;
  const double TAU = 6.2831853; // τ = 2π

  // Para calcular todos los vértices tomamos el perfil y lo
  // rotamos a pasos de 2π/num_perfiles

  for (int giro = 0; giro < num_perfiles; giro++)
    for (int i = 0; i < Nc; i += 3) {
      vertex_coords.push_back(Tupla3f(
        perfil[i] * cos(TAU * giro / num_perfiles),
        perfil.at(i + 1),
        perfil[i] * sin(TAU * giro / num_perfiles)
      ));
    }

  for (int giro = 0; giro < num_perfiles; giro++)
    for (int i = 0; i < Nv - 1; i++) {
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
}

MallaRevol::MallaRevol(const char * filename, unsigned num_perfiles, std::string nombre) {
  nombre_obj = nombre;

  ply::read_vertices(filename, perfil);
  construir(num_perfiles);
}

#include "MallaRev.hpp"
#include "file_ply_stl.hpp"
#include <cmath>

void MallaRevol::construir(unsigned num_perfiles, bool base_inferior, bool base_superior) {
  num_perfiles = num_perfiles;
  vertex_coords.erase(vertex_coords.begin(), vertex_coords.end());
  indexes.erase(indexes.begin(), indexes.end());

  const unsigned Nc = perfil.size(), Nv = perfil.size()/3;
  const double TAU = 6.2831853; // τ = 2π

  // Para calcular todos los vértices tomamos el perfil y lo
  // rotamos a pasos de 2π/num_perfiles

  // Hemos de duplicar vértices para usar las coordenadas de textura
  for (unsigned giro = 0; giro <= num_perfiles; giro++)
    for (unsigned i = 0; i < Nc; i += 3) {
      vertex_coords.push_back(Tupla3f(
        perfil[i] * cos(TAU * giro / num_perfiles),
        perfil.at(i + 1),
        perfil[i] * sin(TAU * giro / num_perfiles)
      ));
    }

  // Añadimos vértices para las bases superior e inferior
  vertex_coords.push_back(Tupla3f(0, perfil.at(1),      0)); // (num_perfiles + 1) * Nv
  vertex_coords.push_back(Tupla3f(0, perfil.at(Nc - 2), 0)); // (num_perfiles + 1) * Nv + 1

  // Unimos cada vértice con su lateral y los del siguiente perfil
  // Puesto que el último perfil y el primero están sobre los mismos
  // puntos, no es necesario unirlos
  for (unsigned giro = 0; giro < num_perfiles; giro++)
    for (unsigned i = 0; i < Nv - 1; i++) {
      indexes.push_back(Tupla3i(
        giro * Nv + i,
        (giro + 1) * Nv + i,
        (giro + 1) * Nv + i + 1
      ));
      indexes.push_back(Tupla3i(
        // seleccionamos vértices en el sentido positivo
        // (la regla del tornillo nos dice que la normal será hacia afuera)
        giro * Nv + i,
        (giro + 1) * Nv + i + 1,
        giro * Nv + i + 1
      ));
    }

  // Caras correspondientes a las bases:
  if (base_inferior)
    for (unsigned giro = 0; giro < num_perfiles; giro++) {
      indexes.push_back(Tupla3i(
        giro * Nv,
        (giro + 1) * Nv,
        (num_perfiles + 1) * Nv
      ));
    }

  if (base_superior)
    for (unsigned giro = 0; giro < num_perfiles; giro++) {
      indexes.push_back(Tupla3i(
        giro * Nv + (Nv - 1),
        (giro + 1) * Nv + (Nv - 1),
        (num_perfiles + 1) * Nv + 1
      ));
    }

  calcularNormales();
}

void MallaRevol::generar_coords_textura() {
  unsigned v_por_perfil = perfil.size()/3,
    total_perfiles = vertex_coords.size() / v_por_perfil;

  // Obtenemos las alturas normalizadas de los vértices del perfil
  std::vector<float> alturas;
  float norma = perfil.at(perfil.size() - 2) - perfil.at(1);

  alturas.push_back(0);
  for (unsigned j = 1; j < v_por_perfil; ++j) {
    alturas.push_back((vertex_coords.at(j)(Y) - perfil.at(1))/norma);
  }

  // Calculamos las coordenadas de textura
  for (unsigned i = 0; i < total_perfiles; i++) {
    for (unsigned j = 0; j < alturas.size(); ++j) {
      text_coords.push_back(Tupla2f(
        i / (float)(total_perfiles - 1),
        alturas.at(j)
      ));
    }
  }
}

MallaRevol::MallaRevol(const char * filename, unsigned num_perfiles, bool usar_textura, bool base_inferior, bool base_superior, std::string nombre) {
  nombre_obj = nombre;

  ply::read_vertices(filename, perfil);
  construir(num_perfiles, base_inferior, base_superior);

  if (usar_textura)
    generar_coords_textura();
}

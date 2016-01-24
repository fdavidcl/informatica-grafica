/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

#include "file_ply_stl.hpp"
#include <cmath>

void MallaBarrido::construir(unsigned num_traslaciones) {
  vertex_coords.erase(vertex_coords.begin(), vertex_coords.end());
  indexes.erase(indexes.begin(), indexes.end());

  const unsigned Nc = figura.size(), Nv = figura.size()/3;

  // Creamos los vértices trasladando la figura base por el vector
  // de traslación
  for (unsigned i = 0; i < Nc; i += 3) {
    Tupla3f punto_actual(figura[i], figura.at(i + 1), figura.at(i + 2));

    for (unsigned t = 0; t < num_traslaciones; t++)
      vertex_coords.push_back(punto_actual + (vector_traslacion * t));
  }

  // Unimos cada vértice con su lateral y los del trasladado
  for (unsigned i = 0; i < Nv - 1; i++)
    for (unsigned t = 0; t < num_traslaciones - 1; t++) {
      indexes.push_back(Tupla3i(
        i * num_traslaciones + t,
        i * num_traslaciones + t + 1, // enfrente
        (i + 1)%Nv * num_traslaciones + t + 1 // enfrente - siguiente
      ));
      indexes.push_back(Tupla3i(
        i * num_traslaciones + t,
        (i + 1) * num_traslaciones + t, // siguiente
        (i + 1) * num_traslaciones + t + 1 // enfrente - siguiente
      ));
    }
}

MallaBarrido::MallaBarrido(const char * filename, unsigned num_traslaciones, Tupla3f vect, std::string nombre) {
  nombre_obj = nombre;

  ply::read_vertices(filename, figura);
  vector_traslacion = vect;
  construir(num_traslaciones);
}

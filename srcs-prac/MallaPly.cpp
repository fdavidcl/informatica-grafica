/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

#include "MallaPly.hpp"
#include "file_ply_stl.hpp"

MallaPly::MallaPly(const char * filename, std::string nombre) {
  nombre_obj = nombre;

  std::vector<float> vertices;
  std::vector<int> caras;
  ply::read(filename, vertices, caras);

  for (int i = 0; i < vertices.size(); i += 3) {
    vertex_coords.push_back(Tupla3f(vertices[i], vertices.at(i + 1), vertices.at(i + 2)));
  }

  for (int i = 0; i < caras.size(); i += 3) {
    indexes.push_back(Tupla3i(caras[i], caras.at(i + 1), caras.at(i + 2)));
  }
}

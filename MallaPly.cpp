#include "MallaPly.hpp"
#include "file_ply_stl.hpp"

MallaPly::MallaPly(const char * filename) {
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

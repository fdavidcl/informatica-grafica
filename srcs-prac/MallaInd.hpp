/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

#ifndef MALLAIND_HPP
#define MALLAIND_HPP

#include "Objeto3D.hpp"
#include "tuplasg.hpp"
#include <vector>

// Clase derivada de Objeto3D para representación de mallas indexadas
class MallaInd : public Objeto3D {
protected:
  std::vector<Tupla3f> vertex_coords;
  std::vector<Tupla3i> indexes;

  // Tablas de normales
  std::vector<Tupla3f> normales_caras;
  std::vector<Tupla3f> normales_vertices;

  void calcularNormales();

  // Tabla de coordenadas de textura
  std::vector<Tupla2f> text_coords;

public:
  //MallaInd() :color(0,0,0) {}
  virtual void visualizar(ContextoVis cv);

  void imprimir();
};

#endif

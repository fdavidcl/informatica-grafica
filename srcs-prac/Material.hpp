/**********************************************************************
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at https://mozilla.org/MPL/2.0/.
**********************************************************************/

#ifndef __MATERIAL
#define __MATERIAL

#include "aux.hpp"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"
#include "tuplasg.hpp"

class Material {
public:
  virtual void activar() = 0;
};

// ---------------------------------------------------------------------
// Imagen de textura

class Textura {
public:
  GLuint id_text; // identificador OpenGL de la textura
  jpg::Imagen* img; // puntero a imagen con los texels
  unsigned mgct; // modo de gen. cc.tt.
  float cs[4], // coeficientes para generación de
        ct[4]; // coordenadas de textura

  // activa textura en el cauce fijo de OpenGL
  void activar();
  // crea una textura a partir de un archivo
  Textura(const std::string& archivoJPG, unsigned mgct);
};

// ---------------------------------------------------------------------
// Parámetros de un material estándar (Amb.+Diffuso+Phong)

class MaterialEstandar : public Material {
public:
  Textura * text; // puntero a la textura (NULL si no hay)
  Tupla4f color[4]; // colores: 0=emisión, 1=ambiental, 2=difuso, 3=especular
  float exponente; // exponente para la componente pseudo-especular

  virtual void activar();// activa material en el cauce fijo
                         //   si tiene textura: activa uso de la textura 'text'
                         //   si no tiene textura: desactiva uso de texturas
};

class MaterialLata : public MaterialEstandar {
public:
  MaterialLata();
};

class MaterialTapasLata : public MaterialEstandar {
public:
  MaterialTapasLata();
};

class MaterialPeonMadera : public MaterialEstandar {
public:
  MaterialPeonMadera();
};

class MaterialPeonBlanco : public MaterialEstandar {
public:
  MaterialPeonBlanco();
};

class MaterialPeonNegro : public MaterialEstandar {
public:
  MaterialPeonNegro();
};

class MaterialBaseR2 : public MaterialEstandar {
public:
  MaterialBaseR2();
};

class MaterialAzulR2 : public MaterialEstandar {
public:
  MaterialAzulR2();
};

class MaterialCuerpoR2 : public MaterialEstandar {
public:
  MaterialCuerpoR2();
};

#endif

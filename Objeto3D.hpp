#ifndef OBJETO3D_HPP
#define OBJETO3D_HPP

#include <string>
#include "tuplasg.hpp"

// clase abstracta para objetos 3D visualizables con OpenGL
class Objeto3D {
protected:
  std::string nombre_obj; // nombre asignado al objeto
  Tupla3f color;

public:
  Objeto3D() :color(0,0,0) {}
  virtual void visualizar(unsigned modo_vis) = 0; // visualizar el objeto con OpenGL
  std::string nombre();  // devuelve el nombre del objeto
  void setColor(Tupla3f new_color) { color = new_color; }
};

#endif

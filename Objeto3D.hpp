#ifndef OBJETO3D_HPP
#define OBJETO3D_HPP

#include <string>
#include "tuplasg.hpp"
#include "Material.hpp"

class ContextoVis {
public:
  unsigned modo_vis;
  Material * materialActivo;

  // Constructor de ContextoVis que mantiene la compatibilidad
  // con el código que sigue utilizando únicamente el entero modo_vis
  ContextoVis(unsigned v, Material * m = NULL) :modo_vis(v), materialActivo(m) {}
};

// clase abstracta para objetos 3D visualizables con OpenGL
class Objeto3D {
protected:
  std::string nombre_obj; // nombre asignado al objeto
  Tupla3f color;

public:
  Objeto3D() :color(0,0,0) {}
  virtual void visualizar(ContextoVis cv) = 0; // visualizar el objeto con OpenGL
  std::string nombre();  // devuelve el nombre del objeto
  void setColor(Tupla3f new_color) { color = new_color; }
};

#endif

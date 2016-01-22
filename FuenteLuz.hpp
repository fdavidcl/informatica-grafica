#ifndef __FUENTE_LUZ
#define __FUENTE_LUZ

#include <vector>
#include "aux.hpp"
#include "tuplasg.hpp"

// ---------------------------------------------------------------------
// Parámetros que definen una fuente de luz

class FuenteLuz
{
protected:
  int index;
public:
  Tupla4f  posvec; // posición (si w=1) o vector (w=0)
  Tupla4f  colores[3]; // colores: 0=ambiental, 1=difuso, 2=especular.
  float    longi, lati; // ángulos de rotación (fuente direccional modificable interactivamente)

  FuenteLuz(int index, float longi, float lati, Tupla4f posvec)
    :index(index), longi(longi), lati(lati), posvec(posvec) {}

  void activar(int i); // activa la fuente de luz (con número GL_LIGHT0+i)
};

// ---------------------------------------------------------------------
// Colección de (hasta 8) fuentes de luz.

class ColeccionFL {
public:
  std::vector<FuenteLuz*> fuentes; // vector de fuentes de luz
  void activar(); // activa todas las fuentes de luz en el cauce fijo
                  //   (antes de eso activa iluminación y la configura)
};

class FuenteDireccional : public FuenteLuz {
public:
  FuenteDireccional(int index, float longi, float lati);
  void variarAngulo(unsigned angulo, float incremento);  // angulo=0 --> variar alpha, angulo=1 --> variar beta
};

class FuentePosicional : public FuenteLuz {
public:
  FuentePosicional(int index, const Tupla3f& posicion);
};

class ColeccionFuentesP4 : public ColeccionFL {
public:
  ColeccionFuentesP4();
};

#endif

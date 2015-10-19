// *********************************************************************
// **
// ** Informática Gráfica, curso 2015-16
// ** Práctica 1  (declaraciones públicas)
// **
// *********************************************************************

#ifndef IG_PRACTICA1_HPP
#define IG_PRACTICA1_HPP

#include "MallaInd.hpp"

void P1_Inicializar( int argc, char *argv[] ) ;
bool P1_FGE_PulsarTeclaNormal(  unsigned char tecla ) ;
void P1_DibujarObjetos( unsigned modo ) ;

class Cubo : public MallaInd {
public:
  Cubo();
};

class Tetraedro : public MallaInd {
public:
  Tetraedro();
};

class Cono : public MallaInd {
public:
  Cono(unsigned prec);
};

class Cilindro : public MallaInd {
public:
  Cilindro(unsigned prec);
};

class Toro : public MallaInd {
private:
  // Calcula el vértice (x, y, z) a partir de las ecuaciones paramétricas
  double rad_int,
    rad_ext;
  Tupla3f vertice(double theta, double phi);
public:
  Toro(double R, double r, unsigned prec);
};

#endif

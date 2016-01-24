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
  Cubo(std::string nombre = "Cubo");
};

class Tetraedro : public MallaInd {
public:
  Tetraedro(std::string nombre = "Tetraedro");
};

class Cono : public MallaInd {
public:
  Cono(unsigned prec, std::string nombre = "Cono");
};

class Cilindro : public MallaInd {
public:
  Cilindro(unsigned prec, std::string nombre = "Cilindro");
};

class Toro : public MallaInd {
private:
  double rad_int,
    rad_ext;
  // Calcula el vértice (x, y, z) a partir de las ecuaciones paramétricas
  Tupla3f vertice(double theta, double phi);
public:
  Toro(double R, double r, unsigned prec, std::string nombre = "Toro");
};

class Moebius : public MallaInd {
private:
  Tupla3f vertice(double u, double v);
public:
  Moebius(unsigned prec, std::string nombre = "Cinta de Möbius");
};

class Klein : public MallaInd {
private:
  Tupla3f vertice(double u, double v);
public:
  Klein(unsigned prec, std::string nombre = "Botella de Klein");
};

#endif

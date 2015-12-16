#ifndef __R2
#define __R2
#include "NodoGrafoEscena.hpp"

class CabezaR2 : public NodoGrafoEscena {
private:
  float giro, offset_cam;
public:
  CabezaR2(float giro, float offset_cam);
  float girar(float nuevo_giro);
  float desplazar_cam(float nuevo_offset);
};

class CuerpoR2 : public NodoGrafoEscena {
public:
  CuerpoR2();
};

class BrazoSuperior : public NodoGrafoEscena {
public:
  BrazoSuperior();
};

class LadoBrazo : public NodoGrafoEscena {
public:
  LadoBrazo();
};

class BrazoR2 : public NodoGrafoEscena {
private:
  float giro, offset;
public:
  BrazoR2(float giro, float offset);
  float girar(float nuevo_giro);
  float desplazar(float nuevo_offset);
};

class PataR2 : public NodoGrafoEscena {
public:
  PataR2();
};

class R2 : public NodoGrafoEscena {
public:
  R2();
};

#endif

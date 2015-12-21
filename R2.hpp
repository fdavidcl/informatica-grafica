#ifndef __R2
#define __R2
#include "NodoGrafoEscena.hpp"

class ProjR2 : public NodoGrafoEscena {
private:
  float offset;
public:
  ProjR2(float offset);

  //float desplazar(float nuevo_offset);
};

class Camara : public NodoGrafoEscena {
public:
  Camara();
};

class CabezaR2 : public NodoGrafoEscena {
private:
  float giro, offset;
  ProjR2 * pr;
public:
  CabezaR2(float giro, float offset);
  /**void girar(float nuevo_giro);
  void desplazar(float nuevo_offset) {
    pr->desplazar(nuevo_offset);
  }**/
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
  /*void girar(float nuevo_giro);
  void desplazar(float nuevo_offset);*/
};

class PataR2 : public NodoGrafoEscena {
public:
  PataR2();
};

class R2 : public NodoGrafoEscena {
private:
  float giro_cabeza, offset_proj, giro_brazos, offset_brazos;
  CabezaR2 * cabeza;
  BrazoR2 * brazos[2];

public:
  static const float DEFAULT_VALUE;
  R2();
  void girar_cabeza(float giro);
  void girar_brazos(float giro);
  void extender_proj(float offset);
  void extender_brazos(float offset);
};

#endif
